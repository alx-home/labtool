/*
 * LabeliserMenu.cpp
 *
 *  Created on: 8 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "LabeliserMenu.h"

#include <windows.h>
#include <mmsystem.h>
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>
#include <vector>

#include "../exception/labellisation/AutoModeEndException.h"
#include "../labellise.hpp"
#include "../Language/LanguageLoader.h"
#include "../resources/resource.h"
#include "../window/Layer/content/Buttons/Button.h"
#include "../window/Layer/content/plot/Plot2d.h"
#include "../window/Layer/content/plot/Plot3d.h"
#include "../window/Layer/disposition/ConstrainedLayer.h"
#include "../window/Layer/disposition/MarginLayer.h"
#include "../window/Layer/disposition/SplitLayer.h"
#include "../window/Layer/disposition/StakeLayer.h"
#include "../window/Layer/disposition/TabLayer.h"
#include "../window/Layer/Layer.h"
#include "../window/Window.cxx"
#include "../window/Window.h"

namespace window {

LabeliserMenu::LabeliserMenu(const std::shared_ptr<Button>& emptyCurves, const std::shared_ptr<Button>& makeFirst,
		const std::shared_ptr<Button>& autoMode, const std::shared_ptr<Button>& labeliseMissingPoints, const std::shared_ptr<Button>& stop,
		const std::shared_ptr<TextLayer>& text, Window& window) :
		window(window), emptyCurvesBtn(emptyCurves), makeFirst(makeFirst), autoMode(autoMode), labeliseMissingPoints(labeliseMissingPoints), stop(
				stop), textLayer(text) {
}

std::shared_ptr<LabeliserMenu> LabeliserMenu::create(std::shared_ptr<SplitLayer>& splitLayerBottom,
		const std::shared_ptr<window::SplitLayer>& splitLayerPlot, const std::shared_ptr<Button>& validate,
		const std::shared_ptr<Button>& cancel, Window& window) {
	struct make_shared_enabler: public LabeliserMenu {
		make_shared_enabler(const std::shared_ptr<Button>& emptyCurves, const std::shared_ptr<Button>& makeFirst,
				const std::shared_ptr<Button>& autoMode, const std::shared_ptr<Button>& labeliseMissingPoints,
				const std::shared_ptr<Button>& stop, std::shared_ptr<TextLayer>& text, Window& window) :
				LabeliserMenu(emptyCurves, makeFirst, autoMode, labeliseMissingPoints, stop, text, window) {
		}
	};

	std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer> > > bottomMenu = std::make_shared<
			std::vector<std::shared_ptr<ConstrainedLayer> > >();
	std::shared_ptr<window::StakeLayer> menu = std::make_shared<window::StakeLayer>(Layer::NoBorders, bottomMenu);

	std::shared_ptr<Button> labeliseMissingPoints, autoMode, stop, makeFirst, emptyCurves;

	constexpr float textMargins = 10.f;

	std::shared_ptr<TextLayer> text;

	text = std::make_shared<TextLayer>(SERIALIZER->getFirstLabelisationText());

	makeFirst = std::make_shared<Button>(false, SERIALIZER->getFirstLabelisationButtonText(), 20);
	autoMode = std::make_shared<Button>(false, SERIALIZER->getAutoButtonText(), 20);
	labeliseMissingPoints = std::make_shared<Button>(false, SERIALIZER->getLabeliseButtonText(), 20);
	stop = std::make_shared<Button>(false, SERIALIZER->getStopButtonText(), 20, nullptr);
	emptyCurves = std::make_shared<Button>(false, SERIALIZER->getEmptyCurvesButtonText(), 20, nullptr);

	std::shared_ptr<LabeliserMenu> result = std::make_shared<make_shared_enabler>(emptyCurves, makeFirst, autoMode, labeliseMissingPoints,
			stop, text, window);

	labeliseMissingPoints->hide();
	labeliseMissingPoints->disable();
	emptyCurves->lockHided();
	autoMode->hide();
	stop->hide();

	result->exitAutomaticMode = true;

	stop->setCallBack([stop, result](float time) {
		result->exitAutomaticMode = true;
		stop->disable();
	});

	stop->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::Escape });

	emptyCurves->setCallBack([emptyCurves, result](float time) {
		emptyCurves->lockHided();

		result->emptyCurves();
	});

	autoMode->setCallBack([result](float time) {
		result->startAutomaticMode();
	});

	makeFirst->setCallBack([result](float time) {
		result->firstLabelisation();
	});

	labeliseMissingPoints->setCallBack([result](float time) {
		result->labelise();
	});

	std::shared_ptr<TabLayer> bottomTabLayer = std::make_shared<TabLayer>(TabLayer::Top, Layer::NoBorders,
			std::map<std::string, std::vector<std::shared_ptr<Layer> > > { { SERIALIZER->getHelpText(), {text}},
{	SERIALIZER->getXCurveText(), {window.get2dXPlotLayer()}}, {SERIALIZER->getYCurveText(), {window.get2dYPlotLayer()}}, {SERIALIZER->getZCurveText(), {
		window.get2dZPlotLayer()}}});

	bottomTabLayer->setActiveLayer(SERIALIZER->getHelpText(), Layer::NoBorders);

	std::shared_ptr<window::SplitLayer> splitLayerBottomMenu = std::make_shared<window::SplitLayer>(
			std::make_shared<ConstrainedLayer>(0.f, [menu](float x, float y, float width, float height) {
				return menu->getHeight(x, y, width, height);
			}, menu),
			std::make_shared<ConstrainedLayer>(0, [bottomTabLayer, textMargins, text](float x, float y, float width, float height) {
				if (bottomTabLayer->getActiveLayer() == text)
				return text->getHeight() + textMargins * 2.f + 20.f;

				return 200.f;
			}, std::make_shared<MarginLayer>(bottomTabLayer, textMargins, textMargins, textMargins, textMargins)), false, false, true,
			[](bool expanded) {}, [](bool expanded) {}, Layer::TopBorder);

	splitLayerBottom =
			std::make_shared<window::SplitLayer>(splitLayerPlot,
					std::make_shared<ConstrainedLayer>(0.f,
							[splitLayerBottomMenu](float x, float y, float width, float height) {
								float height_ = (splitLayerBottomMenu->isExpanded() ? splitLayerBottomMenu->getConstrainedLayer()->getHeight(x, y, width, height) : 0.f);
								return height_ + std::static_pointer_cast<ConstrainedLayer>(splitLayerBottomMenu->getUnConstrainedLayer())->
								getHeight(x, y + height_, width, height - height_);
							}, splitLayerBottomMenu), false, false, true);

	std::function<float(float, float, float, float)> buttonsHeight = [bottomMenu](float x, float y, float width, float height) {
		height = 0.f;
		for (auto layer : *bottomMenu)
		if (std::dynamic_pointer_cast<Button>(layer->getChild()) != nullptr) {
			if (std::static_pointer_cast<Button>(layer->getChild())->getHeight() > height)
			height = std::static_pointer_cast<Button>(layer->getChild())->getHeight();
		}

		return height + 5.f;
	};

	bottomMenu->push_back(std::make_shared<ConstrainedLayer>([makeFirst](float x, float y, float width, float height) {
		return makeFirst->getWidth();
	}, buttonsHeight, makeFirst));

	bottomMenu->push_back(std::make_shared<ConstrainedLayer>([labeliseMissingPoints](float x, float y, float width, float height) {
		return labeliseMissingPoints->getWidth();
	}, buttonsHeight, labeliseMissingPoints));

	bottomMenu->push_back(std::make_shared<ConstrainedLayer>([autoMode](float x, float y, float width, float height) {
		return autoMode->getWidth();
	}, buttonsHeight, autoMode));

	bottomMenu->push_back(std::make_shared<ConstrainedLayer>([stop](float x, float y, float width, float height) {
		return stop->getWidth();
	}, buttonsHeight, stop));

	bottomMenu->push_back(std::make_shared<ConstrainedLayer>([emptyCurves](float x, float y, float width, float height) {
		return emptyCurves->getWidth();
	}, buttonsHeight, emptyCurves));

	bottomMenu->push_back(std::make_shared<ConstrainedLayer>([validate](float x, float y, float width, float height) {
		return validate->getWidth();
	}, buttonsHeight, validate));

	bottomMenu->push_back(std::make_shared<ConstrainedLayer>([cancel](float x, float y, float width, float height) {
		return cancel->getWidth();
	}, buttonsHeight, cancel));

	return result;
}

void LabeliserMenu::setAutomaticMode(bool flag) {
	autoValidation = flag;

	if (flag) {
		disable();
		window.getController()->disable();
		window.getEditor()->disable();
		window.getSelector()->endSelection();
		window.getSelector()->disable();
		window.get3dPlotLayer()->disable();
	} else {
		enable();
		window.getController()->enable();
		window.getEditor()->enable();
		window.getSelector()->enable();
		window.get3dPlotLayer()->enable();
	}
}

bool LabeliserMenu::isInLabelisation() const {
	return inLabelisation;
}

void LabeliserMenu::abordLabelisation() {
	inLabelisation = false;
}

bool LabeliserMenu::isFirstLabelisation() const {
	return firstLabelisationFlag;
}

bool LabeliserMenu::isAutomaticModeEnable() const {
	return autoValidation;
}

void LabeliserMenu::stopAutomaticMode() {
	setAutomaticMode(false);
	{
		typedef window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetNbGapFrames> NbGapFrames;
		if (NbGapFrames::access(window, &Labeliser::getNbGapFrames)) {
			setText(SERIALIZER->getLabelisationText());
			autoMode->display();
		} else {
			setText(SERIALIZER->getAutoModeEndedText());
			disable();
			ended = true;
			emptyCurvesBtn->unlockHided();
			labeliseMissingPoints->lockHided();
		}
	}

	stop->enable();
	stop->hide();
}

void LabeliserMenu::startAutomaticMode() {
	setAutomaticMode();
	inLabelisation = true;
	setText(SERIALIZER->getAutoModeText());
	auto stopPtr = stop;
	stop->display();
	autoMode->hide();
	Window& window = this->window;
	LabeliserMenu& labeliserMenu = *this;
	exitAutomaticMode = false;

	std::shared_ptr<std::thread> autoModeThread;

	autoModeThread = std::make_shared<std::thread>([stopPtr, &window, &labeliserMenu]() {
		{
			std::lock_guard<std::mutex> lock (window.windowLock);
			window.getController()->goTo(0, true);
		}

		unsigned int lastFrame = 0;

		try {
			while (!labeliserMenu.exitAutomaticMode) {
				stopPtr->display();
				{
					std::lock_guard<std::mutex> lock (window.windowLock);

					window.getController()->goToNextLabelisationFrame(1.f, true);

					if (window.getController()->getCurrentFrame() == lastFrame)
					throw exception::labelisation::AutoModeEndException();

					lastFrame = window.getController()->getCurrentFrame();
				}

				{
					typedef window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::FrameLabelisation> FrameLabelisation;
					FrameLabelisation::access(window, &Labeliser::frameLabelisation);
				}
			}

		} catch (const exception::labelisation::AutoModeEndException& e) {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE);
			SetForegroundWindow(window.getSystemHandle());
		} catch (const std::exception& e) {
			std::cerr << "Error : fatal error in : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
			e.what();
		}

		{
			std::lock_guard<std::mutex> lock (window.windowLock);
			labeliserMenu.exitAutomaticMode = false;

			window.getLabeliserMenu()->stopAutomaticMode();
			window.dettachThread(std::this_thread::get_id());
		}
	});

	window.attachThread(autoModeThread);
}

void LabeliserMenu::emptyCurves() {
	window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::ClearCurves>::access(window, &Labeliser::clearCurves);

	applyChanges();
	window.getEditor()->updateCurves();
}

void LabeliserMenu::firstLabelisation() {
	inLabelisation = true;
	window.getController()->disable();
	makeFirst->disable();

	{
		unsigned int frame = window.getController()->getCurrentFrame();
		window.labeliserThreadAccessor([](const std::shared_ptr<Labeliser>& labeliser) {
			labeliser->frameLabelisation();
		});
	}
}

void LabeliserMenu::labelise() {
	inLabelisation = true;
	{
		unsigned int frame = window.getController()->getCurrentFrame();

		window.labeliserThreadAccessor([](const std::shared_ptr<Labeliser>& labeliser) {
			labeliser->frameLabelisation();
		});
	}

	labeliseMissingPoints->disable();
}

void LabeliserMenu::update(unsigned int frame) {
	if (window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::IsGapFrame>::access(window, &Labeliser::isGapFrame))
		labeliseMissingPoints->enable();
	else
		labeliseMissingPoints->disable();
}

void LabeliserMenu::disable() {
	labeliseMissingPoints->hide();
	makeFirst->hide();
	autoMode->hide();
	stop->hide();
	emptyCurvesBtn->hide();
}

void LabeliserMenu::enable() {
	if (ended) {
		emptyCurvesBtn->display();
		return;
	}

	if (isFirstLabelisation()) {
		makeFirst->display();
		makeFirst->enable();
		setText(SERIALIZER->getFirstLabelisationText());
	} else {
		labeliseMissingPoints->display();
		autoMode->display();
		setText(SERIALIZER->getLabelisationText());
	}
}

void LabeliserMenu::applyChanges() {
	inLabelisation = false;
	makeFirst->hide();
	labeliseMissingPoints->display();
	labeliseMissingPoints->disable();
	window.getController()->enable();

	firstLabelisationFlag = false;
}

void LabeliserMenu::setText(const std::string& text) {
	textLayer->setText(text);
}

const std::string& LabeliserMenu::getText() const {
	return textLayer->getText();
}

LabeliserMenu::~LabeliserMenu() {
}

} /* namespace window */
