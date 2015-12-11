/*
 * Editor.cpp
 *
 *  Created on: 8 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "Editor.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vnl/vnl_matrix.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <regex>

#include "../exception/CatchedException.h"
#include "../exception/StopPollEventException.h"
#include "../GroupMarker.h"
#include "../labellise.hpp"
#include "../Language/LanguageLoader.h"
#include "../window/Layer/content/Buttons/Button.h"
#include "../window/Layer/content/Buttons/SplitBar.h"
#include "../window/Layer/content/plot/curve/Curve.h"
#include "../window/Layer/content/plot/line/Line.h"
#include "../window/Layer/content/plot/point/DefaultPoint.h"
#include "../window/Layer/content/plot/point/ModelPoint.h"
#include "../window/Layer/content/plot/point/ScenePoint.h"
#include "../window/Layer/content/plot/Plot2d.h"
#include "../window/Layer/content/popup/Popup.h"
#include "../window/Layer/content/TextField.h"
#include "../window/Layer/content/TextLayer.h"
#include "../window/Layer/disposition/CenteredLayer.h"
#include "../window/Layer/disposition/ConstrainedLayer.h"
#include "../window/Layer/disposition/PopupLayer.h"
#include "../window/Layer/disposition/SplitLayer.h"
#include "../window/Layer/disposition/StakeLayer.h"
#include "../window/Layer/disposition/WindowLayer.h"
#include "../window/Layer/Layer.h"
#include "../window/Window.cxx"
#include "../window/Window.h"
#include "events/CreateMarkerGroupEvent.h"
#include "events/EraseMarkerGroupEvent.h"

namespace window {

Editor::Editor(const std::shared_ptr<Button>& splitSelectedFrames, const std::shared_ptr<Button>& splitNextFrames,
		const std::shared_ptr<Button>& splitPreviousFrames, const std::shared_ptr<Button>& eraseMarker,
		const std::shared_ptr<Button>& renameMarker, const std::shared_ptr<Button>& linkMarkers,
		const std::shared_ptr<Button>& unlinkMarkers, const std::shared_ptr<Button>& setMarkerGroupMargin,
		const std::shared_ptr<Button>& addMarkersToGroups, const std::shared_ptr<Button>& removeMarkersFromGroups,
		const std::shared_ptr<Button>& removeMarkerGroups, const std::shared_ptr<Button>& createGroupFromMarkers,
		const std::shared_ptr<std::vector<std::shared_ptr<window::ConstrainedLayer> > >& stackLayers,
		const std::shared_ptr<window::SplitBar>& groupsSplitBar, Window& window) :
		window(window), unlinkMarkers(unlinkMarkers), linkMarkers(linkMarkers), eraseMarkers(eraseMarker), renameMarker(renameMarker), stackLayers(
				stackLayers), removeMarkersFromGroupsButton(removeMarkersFromGroups), removeMarkerGroupsButton(removeMarkerGroups), addMarkersToGroupsButton(
				addMarkersToGroups), createGroupFromMarkersButton(createGroupFromMarkers), groupsSplitBar(groupsSplitBar), splitSelectedFrames(
				splitSelectedFrames), splitPreviousFrames(splitPreviousFrames), splitNextFrames(splitNextFrames), setMarkerGroupMarginButton(
				setMarkerGroupMargin) {
}

std::shared_ptr<Editor> Editor::create(std::shared_ptr<window::SplitLayer>& splitLayerButtonsRight, Window& window) {
	struct make_shared_enabler: public Editor {
		make_shared_enabler(const std::shared_ptr<Button>& splitFrames, const std::shared_ptr<Button>& splitNextFrames,
				const std::shared_ptr<Button>& splitPreviousFrames, const std::shared_ptr<Button>& eraseMarkers,
				const std::shared_ptr<Button>& renameMarker, const std::shared_ptr<Button>& linkMarkers,
				const std::shared_ptr<Button>& unlinkMarkers, const std::shared_ptr<Button>& setMarkerGroupMargin,
				const std::shared_ptr<Button>& addMarkersToGroups, const std::shared_ptr<Button>& removeMarkerGroups,
				const std::shared_ptr<Button>& removeMarkersFromGroups, const std::shared_ptr<Button>& createGroupFromMarkers,
				const std::shared_ptr<std::vector<std::shared_ptr<window::ConstrainedLayer> > >& stackLayers,
				const std::shared_ptr<window::SplitBar>& groupsSplitBar, Window& window) :
				Editor(splitFrames, splitNextFrames, splitPreviousFrames, eraseMarkers, renameMarker, linkMarkers, unlinkMarkers,
						setMarkerGroupMargin, addMarkersToGroups, removeMarkerGroups, removeMarkersFromGroups, createGroupFromMarkers,
						stackLayers, groupsSplitBar, window) {
		}
	};

	std::shared_ptr<std::vector<std::shared_ptr<window::ConstrainedLayer> > > stackLayers = std::make_shared<
			std::vector<std::shared_ptr<window::ConstrainedLayer> > >();

	std::shared_ptr<window::SplitBar> splitBar = std::make_shared<window::SplitBar>();
	std::shared_ptr<window::SplitBar> groupSplitBar = std::make_shared<window::SplitBar>();

	std::shared_ptr<window::StakeLayer> pannel = std::make_shared<window::StakeLayer>(window::Layer::NoBorders, stackLayers);

	std::shared_ptr<window::Button> eraseMarkers, renameMarker, linkMarkers, unlinkMarkers, addMarkersToGroups, removeMarkersFromGroups,
			createGroupFromMarkers, removeMarkerGroups, splitSelectedFrames, splitPreviousFrames, splitNextFrames, setMarkerGroupMargin;

	std::shared_ptr<std::vector<std::shared_ptr<window::ConstrainedLayer> > > stackButtons = std::make_shared<
			std::vector<std::shared_ptr<window::ConstrainedLayer> > >();

	std::shared_ptr<window::StakeLayer> buttons = std::make_shared<window::StakeLayer>(window::Layer::NoBorders, stackButtons);

	std::shared_ptr<ConstrainedLayer> buttonsContainer = std::make_shared<ConstrainedLayer>(0.f,
			[buttons](float x, float y, float width, float height)->float {
				return buttons->getHeight(x, y, width, height);
			}, buttons);

	splitLayerButtonsRight = std::make_shared<window::SplitLayer>(pannel, buttonsContainer, false, true, true);

	eraseMarkers = std::make_shared<window::Button>(true, SERIALIZER->getSplitAllFrames(), 20);
	splitSelectedFrames = std::make_shared<window::Button>(true, SERIALIZER->getSplitFrames(), 20);
	splitPreviousFrames = std::make_shared<window::Button>(true, SERIALIZER->getSplitPreviousFrames(), 20);
	splitNextFrames = std::make_shared<window::Button>(true, SERIALIZER->getSplitNextFrames(), 20);
	unlinkMarkers = std::make_shared<window::Button>(true, SERIALIZER->getLinkSupression(), 20);
	linkMarkers = std::make_shared<window::Button>(true, SERIALIZER->getLinkMarkers(), 20);
	renameMarker = std::make_shared<window::Button>(true, SERIALIZER->getMarkerRename(), 20);
	addMarkersToGroups = std::make_shared<window::Button>(true, SERIALIZER->getAddMarkersToGroups(), 20);
	removeMarkersFromGroups = std::make_shared<window::Button>(true, SERIALIZER->getRemoveMarkersFromGroups(), 20);
	removeMarkerGroups = std::make_shared<window::Button>(true, SERIALIZER->getRemoveMarkerGroups(), 20);
	createGroupFromMarkers = std::make_shared<window::Button>(true, SERIALIZER->getCreateGroupFromMarkers(), 20);
	setMarkerGroupMargin = std::make_shared<window::Button>(true, SERIALIZER->getSetGroupMargin(), 20);

	std::shared_ptr<Editor> editor = std::make_shared<make_shared_enabler>(splitSelectedFrames, splitNextFrames, splitPreviousFrames,
			eraseMarkers, renameMarker, linkMarkers, unlinkMarkers, setMarkerGroupMargin, addMarkersToGroups, removeMarkerGroups,
			removeMarkersFromGroups, createGroupFromMarkers, stackLayers, groupSplitBar, window);

	renameMarker->setCallBack([editor](float time) {
		editor->renamePoint();
	});

	eraseMarkers->setCallBack([editor](float time) {
		editor->erasePoint();
	});

	splitSelectedFrames->setCallBack([editor](float time) {
		editor->splitPoints(Selection);
	});

	splitPreviousFrames->setCallBack([editor](float time) {
		editor->splitPoints(Previous);
	});

	splitNextFrames->setCallBack([editor](float time) {
		editor->splitPoints(Next);
	});

	eraseMarkers->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::Delete });

	unlinkMarkers->setCallBack([editor](float time) {
		editor->unlinkPoints();
	});

	setMarkerGroupMargin->setCallBack([editor](float time) {
		editor->setMarkerGroupMargin();
	});

	linkMarkers->setCallBack([editor](float time) {
		editor->linkPoints();
	});

	addMarkersToGroups->setCallBack([editor](float time) {
		editor->addMarkersToGroups();
	});

	removeMarkersFromGroups->setCallBack([editor](float time) {
		editor->removeMarkersFromGroups();
	});

	removeMarkerGroups->setCallBack([editor](float time) {
		editor->removeMarkerGroups();
	});

	createGroupFromMarkers->setCallBack([editor](float time) {
		editor->createGroupFromMarkers();
	});

	linkMarkers->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::LControl, sf::Keyboard::L });
	renameMarker->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::F2 });
	splitSelectedFrames->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::LControl, sf::Keyboard::S, sf::Keyboard::Down });
	splitNextFrames->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::LControl, sf::Keyboard::S, sf::Keyboard::Right });
	splitPreviousFrames->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::LControl, sf::Keyboard::S, sf::Keyboard::Left });

	stackButtons->push_back(std::make_shared<window::ConstrainedLayer>(Window::pannelWidth, [eraseMarkers](float x,
			float y, float width, float height) {
		return eraseMarkers->getHeight();
	}, eraseMarkers));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth, [renameMarker](float x, float y, float width, float height) {
				return renameMarker->getHeight();
			}, renameMarker));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth,
					[splitPreviousFrames](float x, float y, float width, float height) {
						return splitPreviousFrames->getHeight();
					}, splitPreviousFrames));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth,
					[splitSelectedFrames](float x, float y, float width, float height) {
						return splitSelectedFrames->getHeight();
					}, splitSelectedFrames));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth, [splitNextFrames](float x, float y, float width, float height) {
				return splitNextFrames->getHeight();
			}, splitNextFrames));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth, [splitBar](float x, float y, float width, float height) {
				return splitBar->getHeight();
			}, splitBar));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth, [linkMarkers](float x, float y, float width, float height) {
				return linkMarkers->getHeight();
			}, linkMarkers));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth, [unlinkMarkers](float x, float y, float width, float height) {
				return unlinkMarkers->getHeight();
			}, unlinkMarkers));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth, [splitBar](float x, float y, float width, float height) {
				return splitBar->getHeight();
			}, splitBar));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth,
					[setMarkerGroupMargin](float x, float y, float width, float height) {
						return setMarkerGroupMargin->getHeight();
					}, setMarkerGroupMargin));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth,
					[createGroupFromMarkers](float x, float y, float width, float height) {
						return createGroupFromMarkers->getHeight();
					}, createGroupFromMarkers));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth,
					[removeMarkerGroups](float x, float y, float width, float height) {
						return removeMarkerGroups->getHeight();
					}, removeMarkerGroups));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth,
					[addMarkersToGroups](float x, float y, float width, float height) {
						return addMarkersToGroups->getHeight();
					}, addMarkersToGroups));

	stackButtons->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::pannelWidth,
					[removeMarkersFromGroups](float x, float y, float width, float height) {
						return removeMarkersFromGroups->getHeight();
					}, removeMarkersFromGroups));

	stackButtons->push_back(std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth, [groupSplitBar](float x,
			float y, float width, float height) {
		return groupSplitBar->getHeight();
	}, groupSplitBar));

	return editor;
}

void Editor::disable() {
	unlinkMarkers->disable();
	setMarkerGroupMarginButton->disable();
	linkMarkers->disable();
	renameMarker->disable();
	eraseMarkers->disable();
	splitSelectedFrames->disable();
	splitNextFrames->disable();
	splitPreviousFrames->disable();
	addMarkersToGroupsButton->disable();
	createGroupFromMarkersButton->disable();
	removeMarkersFromGroupsButton->disable();
	removeMarkerGroupsButton->disable();

	isDisable = true;
}

void Editor::enable() {
	isDisable = false;

	update();
}

unsigned int Editor::getFirstSelection() const {
	return firstSelection;
}

unsigned int Editor::getLastSelection() const {
	return lastSelection;
}

void Editor::setFirstSelection(unsigned int firstSelection) {
	this->firstSelection = firstSelection;
}

void Editor::setLastSelection(unsigned int lastSelection) {
	this->lastSelection = lastSelection;
}

void Editor::updateCurves() {
	auto plotX = window.get2dXPlotLayer();
	auto plotY = window.get2dYPlotLayer();
	auto plotZ = window.get2dZPlotLayer();

	plotX->clear();
	plotY->clear();
	plotZ->clear();
	curveColors = ColorPicker();

	for (const auto& point : window.getSelector()->getSelectedPoints()) {
		vnl_matrix<double> inputScene;

		try {
			window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetInputSceneDatas2>::access(window,
					&Labeliser::getInputSceneDatas, point->getLabel(), inputScene);
		} catch (...) {
			continue;
		}

		auto color = curveColors.pickColor();

		auto curveX = std::make_shared<utils::Curve>(color, 1.5, utils::Curve::X, true, window.getGapFramesSizeMin(), true,
				window.getAccelerationMaxErrors(), window.getFrameRate());
		auto curveY = std::make_shared<utils::Curve>(color, 1.5, utils::Curve::Y, true, window.getGapFramesSizeMin(), true,
				window.getAccelerationMaxErrors(), window.getFrameRate());
		auto curveZ = std::make_shared<utils::Curve>(color, 1.5, utils::Curve::Z, true, window.getGapFramesSizeMin(), true,
				window.getAccelerationMaxErrors(), window.getFrameRate());

		for (unsigned int i = 0; i < inputScene.rows(); ++i) {
			auto coords = std::make_shared<utils::DefaultPoint>(inputScene(i, 0), inputScene(i, 1), inputScene(i, 2), color, 0.);
			coords->set2DColor(color);

			curveX->addPoint(coords);
			curveY->addPoint(coords);
			curveZ->addPoint(coords);
		}

		plotX->addCurveToPlot(curveX);
		plotY->addCurveToPlot(curveY);
		plotZ->addCurveToPlot(curveZ);
	}

	for (const auto& point : window.getSelector()->getSelectedNaNPoints()) {
		vnl_matrix<double> inputScene;

		try {
			window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetInputSceneDatas2>::access(window,
					&Labeliser::getInputSceneDatas, point.first, inputScene);
		} catch (...) {
			continue;
		}

		auto color = curveColors.pickColor();

		auto curveX = std::make_shared<utils::Curve>(color, 1.5, utils::Curve::X, true, window.getGapFramesSizeMin(), true,
				window.getAccelerationMaxErrors(), window.getFrameRate());
		auto curveY = std::make_shared<utils::Curve>(color, 1.5, utils::Curve::Y, true, window.getGapFramesSizeMin(), true,
				window.getAccelerationMaxErrors(), window.getFrameRate());
		auto curveZ = std::make_shared<utils::Curve>(color, 1.5, utils::Curve::Z, true, window.getGapFramesSizeMin(), true,
				window.getAccelerationMaxErrors(), window.getFrameRate());

		for (unsigned int i = 0; i < inputScene.rows(); ++i) {
			auto coords = std::make_shared<utils::DefaultPoint>(inputScene(i, 0), inputScene(i, 1), inputScene(i, 2), color, 0.);
			coords->set2DColor(color);

			curveX->addPoint(coords);
			curveY->addPoint(coords);
			curveZ->addPoint(coords);
		}

		plotX->addCurveToPlot(curveX);
		plotY->addCurveToPlot(curveY);
		plotZ->addCurveToPlot(curveZ);
	}
}

void Editor::updateLabelsText() {
	stackLayers->clear();

	for (const auto& point : window.getSelector()->getSelectedPoints()) {
		std::shared_ptr<window::TextLayer> layer = std::make_shared<window::TextLayer>(point->getLabel(), 25, window::TextLayer::CENTERED);
		layer->setWidthMax(Window::pannelWidth);
		layer->setMargin(5.f);
		stackLayers->push_back(std::make_shared<window::ConstrainedLayer>(Window::pannelWidth, layer->getHeight(), layer));
	}
}

void Editor::linkPoints() {
	if (window.getSelector()->getSelectedPoints().size() != 2) {
		std::cerr << "Error: fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
		return;
	}

	try {

		setInEdition();

		const std::shared_ptr<utils::Point>& pointA = window.getSelector()->getSelectedPoints()[0];
		const std::shared_ptr<utils::Point>& pointB = window.getSelector()->getSelectedPoints()[1];

		std::shared_ptr<utils::Point> modelPoint;
		std::shared_ptr<utils::Point> scenePoint;

		if (std::dynamic_pointer_cast<utils::ScenePoint>(pointA) != nullptr) {
			scenePoint = pointA;
			modelPoint = pointB;
		} else {
			scenePoint = pointB;
			modelPoint = pointA;
		}

		if (std::dynamic_pointer_cast<utils::ScenePoint>(modelPoint) != nullptr) {
			std::cerr << "Error: fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
			throw exception::CatchedException();
		}

		scenePoint->setLabel(modelPoint->getLabel());

		if (modelPoint->getLines().size() != 0)
			for (const auto& line : modelPoint->getLines()) {
				if (std::dynamic_pointer_cast<utils::ScenePoint>(line->getPointA()) != nullptr)
					line->getPointA()->setLabel("outlier");
				else
					line->getPointB()->setLabel("outlier");

				line->clear();
			}

		if (scenePoint->getLines().size() != 0)
			for (const auto& line : scenePoint->getLines())
				line->clear();

		window.addLineToPlot(utils::Line::createLine(pointA, pointB, window::Window::selectedPoint, 0.001f));
		update();
	} catch (const exception::CatchedException& e) {
	} catch (...) {
		std::cerr << "Error: fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
	}
}

void Editor::unlinkPoints() {
	setInEdition();

	for (const auto& point : window.getSelector()->getSelectedPoints()) {

		if (std::dynamic_pointer_cast<utils::ScenePoint>(point) != nullptr) {
			point->setLabel("outlier");

			for (const auto& line : point->getLines())
				line->clear();

		} else
			for (const auto& line : point->getLines()) {
				if (std::dynamic_pointer_cast<utils::ScenePoint>(line->getPointA()) == nullptr)
					line->getPointB()->setLabel("outlier");
				else
					line->getPointA()->setLabel("outlier");

				line->clear();
			}
	}

	update();
}

void Editor::setMarkerGroupMargin() {
	constexpr float buttonWidth = 100.f;
	std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>>stack = std::make_shared<
	std::vector<std::shared_ptr<ConstrainedLayer>>>();
	std::shared_ptr<TextLayer> text = std::make_shared<TextLayer>("marge : ", 25, false);
	stack->push_back(std::make_shared<ConstrainedLayer>(text->getTextWidth(), text->getHeight(), text));

	std::shared_ptr<TextField> textField = std::make_shared<TextField>("");
	stack->push_back(std::make_shared<ConstrainedLayer>(200.f, 28.f, textField));

	std::shared_ptr<StakeLayer> textLayer = std::make_shared<StakeLayer>(Layer::NoBorders, stack);

	std::shared_ptr<ConstrainedLayer> content = std::make_shared<ConstrainedLayer>(300.f, 80.f,
			std::make_shared<CenteredLayer>(std::make_shared<ConstrainedLayer>([textLayer](float x, float y, float width, float height) {
				return textLayer->getWidth(x, y, width, height);
			}, [textLayer](float x, float y, float width, float height) {
				return textLayer->getHeight(x, y, width, height);
			}, textLayer)));

	std::function<void(float)> validationFunction =
			[this, textField](float time) {
				if (textField->getText().size() == 0 || textField->getText() == "." || !std::regex_match(textField->getText().begin(), textField->getText().end(), std::regex("[0-9]*\\.?[0-9]*")))
				return;

				std::stringstream ss;
				ss << textField->getText();
				double margin;
				ss >> margin;

				setInEdition();

				std::unordered_map<unsigned long long int, GroupMarker> markerGroups = std::unordered_map<unsigned long long int, GroupMarker>();

				for (const auto& point : window.getSelector()->getSelectedPoints())
				if (std::dynamic_pointer_cast<utils::ModelPoint>(point))
				std::static_pointer_cast<utils::ModelPoint>(point)->setGroupMargin(margin);
				else
				for (const auto& group : std::static_pointer_cast<utils::ScenePoint>(point)->getGroups())
				std::static_pointer_cast<utils::ScenePoint>(point)->setGroupMargin(margin);

				window.getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(window.getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			};

	std::shared_ptr<Button> validateButton = std::make_shared<Button>(-1.f, "Valider", 20, validationFunction);
	textField->setValidationFunc([validationFunction] () {
		validationFunction(1.f);
	});

	textField->setEscapeFunc([this]() {
		window.getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(window.getFirstLayer()->getChild())->getBackgroundLayer());
		throw exception::StopPollEventException();
	});

	std::shared_ptr<ConstrainedLayer> validateButtonCstr = std::make_shared<ConstrainedLayer>(
			[validateButton] (float x, float y, float width, float height) {
				return validateButton->getWidth();
			}, [validateButton](float x, float y, float width, float height) {
				return validateButton->getHeight();
			}, validateButton);

	std::shared_ptr<ConstrainedLayer> validateLayer = std::make_shared<ConstrainedLayer>(buttonWidth,
			[validateButton](float x, float y, float width, float height) {
				return validateButton->getHeight();
			}, std::make_shared<CenteredLayer>(validateButtonCstr));

	std::shared_ptr<SplitLayer> popupSplit = std::make_shared<SplitLayer>(content, validateLayer, false, false);

	std::shared_ptr<Popup> popup = std::make_shared<Popup>(
			std::make_shared<ConstrainedLayer>([content, validateButton] (float x, float y, float width, float height) {
				return std::max(content->getWidth(x, y, width, height), validateButton->getWidth());
			}, [content, validateButton] (float x, float y, float width, float height) {
				return content->getHeight(x, y, width, height) + validateButton->getHeight();
			}, popupSplit));

	window.getFirstLayer()->setChild(std::make_shared<PopupLayer>(window.getFirstLayer()->getChild(), popup));
}

void Editor::addMarkersToGroups() {
	setInEdition();
	window.notifyModelSettingsChanged();

	bool model = false;
	std::unordered_map<unsigned long long int, GroupMarker> groups = std::unordered_map<unsigned long long int, GroupMarker>();

	for (const auto& point : window.getSelector()->getSelectedPoints())
		if (std::dynamic_pointer_cast<utils::ModelPoint>(point)) {
			model = true;
			for (const auto& group : std::static_pointer_cast<utils::ModelPoint>(point)->getGroups())
				groups.insert(group);
		} else
			for (const auto& group : std::static_pointer_cast<utils::ScenePoint>(point)->getGroups())
				groups.insert(group);

	if (model) {
		for (const auto& point : window.getSelector()->getSelectedPoints())
			if (std::static_pointer_cast<utils::ModelPoint>(point)->getGroups().size() == 0)
				for (auto& group : groups) {
					group.second.addMarker(point->getLabel(), 0.015);
					std::static_pointer_cast<utils::ModelPoint>(point)->addGroup(true, group.second, false);
				}
	} else
		for (const auto& point : window.getSelector()->getSelectedPoints())
			if (std::static_pointer_cast<utils::ScenePoint>(point)->getGroups().size() == 0)
				for (auto& group : groups) {
					group.second.addMarker(point->getLabel(), 0.015);
					std::static_pointer_cast<utils::ScenePoint>(point)->addGroup(true, group.second, false);
				}

	update();
}

void Editor::removeMarkersFromGroups() {
	setInEdition();
	window.notifyModelSettingsChanged();

	for (const auto& point : window.getSelector()->getSelectedPoints())
		if (std::dynamic_pointer_cast<utils::ModelPoint>(point))
			std::static_pointer_cast<utils::ModelPoint>(point)->clearGroups(true, false);
		else
			std::static_pointer_cast<utils::ScenePoint>(point)->clearGroups(true, false);

	update();
}

void Editor::removeMarkerGroups() {
	setInEdition();
	window.notifyModelSettingsChanged();

	std::unordered_map<unsigned long long int, bool> deletedGroups = std::unordered_map<unsigned long long int, bool>();

	for (const auto& point : window.getSelector()->getSelectedPoints())
		if (std::dynamic_pointer_cast<utils::ModelPoint>(point))
			for (const auto& group : std::static_pointer_cast<utils::ModelPoint>(point)->getGroups())
				deletedGroups[group.first] = true;
		else
			for (const auto& group : std::static_pointer_cast<utils::ScenePoint>(point)->getGroups())
				deletedGroups[group.first] = true;
	for (auto& point : window.getScenePoints()) {
		auto pointGroups = point->getGroups();

		for (const auto& pointGroup : pointGroups) {
			try {
				deletedGroups.at(pointGroup.first);
				point->removeGroup(true, pointGroup.second, false);
			} catch (...) {
			}
		}
	}

	for (auto& point : window.getModelPoints()) {
		auto pointGroups = point->getGroups();

		for (const auto& pointGroup : pointGroups) {
			try {
				deletedGroups.at(pointGroup.first);
				point->removeGroup(true, pointGroup.second, false);
			} catch (...) {
			}
		}
	}

	for (const auto& group : deletedGroups) {
		events.push(std::make_shared<utils::Editor::EraseMarkerGroupEvent>(group.first));
	}

	update();
}

void Editor::createGroupFromMarkers() {
	setInEdition();
	window.notifyModelSettingsChanged();
	GroupMarker group = GroupMarker(0.015f);

	for (const auto& point : window.getSelector()->getSelectedPoints())
		group.addMarker(point->getLabel(), 0.015f);

	for (const auto& point : window.getSelector()->getSelectedPoints())
		if (std::dynamic_pointer_cast<utils::ModelPoint>(point))
			std::static_pointer_cast<utils::ModelPoint>(point)->addGroup(true, group, false);
		else
			std::static_pointer_cast<utils::ScenePoint>(point)->addGroup(true, group, false);

	events.push(std::make_shared<utils::Editor::CreateMarkerGroupEvent>(group));

	update();
}

void Editor::erasePoint() {
	setInEdition();

	for (const auto& point : window.getSelector()->getSelectedPoints())
		if (std::dynamic_pointer_cast<utils::ScenePoint>(point) != nullptr)
			point->setLabel("outlier");

	update();
}

void Editor::splitPoints(SplitType type) {
	setInEdition();

	for (const auto& point : window.getSelector()->getSelectedPoints())
		if (std::dynamic_pointer_cast<utils::ScenePoint>(point) != nullptr) {
			if (point->getLabel().substr(0, 1) == "{") {
				unsigned int timeSize = point->getLabel().find_first_of("}") + 1;
				point->setLabel(point->getLabel().substr(timeSize, point->getLabel().size() - timeSize));
			}

			point->unlinkPoint();
			if (type == Previous)
				point->setLabel(
						std::string("{,") + std::to_string(window.getController()->getCurrentFrame()) + "}" + point->getLabel());
			else if (type == Next)
				point->setLabel(
						std::string("{") + std::to_string(window.getController()->getCurrentFrame() + 2) + ",}" + point->getLabel());
			else {
				double currentFrame = window.getController()->getCurrentFrame();

				if (firstSelection == std::numeric_limits<unsigned int>::max())
					firstSelection = currentFrame;

				if (lastSelection == std::numeric_limits<unsigned int>::max())
					lastSelection = currentFrame;

				if (firstSelection > lastSelection) {
					unsigned int tmp = firstSelection;
					firstSelection = lastSelection;
					lastSelection = tmp;
				}

				point->setLabel(
						std::string("{") + std::to_string(firstSelection + 1) + "," + std::to_string(lastSelection + 1) + "}" + point->getLabel());
			}
		}

	update();
}

void Editor::setInEdition(bool flag) {
	if (flag && !window.getValidator()->isEnable())
		try {
			window.getValidator()->start(SERIALIZER->getEditText(), window.getLabeliserMenu()->getText());
		} catch (...) {
			//todo exceptions
		}
	}

const std::queue<std::shared_ptr<utils::Editor::Event>>& Editor::getEvents() const {
	return events;
}

void Editor::applyEvents() {
	while (!events.empty()) {
		events.front()->apply(window);
		events.pop();
	}
}

Window& Editor::getWindow() const {
	return window;
}

void Editor::renamePoint() {
	if (window.getSelector()->getSelectedPoints().size() != 1) {
		std::cerr << "Error: fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
		return;
	}

	const std::shared_ptr<utils::Point>& point = window.getSelector()->getSelectedPoints()[0];

	constexpr float buttonWidth = 100.f;
	std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>>stack = std::make_shared<
	std::vector<std::shared_ptr<ConstrainedLayer>>>();
	std::shared_ptr<TextLayer> text = std::make_shared<TextLayer>("nom : ", 25, false);
	stack->push_back(std::make_shared<ConstrainedLayer>(text->getTextWidth(), text->getHeight(), text));

	std::shared_ptr<TextField> textField = std::make_shared<TextField>(point->getLabel());
	stack->push_back(std::make_shared<ConstrainedLayer>(200.f, 28.f, textField));

	std::shared_ptr<StakeLayer> textLayer = std::make_shared<StakeLayer>(Layer::NoBorders, stack);
	std::shared_ptr<ConstrainedLayer> content = std::make_shared<ConstrainedLayer>(300.f, 80.f,
			std::make_shared<CenteredLayer>(std::make_shared<ConstrainedLayer>([textLayer](float x, float y, float width, float height) {
				return textLayer->getWidth(x, y, width, height);
			}, [textLayer](float x, float y, float width, float height) {
				return textLayer->getHeight(x, y, width, height);
			}, textLayer)));

	Editor& editor = *this;

	std::function<void(float)> validationFunction =
			[&editor, point, textField](float time) {
				editor.setInEdition();

				const std::string& label = textField->getText();
				point->setLabel(label);

				for (const auto& line : point->getLines())
				line->clear();

				for (const auto& modelPoint : editor.getWindow().getModelPoints())
				if (modelPoint->getLabel() == label) {
					for (const auto& line : modelPoint->getLines()) {
						line->clear();

						std::shared_ptr<utils::ScenePoint> linePoint = std::static_pointer_cast<utils::ScenePoint>(line->getPointA());

						if (linePoint == nullptr)
						linePoint = std::static_pointer_cast<utils::ScenePoint>(line->getPointB());

						if (linePoint != point)
						linePoint->setLabel("outlier");
					}

					editor.getWindow().addLineToPlot(utils::Line::createLine(point, modelPoint, window::Window::selectedPoint, 0.001f));

					break;
				}

				editor.update();

				editor.getWindow().getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(editor.getWindow().getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			};

	std::shared_ptr<Button> validateButton = std::make_shared<Button>(-1.f, "Valider", 20, validationFunction);
	textField->setValidationFunc([validationFunction] () {
		validationFunction(1.f);
	});

	textField->setEscapeFunc(
			[&editor, point, textField]() {
				editor.getWindow().getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(editor.getWindow().getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			});

	std::shared_ptr<ConstrainedLayer> validateButtonCstr = std::make_shared<ConstrainedLayer>(
			[validateButton] (float x, float y, float width, float height) {
				return validateButton->getWidth();
			}, [validateButton](float x, float y, float width, float height) {
				return validateButton->getHeight();
			}, validateButton);

	std::shared_ptr<ConstrainedLayer> validateLayer = std::make_shared<ConstrainedLayer>(buttonWidth,
			[validateButton](float x, float y, float width, float height) {
				return validateButton->getHeight();
			}, std::make_shared<CenteredLayer>(validateButtonCstr));

	std::shared_ptr<SplitLayer> popupSplit = std::make_shared<SplitLayer>(content, validateLayer, false, false);

	std::shared_ptr<Popup> popup = std::make_shared<Popup>(
			std::make_shared<ConstrainedLayer>([content, validateButton] (float x, float y, float width, float height) {
				return std::max(content->getWidth(x, y, width, height), validateButton->getWidth());
			}, [content, validateButton] (float x, float y, float width, float height) {
				return content->getHeight(x, y, width, height) + validateButton->getHeight();
			}, popupSplit));

	window.getFirstLayer()->setChild(std::make_shared<PopupLayer>(window.getFirstLayer()->getChild(), popup));
}

void Editor::update() {
	if (isDisable)
		return;

	disable();
	isDisable = false;

	updateLabelsText();

	{
		bool flag = false;
		bool flag2 = true;

		for (const auto& point : window.getSelector()->getSelectedPoints())
			if (std::dynamic_pointer_cast<utils::ScenePoint>(point) != nullptr) {
				flag = true;

				if (point->getLabel() == "outlier") {
					flag2 = false;
					break;
				}
			}

		if (flag) {
			eraseMarkers->enable();

			if (flag2) {
				splitSelectedFrames->enable();
				splitNextFrames->enable();
				splitPreviousFrames->enable();
			}
		}
	}

	if (window.isMarkerGroupsDisplayed()) {
		createGroupFromMarkersButton->enable();
		addMarkersToGroupsButton->enable();
		removeMarkersFromGroupsButton->enable();
		removeMarkerGroupsButton->enable();
		setMarkerGroupMarginButton->enable();

		createGroupFromMarkersButton->display();
		addMarkersToGroupsButton->display();
		removeMarkersFromGroupsButton->display();
		removeMarkerGroupsButton->display();
		groupsSplitBar->display();
		setMarkerGroupMarginButton->display();

		for (auto point : window.getSelector()->getSelectedPoints())
			if (std::dynamic_pointer_cast<utils::ModelPoint>(point) == nullptr) {
				addMarkersToGroupsButton->disable();
				break;
			}

		if (addMarkersToGroupsButton->isDisable()) {
			addMarkersToGroupsButton->enable();

			for (auto point : window.getSelector()->getSelectedPoints())
				if (std::dynamic_pointer_cast<utils::ScenePoint>(point) == nullptr) {
					createGroupFromMarkersButton->disable();
					addMarkersToGroupsButton->disable();
					removeMarkersFromGroupsButton->disable();
					removeMarkerGroupsButton->disable();
					break;
				}
		}

		if (window.getSelector()->getSelectedPoints().size() < 4)
			createGroupFromMarkersButton->disable();

		if (!addMarkersToGroupsButton->isDisable()) {
			addMarkersToGroupsButton->disable();
			removeMarkersFromGroupsButton->disable();
			removeMarkerGroupsButton->disable();

			auto containPointWithoutGroups = false;

			for (auto point : window.getSelector()->getSelectedPoints())
				if (std::dynamic_pointer_cast<utils::ModelPoint>(point)) {
					if (std::static_pointer_cast<utils::ModelPoint>(point)->getGroups().size() != 0) {
						addMarkersToGroupsButton->enable();
						removeMarkersFromGroupsButton->enable();
						removeMarkerGroupsButton->enable();
					} else {
						setMarkerGroupMarginButton->disable();

						if (containPointWithoutGroups)
							break;

						containPointWithoutGroups = true;
					}
				} else if (std::dynamic_pointer_cast<utils::ScenePoint>(point)) {
					if (std::static_pointer_cast<utils::ScenePoint>(point)->getGroups().size() != 0) {
						addMarkersToGroupsButton->enable();
						removeMarkersFromGroupsButton->enable();
						removeMarkerGroupsButton->enable();
					} else {
						setMarkerGroupMarginButton->disable();

						if (containPointWithoutGroups)
							break;

						containPointWithoutGroups = true;
					}
				}

			if (!addMarkersToGroupsButton->isDisable() && !containPointWithoutGroups)
				addMarkersToGroupsButton->disable();
		}
	} else {
		createGroupFromMarkersButton->hide();
		addMarkersToGroupsButton->hide();
		removeMarkersFromGroupsButton->hide();
		removeMarkerGroupsButton->hide();
		groupsSplitBar->hide();
		setMarkerGroupMarginButton->hide();
	}

	{
		std::shared_ptr<std::vector<std::shared_ptr<utils::Point> > > linkedPoints = std::make_shared<
				std::vector<std::shared_ptr<utils::Point> > >();

		for (auto point : window.getSelector()->getSelectedPoints()) {
			if (point->getLines().size() != 0)
				linkedPoints->push_back(point);
		}

		if (linkedPoints->size()) {
			unlinkMarkers->enable();
		}
	}

	if (window.getSelector()->getSelectedPoints().size() == 2) {
		std::shared_ptr<utils::Point> pointA;
		std::shared_ptr<utils::Point> pointB;

		bool flag = true;

		for (auto line : window.getSelector()->getSelectedPoints()[1]->getLines())
			if (line->getPointA() == window.getSelector()->getSelectedPoints()[0]
					|| line->getPointB() == window.getSelector()->getSelectedPoints()[0])
				flag = false;

		pointA = window.getSelector()->getSelectedPoints()[0];
		pointB = window.getSelector()->getSelectedPoints()[1];

		if (std::dynamic_pointer_cast<utils::ScenePoint>(pointA) != nullptr
				&& std::dynamic_pointer_cast<utils::ScenePoint>(pointB) != nullptr)
			flag = false;
		if (std::dynamic_pointer_cast<utils::ScenePoint>(pointA) == nullptr
				&& std::dynamic_pointer_cast<utils::ScenePoint>(pointB) == nullptr)
			flag = false;

		if (flag) {
			linkMarkers->enable();
		}
	} else if ((window.getSelector()->getSelectedPoints().size() == 1)
			&& (std::dynamic_pointer_cast<utils::ScenePoint>(window.getSelector()->getSelectedPoints().front()) != nullptr)) {
		renameMarker->enable();

		std::shared_ptr<utils::Point> point = window.getSelector()->getSelectedPoints().front();
	}
}

Editor::~Editor() {
}

} /* namespace window */
