/*
 * Validator.cpp
 *
 *  Created on: 8 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "Validator.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <windows.h>
#include <mmsystem.h>
#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>

#include "../labellise.hpp"
#include "../Language/LanguageLoader.h"
#include "../utils/math/Vector.h"
#include "../resources/resource.h"
#include "../window/Layer/content/Buttons/Button.h"
#include "../window/Layer/content/plot/line/Line.h"
#include "../window/Layer/content/plot/box/Box.h"
#include "../window/Layer/content/plot/point/ScenePoint.h"
#include "../window/Layer/content/plot/Plot3d.h"
#include "../window/Window.cxx"
#include "../window/Window.h"
#include "LabeliserMenu.h"

namespace window {

std::shared_ptr<Validator> Validator::create(const std::shared_ptr<Button>& validate, const std::shared_ptr<Button>& cancel, Window& window,
		const std::shared_ptr<LabeliserMenu>& labeliserMenu) {
	struct make_shared_enabler: public Validator {
		make_shared_enabler(const std::shared_ptr<Button>& validate, const std::shared_ptr<Button>& cancel, Window& window,
				const std::shared_ptr<LabeliserMenu>& labeliserMenu) :
				Validator(validate, cancel, window, labeliserMenu) {
		}
	};

	validate->hide();
	cancel->hide();

	cancel->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::Escape });
	validate->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::Return });

	std::shared_ptr<Validator> validator = std::make_shared<make_shared_enabler>(validate, cancel, window, labeliserMenu);

	validate->setCallBack([validator](float time) {
		validator->applyChanges();
	});

	cancel->setCallBack([validator] (float time) {
		validator->abord();
	});

	return validator;
}

void Validator::applyChanges() {
	enable = false;
	labeliserMenu->setText(textAfterValidation);
	lastText = "";

	validate->hide();
	cancel->hide();

	std::stack<std::shared_ptr<utils::ScenePoint>> points = std::stack<std::shared_ptr<utils::ScenePoint>>();
	window.getEditor()->applyEvents();

	for (const auto& point : window.getScenePoints())
		if (point->getOldName() != point->getLabel()) {
			point->applyChanges(window, true);
			points.push(point);
		}

	while (!points.empty()) {
		points.top()->applyChanges(window, false);
		points.pop();
	}

	for (const auto& point : window.getScenePoints())
		point->applyGroupesChanges(window);

	for (const auto& point : window.getModelPoints())
		point->applyGroupesChanges(window);

	for (const auto& box : window.getLabelisationBoxes())
		box->applyChanges();

	window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::UpdateIncompletePoints>::access(window,
			&Labeliser::updateIncompletePoints);

	if (window.getLabeliserMenu()->isInLabelisation())
		if (window.getController()->getModelFrame() == UINT_MAX) {
			window.getController()->setModelFrame(window.getController()->getCurrentFrame());

			window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::SetModelFrame>::access(window,
					&Labeliser::setModelFrame, window.getController()->getModelFrame());
		} else
			window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::SetGapFrames>::access(window, &Labeliser::setGapFrames);

	if (!labeliserMenu->isAutomaticModeEnable()) {
		if (window.getLabeliserMenu()->isInLabelisation())
			labeliserMenu->applyChanges();

		labeliserMenu->enable();

		window.getController()->enable();
		window.getSelector()->endSelection();
	}

	unPause();
}

bool Validator::isEnable() const {
	return enable;
}

void Validator::unPause() {
	std::unique_lock<std::mutex> lck(waiterMutex);

	waiter.notify_one();
}

void Validator::start(const std::string& textDuringValidation, const std::string& textAfterValidation, bool stopFlag) {
	enable = true;
	window.getController()->disable();
	labeliserMenu->disable();
	this->textAfterValidation = textAfterValidation;

	bool stopFlag2 = false;

	if (labeliserMenu->isAutomaticModeEnable()) {
		const std::unordered_map<unsigned long long int, std::tuple<std::string, labeliser::Box>>& labelisationBoxes =
				window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetLabelisationBoxes>::access(window,
						&Labeliser::getLabelisationBoxes);

		for (const auto& point : window.getScenePoints()) {
			if (point->getColor() != window::Window::labellisedColor && point->getColor() != window::Window::newlySuppressedColorPoint)
				continue;

			::Vector3d coords = point->getPosition();

			bool ignore = false;

			for (const auto& box : labelisationBoxes) {
				if (std::get<1>(box.second).isInside(coords)) {
					if (point->getLabel() != std::get<0>(box.second)) {
						point->unlinkPoint();

						for (const auto& modelPoint : window.getModelPoints())
							if (modelPoint->getLabel() == std::get<0>(box.second)) {
								window.addLineToPlot(
										utils::Line::createLine(modelPoint, point, window::Window::labelisedColorLine, 0.001f));
							}

						point->setLabel(std::get<0>(box.second));

						if (std::get<0>(box.second) != "outlier") {
							point->setColor(window::Window::labellisedColor);
							point->setSize(window::Window::labellisedSize);
						}
					}

					ignore = true;

					break;
				}
			}

			if (!ignore) {
				if (point->getLabel() != "outlier")
					try {
						if (!window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::CheckPredictionMatch>::access(window,
								&Labeliser::checkPredictionMatch, point->getLabel(), coords))
							stopFlag2 = true;
					} catch (...) {
						if (stopFlag)
							stopFlag2 = true;
					}
			}
		}

		if (stopFlag && stopFlag2) {
			std::unique_lock<std::mutex> lck(waiterMutex);

			const auto& oldText = labeliserMenu->getText();
			labeliserMenu->setText(SERIALIZER->getAutoModeWaitText());
			validate->enable();
			validate->display();
			cancel->enable();
			cancel->display();
			window.get3dPlotLayer()->enable();
			window.getSelector()->enable();
			window.getEditor()->enable();

			PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE);
			SetForegroundWindow(window.getSystemHandle());

			window.windowLock.unlock();
			waiter.wait(lck);
			window.windowLock.lock();

			labeliserMenu->setText(oldText);
			window.getSelector()->disable();
			window.getEditor()->disable();
			window.get3dPlotLayer()->disable();
		}

		validate->getCallBack()(1.f);
		return;
	}

	if (lastText == "")
		lastText = labeliserMenu->getText();

	labeliserMenu->setText(textDuringValidation);

	validate->enable();
	cancel->enable();
	validate->display();
	cancel->display();
	labeliserMenu->disable();
}

void Validator::abord() {
	enable = false;

	labeliserMenu->abordLabelisation();

	if (lastText != "") {
		labeliserMenu->setText(lastText);
		lastText = "";
	}

	validate->hide();
	cancel->hide();
	labeliserMenu->enable();

	window.getController()->enable();
	window.getSelector()->endSelection();

	if (labeliserMenu->isAutomaticModeEnable()) {
		unPause();
		labeliserMenu->exitAutomaticMode = true;
	}
}

Validator::Validator(const std::shared_ptr<Button>& validate, const std::shared_ptr<Button>& cancel, Window& window,
		const std::shared_ptr<LabeliserMenu>& labeliserMenu) :
		validate(validate), cancel(cancel), window(window), labeliserMenu(labeliserMenu), waiterMutex(), waiter() {
}

Validator::~Validator() {
}

} /* namespace window */
