/*
 * Window.cpp
 *
 *  Created on: 30 oct. 2015
 *      Author: Alexandre GARCIN
 */

#include "Window.cxx"
#include "Window.h"

#include <GL/glew.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <windef.h>
#include <winuser.h>
#include <algorithm>
#include <array>
#include <condition_variable>
#include <iostream>
#include <iterator>
#include <map>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <regex>

#include "../datas/Box.h"
#include "../exception/StopPollEventException.h"
#include "../Language/LanguageLoader.h"
#include "../utils/math/math.h"
#include "../utils/math/Vector.h"
#include "../utils/window/Cursor.h"
#include "Layer/content/Buttons/Button.h"
#include "Layer/content/Buttons/SplitBar.h"
#include "Layer/content/plot/box/ResizableBox.h"
#include "Layer/content/plot/line/Line.h"
#include "Layer/content/plot/point/exception/EmptyLabelDrawerFunctionException.h"
#include "Layer/content/plot/Plot2d.h"
#include "Layer/content/plot/Plot3d.h"
#include "Layer/content/popup/Legend.h"
#include "Layer/content/popup/MousePopup.h"
#include "Layer/content/popup/Popup.h"
#include "Layer/content/TextField.h"
#include "Layer/disposition/ConstrainedLayer.h"
#include "Layer/disposition/CenteredLayer.h"
#include "Layer/disposition/MarginLayer.h"
#include "Layer/disposition/PopupLayer.h"
#include "Layer/disposition/SplitLayer.h"
#include "Layer/disposition/StakeLayer.h"
#include "Layer/disposition/TabLayer.h"
#include "Layer/disposition/WindowLayer.h"
#include "Layer/EmptyLayer.h"
#include "Layer/Layer.h"
#include "observable/event/LabellisationEndedEvent.h"
#include "SplashScreenSaver.h"

std::string sceneLabelPrefix = "Marker_";
std::string sceneLabelUnlabelisedPrefix = "^";
char softwareName[] = "LabTools";

namespace window {

constexpr float Window::pannelWidth;
constexpr float Window::mouseMenuWidth;
sf::Color Window::sceneColor = sf::Color(0, 0, 255);
sf::Color Window::incompletePointColor = sf::Color(128, 0, 128);
sf::Color Window::outlierColor = sf::Color(0, 0, 0, 80);
sf::Color Window::labellisedColor = sf::Color(0, 255, 0, 80);
sf::Color Window::selectedPoint = sf::Color(0, 255, 255, 255);
sf::Color Window::errorPoint = sf::Color(0, 255, 255, 200);
sf::Color Window::newlyLabellisedLinkColor = sf::Color(255, 0, 255);
sf::Color Window::oldLabellisedLinkColor = sf::Color(0, 0, 0);
sf::Color Window::modelColor = sf::Color(255, 0, 0);
sf::Color Window::predictionSphereColor = sf::Color(100, 100, 100, 50);
sf::Color Window::newlySuppressedColorPoint = sf::Color(255, 0, 255, 120);
sf::Color Window::splitedColorPoint = sf::Color(50, 150, 255, 120);
sf::Color Window::selectColorPoint = sf::Color(255, 255, 0, 80);
sf::Color Window::selectColorLine = sf::Color(255, 0, 255, 130);
sf::Color Window::labelisedColorLine = sf::Color(0, 255, 0, 130);
sf::Color Window::lowProbaLinkColor = sf::Color(0, 255, 0);
sf::Color Window::labelisationBoxColor = Window::labellisedColor;
sf::Color Window::supressionBoxColor = Window::newlySuppressedColorPoint;
float Window::labellisedSize = 0.007f;
float Window::suppressedSize = 0.01f;
float Window::pointSize = 0.003f;

Window::Window(const std::shared_ptr<Labeliser>& labeliser,
		unsigned int nbFrames, double probaMin, unsigned int gapFramesSizeMin,
		double accelerationMax, double frameRate, unsigned int minWidth,
		unsigned int minHeight, unsigned int width, unsigned int height) :
		width(width), height(height), minHeight(minHeight), minWidth(minWidth), gapFramesSizeMin(
				gapFramesSizeMin), probaMin(probaMin), labeliser(labeliser), windowLock(), labeliserLock(), labeliserMemberLock(), accelerationMax(
				accelerationMax), frameRate(frameRate) {

	std::shared_ptr<window::SplitLayer> splitLayerPlot = std::make_shared<
			window::SplitLayer>(nullptr,
			std::make_shared<ConstrainedLayer>(0.f, 0.f,
					std::make_shared<window::EmptyLayer>(
							window::Layer::LeftBorder)), true, false, false);

	std::shared_ptr<window::SplitLayer> splitLayerBottom, splitLayerTopMenu;
	std::shared_ptr<Button> validate, cancel;

	createRightPannel(splitLayerPlot);
	createPlot();
	createBottomMenu(splitLayerBottom, splitLayerPlot, validate, cancel);
	createTopMenu(splitLayerBottom, splitLayerTopMenu, nbFrames, validate,
			cancel);

	layer = std::make_shared<WindowLayer>(splitLayerTopMenu);

	labeliser->addObserver(*this);
}

void Window::createBottomMenu(std::shared_ptr<SplitLayer>& splitLayerBottom,
		const std::shared_ptr<window::SplitLayer>& splitLayerPlot,
		std::shared_ptr<Button>& validate, std::shared_ptr<Button>& cancel) {
	validate = std::make_shared<Button>(-1.f, SERIALIZER->getValidateButtonText(), 20, nullptr);
	cancel = std::make_shared<Button>(-1.f, SERIALIZER->getCancelButtonText(), 20, nullptr);

	labeliserMenu = LabeliserMenu::create(splitLayerBottom, splitLayerPlot, validate, cancel, *this);
	validator = Validator::create(validate, cancel, *this, labeliserMenu);
}

const std::shared_ptr<Validator>& Window::getValidator() const {
	return validator;
}

const std::shared_ptr<LabeliserMenu>& Window::getLabeliserMenu() const {
	return labeliserMenu;
}

void Window::attachThread(const std::shared_ptr<std::thread>& thread) {
	threads[thread->get_id()] = thread;
}

void Window::dettachThread(std::thread::id threadId) {
	std::unordered_map<std::thread::id, std::shared_ptr<std::thread>>::iterator threadIt =
			threads.find(threadId);

	if (threadIt != threads.end())
		endedThreads.push(threadId);
	else
		std::cerr << "Error : fatal error occurred in file : " << __FILE__
				<< ", at line : " << __LINE__ << std::endl;
}

void Window::displayModelPoint() {
	displayModelPointFlag = true;

	for (const auto& point : getScenePoints()) {
		point->hideLabel();
	}
}

void Window::hideModelPoint() {
	displayModelPointFlag = false;

	if (displayLabelsFlag)
		for (const auto& point : getScenePoints()) {
			point->displayLabel();
		}
}

void Window::hidePredictionSpherePoints() {
	displayPredictionSpheresFlag = false;
}

void Window::displayPredictionSpherePoints() {
	displayPredictionSpheresFlag = true;
}

void Window::hideLabelisationBoxes() {
	displayLabelisationBoxesFlag = false;
}

void Window::displayLabelisationBoxes() {
	displayLabelisationBoxesFlag = true;
}

void Window::hideMarkerGroups() {
	displayMarkerGroupsFlag = false;
}

void Window::displayMarkerGroups() {
	displayMarkerGroupsFlag = true;
}

bool Window::isMarkerGroupsDisplayed() const {
	return displayMarkerGroupsFlag;
}

void Window::hideLabels() {
	displayLabelsFlag = false;
}

void Window::displayLabels() {
	displayLabelsFlag = true;
}

bool Window::isLabelsDisplayed() const {
	return displayLabelsFlag;
}

void Window::deleteEndedThreads() {
	while (!endedThreads.empty()) {
		threads[endedThreads.top()]->join();
		threads.erase(endedThreads.top());
		endedThreads.pop();
	}
}

std::shared_ptr<Labeliser> Window::getLabeliser() const {
	std::lock_guard<std::mutex> lock(
			const_cast<std::mutex&>(labeliserMemberLock));
	return labeliser;
}

HWND Window::getSystemHandle() const {
	if (window == nullptr)
		return nullptr;
	return window->getSystemHandle();
}

void Window::notifyModelSettingsChanged() {
	modelSettingsChanged = true;
}

void Window::createTopMenu(std::shared_ptr<SplitLayer>& splitLayerBottom,
		std::shared_ptr<SplitLayer>& splitLayerTopMenu, unsigned int nbFrames,
		const std::shared_ptr<Button>& validate,
		const std::shared_ptr<Button>& cancel) {
	controller = Controller::create(splitLayerBottom, splitLayerTopMenu,
			nbFrames, validate, cancel, *this, labeliserMenu);
}

const std::shared_ptr<Controller>& Window::getController() const {
	return controller;
}

void Window::createPlot() {
	plot2dX = std::make_shared<Plot2d>(*this);
	plot2dY = std::make_shared<Plot2d>(*this);
	plot2dZ = std::make_shared<Plot2d>(*this);
	plot3d = std::make_shared<window::Plot3d>(Vector3d( { .5, .5, 1.0 }) * 7.,
			Vector3d::center, 0.f, 0.f, 0.f, sf::Color::White, 0);
	std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer> > > content =
			std::make_shared<std::vector<std::shared_ptr<ConstrainedLayer> > >();

	std::shared_ptr<window::SplitBar> splitBarre = std::make_shared<
			window::SplitBar>();
	std::shared_ptr<window::Button> showModelPoint, hideModelPoint, showLegend,
			hideLegend, showPredictionSpheres, hidePredictionSpheres,
			hideLabels, showLabels, showLabelisationBoxes,
			hideLabelisationBoxes, addSuppressionBoxes, showGroups,
			addLabelisationBoxes, hideGroups, rotateDatas;

	showModelPoint = std::make_shared<window::Button>(true, SERIALIZER->getShowModelPointText(), 20);
	showPredictionSpheres = std::make_shared<window::Button>(true, SERIALIZER->getShowPredictionSpheresText(), 20);
	hidePredictionSpheres = std::make_shared<window::Button>(true, SERIALIZER->getHidePredictionSpheresText(), 20);
	hideModelPoint = std::make_shared<window::Button>(true, SERIALIZER->getHideModelPointsText(), 20);
	showLegend = std::make_shared<window::Button>(true, SERIALIZER->getShowLegendText(), 20);
	showLabels = std::make_shared<window::Button>(true, SERIALIZER->getShowLabelsText(), 20);
	hideLabels = std::make_shared<window::Button>(true, SERIALIZER->getHideLabelsText(), 20);
	hideLegend = std::make_shared<window::Button>(true, SERIALIZER->getHideLegendText(), 20);
	showLabelisationBoxes = std::make_shared<window::Button>(true, SERIALIZER->getShowLabelisationBoxesText(), 20);
	hideLabelisationBoxes = std::make_shared<window::Button>(true, SERIALIZER->getHideLabelisationBoxesText(), 20);
	addSuppressionBoxes = std::make_shared<window::Button>(true, SERIALIZER->getAddSuppressionBoxesText(), 20);
	addLabelisationBoxes = std::make_shared<window::Button>(true, SERIALIZER->getAddLabelisationBoxesText(), 20);
	showGroups = std::make_shared<window::Button>(true, SERIALIZER->getShowGroupsText(), 20);
	hideGroups = std::make_shared<window::Button>(true, SERIALIZER->getHideGroupsText(), 20);
	rotateDatas = std::make_shared<window::Button>(true, SERIALIZER->getRotateDatasText(), 20);

	showLegend->hide();
	showModelPoint->hide();
	hidePredictionSpheres->hide();
	showLabels->hide();
	hideLabels->hide();
	hideLabelisationBoxes->hide();
	hideGroups->hide();

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[showModelPoint](float x,
							float y, float width, float height) {
						return showModelPoint->getHeight();
					}, showModelPoint));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[hideModelPoint](float x,
							float y, float width, float height) {
						return hideModelPoint->getHeight();
					}, hideModelPoint));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[hideLabels](float x,
							float y, float width, float height) {
						return hideLabels->getHeight();
					}, hideLabels));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[showLabels](float x,
							float y, float width, float height) {
						return showLabels->getHeight();
					}, showLabels));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[splitBarre](float x,
							float y, float width, float height) {
						return splitBarre->getHeight();
					}, splitBarre));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[showPredictionSpheres](float x,
							float y, float width, float height) {
						return showPredictionSpheres->getHeight();
					}, showPredictionSpheres));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[hidePredictionSpheres](float x,
							float y, float width, float height) {
						return hidePredictionSpheres->getHeight();
					}, hidePredictionSpheres));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[showGroups](float x,
							float y, float width, float height) {
						return showGroups->getHeight();
					}, showGroups));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[hideGroups](float x,
							float y, float width, float height) {
						return hideGroups->getHeight();
					}, hideGroups));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[showLabelisationBoxes](float x,
							float y, float width, float height) {
						return showLabelisationBoxes->getHeight();
					}, showLabelisationBoxes));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[hideLabelisationBoxes](float x,
							float y, float width, float height) {
						return hideLabelisationBoxes->getHeight();
					}, hideLabelisationBoxes));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[splitBarre](float x,
							float y, float width, float height) {
						return splitBarre->getHeight();
					}, splitBarre));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[addSuppressionBoxes](float x,
							float y, float width, float height) {
						return addSuppressionBoxes->getHeight();
					}, addSuppressionBoxes));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[addLabelisationBoxes](float x,
							float y, float width, float height) {
						return addLabelisationBoxes->getHeight();
					}, addLabelisationBoxes));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[splitBarre](float x,
							float y, float width, float height) {
						return splitBarre->getHeight();
					}, splitBarre));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[showLegend](float x,
							float y, float width, float height) {
						return showLegend->getHeight();
					}, showLegend));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[hideLegend](float x,
							float y, float width, float height) {
						return hideLegend->getHeight();
					}, hideLegend));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[splitBarre](float x,
							float y, float width, float height) {
						return splitBarre->getHeight();
					}, splitBarre));

	content->push_back(
			std::make_shared<window::ConstrainedLayer>(Window::mouseMenuWidth,
					[rotateDatas](float x,
							float y, float width, float height) {
						return rotateDatas->getHeight();
					}, rotateDatas));

	std::shared_ptr<MousePopup> mousePopup = std::make_shared<MousePopup>(
			Window::mouseMenuWidth, content);

	hideLabels->setCallBack(
			[this, mousePopup, hideLabels, showLabels] (float timeStamp) {
				this->hideLabels();
				hideLabels->hide();
				mousePopup->disable();
				showLabels->display();

				for (const auto& point : getScenePoints()) {
					point->hideLabel();
				}
			});

	showLabels->setCallBack(
			[this, mousePopup, hideLabels, showLabels] (float timeStamp) {
				displayLabels();
				hideLabels->display();
				mousePopup->disable();
				showLabels->hide();

				for (const auto& point : getScenePoints()) {
					point->displayLabel();
				}
			});

	hidePredictionSpheres->setCallBack(
			[this, mousePopup, hidePredictionSpheres, showPredictionSpheres] (float timeStamp) {
				hidePredictionSpherePoints();
				hidePredictionSpheres->hide();
				mousePopup->disable();
				showPredictionSpheres->display();

				for (const auto& point : getPredictionSpherePoints()) {
					point->hide();
				}
			});

	showPredictionSpheres->setCallBack(
			[this, mousePopup, hidePredictionSpheres, showPredictionSpheres] (float timeStamp) {
				displayPredictionSpherePoints();
				hidePredictionSpheres->display();
				mousePopup->disable();
				showPredictionSpheres->hide();

				for (const auto& point : getPredictionSpherePoints()) {
					point->display();
				}
			});

	hideLabelisationBoxes->setCallBack(
			[this, mousePopup, hideLabelisationBoxes, showLabelisationBoxes] (float timeStamp) {
				this->hideLabelisationBoxes();
				hideLabelisationBoxes->hide();
				mousePopup->disable();
				showLabelisationBoxes->display();

				for (const auto& box : getLabelisationBoxes()) {
					box->hide();
				}
			});

	showGroups->setCallBack(
			[this, mousePopup, hideGroups, showGroups] (float timeStamp) {
				mousePopup->disable();
				showGroups->hide();
				hideGroups->display();
				displayMarkerGroups();

				for (const auto& point : getScenePoints())
				try {
					const auto& markerGroups =
					window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetMarkerGroups>::access(*this,
							&Labeliser::getMarkerGroups, point->getLabel());

					for (const auto& group : markerGroups)
					point->addGroup(false, *group.second);
				} catch (...) {
				}

				for (const auto& point : getModelPoints())
				try {
					const auto& markerGroups =
					window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetMarkerGroups>::access(*this,
							&Labeliser::getMarkerGroups, point->getLabel());

					for (const auto& group : markerGroups)
					point->addGroup(false, *group.second);
				} catch (...) {
				}
			});

	hideGroups->setCallBack(
			[this, mousePopup, hideGroups, showGroups] (float timeStamp) {
				mousePopup->disable();
				showGroups->display();
				hideGroups->hide();
				hideMarkerGroups();

				for (const auto& point : getScenePoints())
				try {
					point->clearGroups(false);
				} catch (...) {
				}

				for (const auto& point : getModelPoints())
				try {
					point->clearGroups(false);
				} catch (...) {
				}
			});

	showLabelisationBoxes->setCallBack(
			[this, mousePopup, hideLabelisationBoxes, showLabelisationBoxes] (float timeStamp) {
				displayLabelisationBoxes();
				hideLabelisationBoxes->display();
				mousePopup->disable();
				showLabelisationBoxes->hide();

				for (const auto& box : getLabelisationBoxes()) {
					box->display();
				}
			});

	hideModelPoint->setCallBack(
			[this, mousePopup, hideModelPoint, showModelPoint, showLabels, hideLabels] (float timeStamp) {
				this->hideModelPoint();

				hideModelPoint->hide();
				mousePopup->disable();
				showModelPoint->display();
				if (isLabelsDisplayed())
				hideLabels->display();
				else
				showLabels->display();

				for (const auto& point : getModelPoints()) {
					point->hide();

					for (const auto& line : point->getLines())
					line->hide();
				}
			});

	showModelPoint->setCallBack(
			[this, mousePopup, hideModelPoint, showModelPoint, hideLabels, showLabels] (float timeStamp) {
				displayModelPoint();

				hideModelPoint->display();
				mousePopup->disable();
				showModelPoint->hide();
				showLabels->hide();
				hideLabels->hide();

				for (const auto& point : getModelPoints()) {
					point->display();

					for (const auto& line : point->getLines())
					line->display();
				}
			});

	addSuppressionBoxes->setCallBack(
			[this, mousePopup, showLabelisationBoxes] (float timeStamp) {
				mousePopup->disable();

				addBoxToPlot(std::make_shared<utils::ResizableBox>( std::array<double, 6> {
									-0.2, -0.2, -0.2,
									0.2, 0.2, 0.2
								}, window::Window::supressionBoxColor, false, "outlier"), labBoxUUID.getUUID());

				editor->setInEdition();
				showLabelisationBoxes->trigger(1.f);
			});

	addLabelisationBoxes->setCallBack(
			[this, mousePopup, showLabelisationBoxes] (float timeStamp) {
				mousePopup->disable();

				createLabelisationBox(showLabelisationBoxes);
			});

	rotateDatas->setCallBack([this, mousePopup] (float timeStamp) {
		mousePopup->disable();

		this->rotateDatas();
	});

	plot3d->setSelector(selector);
	std::shared_ptr<Legend> legend = std::make_shared<Legend>(0.f, 0.f, 400.f,
			125.f);
	std::shared_ptr<PopupLayer> popupLayer = std::make_shared<PopupLayer>(
			plot3d, legend, false);

	showLegend->setCallBack(
			[legend, hideLegend, showLegend, mousePopup] (float timeStamp) {
				legend->display();
				showLegend->hide();
				hideLegend->display();
				mousePopup->disable();
			});

	hideLegend->setCallBack(
			[legend, hideLegend, showLegend, mousePopup] (float timeStamp) {
				legend->hide();
				showLegend->display();
				hideLegend->hide();
				mousePopup->disable();
			});

	splitLayerPlot->setUnConstrainedLayer(
			std::make_shared<window::PopupLayer>(popupLayer, mousePopup,
					false));
	initializePlot(false);
}

void Window::renameLabelisationBox(utils::ResizableBox& box) {
	constexpr float buttonWidth = 100.f;
	std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>> stack =
			std::make_shared<std::vector<std::shared_ptr<ConstrainedLayer>>>();
	std::shared_ptr<TextLayer> text = std::make_shared<TextLayer>("label : ",
			25, false);
	stack->push_back(
			std::make_shared<ConstrainedLayer>(text->getTextWidth(),
					text->getHeight(), text));

	std::shared_ptr<TextField> textField = std::make_shared<TextField>(
			box.getName());
	stack->push_back(
			std::make_shared<ConstrainedLayer>(200.f, 28.f, textField));

	std::shared_ptr<StakeLayer> textLayer = std::make_shared<StakeLayer>(
			Layer::NoBorders, stack);

	std::shared_ptr<ConstrainedLayer> content =
			std::make_shared<ConstrainedLayer>(300.f, 80.f,
					std::make_shared<CenteredLayer>(
							std::make_shared<ConstrainedLayer>(
									[textLayer](float x, float y, float width, float height) {
										return textLayer->getWidth(x, y, width, height);
									},
									[textLayer](float x, float y, float width, float height) {
										return textLayer->getHeight(x, y, width, height);
									}, textLayer)));

	std::function<void(float)> validationFunction =
			[this, textField, &box](float time) {
				if (textField->getText().size() == 0 || (textField->getText().size() > 7 && textField->getText().substr(0, 7) == "outlier"))
				return;

				editor->setInEdition();
				box.setName(textField->getText());

				if (textField->getText() == "outlier")
				box.setColor(window::Window::supressionBoxColor);
				else
				box.setColor(window::Window::labelisationBoxColor);

				getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			};

	std::shared_ptr<Button> validateButton = std::make_shared<Button>(-1.f,
			"Valider", 20, validationFunction);
	textField->setValidationFunc([validationFunction] () {
		validationFunction(1.f);
	});

	textField->setEscapeFunc(
			[this]() {
				getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			});

	std::shared_ptr<ConstrainedLayer> validateButtonCstr = std::make_shared<
			ConstrainedLayer>(
			[validateButton] (float x, float y, float width, float height) {
				return validateButton->getWidth();
			}, [validateButton](float x, float y, float width, float height) {
				return validateButton->getHeight();
			}, validateButton);

	std::shared_ptr<ConstrainedLayer> validateLayer = std::make_shared<
			ConstrainedLayer>(buttonWidth,
			[validateButton](float x, float y, float width, float height) {
				return validateButton->getHeight();
			}, std::make_shared<CenteredLayer>(validateButtonCstr));

	std::shared_ptr<SplitLayer> popupSplit = std::make_shared<SplitLayer>(
			content, validateLayer, false, false);

	std::shared_ptr<Popup> popup =
			std::make_shared<Popup>(
					std::make_shared<ConstrainedLayer>(
							[content, validateButton] (float x, float y, float width, float height) {
								return std::max(content->getWidth(x, y, width, height), validateButton->getWidth());
							},
							[content, validateButton] (float x, float y, float width, float height) {
								return content->getHeight(x, y, width, height) + validateButton->getHeight();
							}, popupSplit));

	getFirstLayer()->setChild(
			std::make_shared<PopupLayer>(getFirstLayer()->getChild(), popup));
}

void Window::rotateDatas() {
	if (validator->isEnable())
		return;

	constexpr float buttonWidth = 100.f;
	std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>> stack =
			std::make_shared<std::vector<std::shared_ptr<ConstrainedLayer>>>();
	std::shared_ptr<TextLayer> xText = std::make_shared<TextLayer>(" x axis : ",
			25, false);
	std::shared_ptr<TextLayer> yText = std::make_shared<TextLayer>(" y axis : ",
			25, false);
	std::shared_ptr<TextLayer> zText = std::make_shared<TextLayer>(" z axis : ",
			25, false);
	std::shared_ptr<TextLayer> angleText = std::make_shared<TextLayer>(
			" angle : ", 25, false);

	std::shared_ptr<TextField> xTextField = std::make_shared<TextField>("0.0");
	std::shared_ptr<TextField> yTextField = std::make_shared<TextField>("0.0");
	std::shared_ptr<TextField> zTextField = std::make_shared<TextField>("1.0");
	std::shared_ptr<TextField> angleTextField = std::make_shared<TextField>(
			"180.");

	stack->push_back(
			std::make_shared<ConstrainedLayer>(xText->getTextWidth(),
					xText->getHeight(), xText));
	stack->push_back(
			std::make_shared<ConstrainedLayer>(200.f, 28.f, xTextField));
	stack->push_back(
			std::make_shared<ConstrainedLayer>(yText->getTextWidth(),
					yText->getHeight(), yText));
	stack->push_back(
			std::make_shared<ConstrainedLayer>(200.f, 28.f, yTextField));
	stack->push_back(
			std::make_shared<ConstrainedLayer>(zText->getTextWidth(),
					zText->getHeight(), zText));
	stack->push_back(
			std::make_shared<ConstrainedLayer>(200.f, 28.f, zTextField));
	stack->push_back(
			std::make_shared<ConstrainedLayer>(angleText->getTextWidth(),
					angleText->getHeight(), angleText));
	stack->push_back(
			std::make_shared<ConstrainedLayer>(200.f, 28.f, angleTextField));

	std::shared_ptr<StakeLayer> textLayer = std::make_shared<StakeLayer>(
			Layer::NoBorders, stack);

	std::shared_ptr<ConstrainedLayer> content =
			std::make_shared<ConstrainedLayer>(300.f, 120.f,
					std::make_shared<CenteredLayer>(
							std::make_shared<ConstrainedLayer>(
									[textLayer](float x, float y, float width, float height) {
										return textLayer->getWidth(x, y, width, height);
									},
									[textLayer](float x, float y, float width, float height) {
										return textLayer->getHeight(x, y, width, height);
									}, textLayer)));

	std::function<void(float)> validationFunction =
			[this, xTextField, yTextField, zTextField, angleTextField](float time) {
				if (!std::regex_match(xTextField->getText().begin(), xTextField->getText().end(), std::regex("[0-9]*\\.?[0-9]*")) || xTextField->getText().size() == 0)
				return;

				if (!std::regex_match(yTextField->getText().begin(), yTextField->getText().end(), std::regex("[0-9]*\\.?[0-9]*")) || yTextField->getText().size() == 0)
				return;

				if (!std::regex_match(zTextField->getText().begin(), zTextField->getText().end(), std::regex("[0-9]*\\.?[0-9]*")) || zTextField->getText().size() == 0)
				return;

				if (!std::regex_match(angleTextField->getText().begin(), angleTextField->getText().end(), std::regex("[0-9]*\\.?[0-9]*")) || angleTextField->getText().size() == 0)
				return;

				::Vector3d axis;
				double angle;

				std::stringstream ss;
				ss << xTextField->getText();
				ss >> axis[0];

				ss.clear();

				ss << yTextField->getText();
				ss >> axis[1];

				ss.clear();

				ss << zTextField->getText();
				ss >> axis[2];

				ss.clear();

				ss << angleTextField->getText();
				ss >> angle;

				angle *= M_PI / 180.;

				window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::RotateDatas>::access(*this, &Labeliser::rotateDatas, axis, angle);

				this->getController()->enable();
				this->getEditor()->updateCurves();

				getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			};

	std::shared_ptr<Button> validateButton = std::make_shared<Button>(-1.f,
			"Valider", 20, validationFunction);
	xTextField->setValidationFunc([validationFunction] () {
		validationFunction(1.f);
	});

	yTextField->setValidationFunc([validationFunction] () {
		validationFunction(1.f);
	});

	zTextField->setValidationFunc([validationFunction] () {
		validationFunction(1.f);
	});

	angleTextField->setValidationFunc([validationFunction] () {
		validationFunction(1.f);
	});

	xTextField->setEscapeFunc(
			[this]() {
				getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			});

	yTextField->setEscapeFunc(
			[this]() {
				getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			});

	zTextField->setEscapeFunc(
			[this]() {
				getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			});

	angleTextField->setEscapeFunc(
			[this]() {
				getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			});

	std::shared_ptr<ConstrainedLayer> validateButtonCstr = std::make_shared<
			ConstrainedLayer>(
			[validateButton] (float x, float y, float width, float height) {
				return validateButton->getWidth();
			}, [validateButton](float x, float y, float width, float height) {
				return validateButton->getHeight();
			}, validateButton);

	std::shared_ptr<ConstrainedLayer> validateLayer = std::make_shared<
			ConstrainedLayer>(buttonWidth,
			[validateButton](float x, float y, float width, float height) {
				return validateButton->getHeight();
			}, std::make_shared<CenteredLayer>(validateButtonCstr));

	std::shared_ptr<SplitLayer> popupSplit = std::make_shared<SplitLayer>(
			content, validateLayer, false, false);

	std::shared_ptr<Popup> popup =
			std::make_shared<Popup>(
					std::make_shared<ConstrainedLayer>(
							[content, validateButton] (float x, float y, float width, float height) {
								return std::max(content->getWidth(x, y, width, height), validateButton->getWidth());
							},
							[content, validateButton] (float x, float y, float width, float height) {
								return content->getHeight(x, y, width, height) + validateButton->getHeight();
							}, popupSplit));

	getFirstLayer()->setChild(
			std::make_shared<PopupLayer>(getFirstLayer()->getChild(), popup));
}

void Window::createLabelisationBox(
		const std::shared_ptr<Button>& showLabelisationBoxes) {
	constexpr float buttonWidth = 100.f;
	std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>> stack =
			std::make_shared<std::vector<std::shared_ptr<ConstrainedLayer>>>();
	std::shared_ptr<TextLayer> text = std::make_shared<TextLayer>("label : ",
			25, false);
	stack->push_back(
			std::make_shared<ConstrainedLayer>(text->getTextWidth(),
					text->getHeight(), text));

	std::shared_ptr<TextField> textField = std::make_shared<TextField>();
	stack->push_back(
			std::make_shared<ConstrainedLayer>(200.f, 28.f, textField));

	std::shared_ptr<StakeLayer> textLayer = std::make_shared<StakeLayer>(
			Layer::NoBorders, stack);

	std::shared_ptr<ConstrainedLayer> content =
			std::make_shared<ConstrainedLayer>(300.f, 80.f,
					std::make_shared<CenteredLayer>(
							std::make_shared<ConstrainedLayer>(
									[textLayer](float x, float y, float width, float height) {
										return textLayer->getWidth(x, y, width, height);
									},
									[textLayer](float x, float y, float width, float height) {
										return textLayer->getHeight(x, y, width, height);
									}, textLayer)));

	std::function<void(float)> validationFunction =
			[this, showLabelisationBoxes, textField](float time) {
				if (textField->getText().size() == 0 || (textField->getText().size() > 7 && textField->getText().substr(0, 7) == "outlier"))
				return;

				addBoxToPlot(std::make_shared<utils::ResizableBox>( std::array<double, 6> {
									-0.2, -0.2, -0.2,
									0.2, 0.2, 0.2
								}, textField->getText().size() == 7 && textField->getText().substr(0, 7) == "outlier" ? window::Window::supressionBoxColor : window::Window::labelisationBoxColor, false, textField->getText()), labBoxUUID.getUUID());

				editor->setInEdition();
				showLabelisationBoxes->trigger(1.f);

				getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			};

	std::shared_ptr<Button> validateButton = std::make_shared<Button>(-1.f,
			"Valider", 20, validationFunction);
	textField->setValidationFunc([validationFunction] () {
		validationFunction(1.f);
	});

	textField->setEscapeFunc(
			[this]() {
				getFirstLayer()->setChild(std::static_pointer_cast<PopupLayer>(getFirstLayer()->getChild())->getBackgroundLayer());
				throw exception::StopPollEventException();
			});

	std::shared_ptr<ConstrainedLayer> validateButtonCstr = std::make_shared<
			ConstrainedLayer>(
			[validateButton] (float x, float y, float width, float height) {
				return validateButton->getWidth();
			}, [validateButton](float x, float y, float width, float height) {
				return validateButton->getHeight();
			}, validateButton);

	std::shared_ptr<ConstrainedLayer> validateLayer = std::make_shared<
			ConstrainedLayer>(buttonWidth,
			[validateButton](float x, float y, float width, float height) {
				return validateButton->getHeight();
			}, std::make_shared<CenteredLayer>(validateButtonCstr));

	std::shared_ptr<SplitLayer> popupSplit = std::make_shared<SplitLayer>(
			content, validateLayer, false, false);

	std::shared_ptr<Popup> popup =
			std::make_shared<Popup>(
					std::make_shared<ConstrainedLayer>(
							[content, validateButton] (float x, float y, float width, float height) {
								return std::max(content->getWidth(x, y, width, height), validateButton->getWidth());
							},
							[content, validateButton] (float x, float y, float width, float height) {
								return content->getHeight(x, y, width, height) + validateButton->getHeight();
							}, popupSplit));

	getFirstLayer()->setChild(
			std::make_shared<PopupLayer>(getFirstLayer()->getChild(), popup));
}

void Window::createRightPannel(
		std::shared_ptr<window::SplitLayer>& splitLayerPlot) {
	std::shared_ptr<window::SplitLayer> splitLayerButtonsRight;

	editor = Editor::create(splitLayerButtonsRight, *this);

	splitLayerButtonsRight->setBorders(window::Layer::LeftBorder);

	selector =
			point::Selector::create(*this, [splitLayerPlot]() {
				splitLayerPlot->expandSplit();
			}, [this, splitLayerPlot]() {
				splitLayerPlot->retractSplit();
				get2dXPlotLayer()->clear();
				get2dYPlotLayer()->clear();
				get2dZPlotLayer()->clear();
			},
					[this](const std::shared_ptr<utils::Point>& point, point::Selector& selector, bool withUpdate) {
						if (withUpdate)
						getEditor()->updateCurves();
					},
					[this](const std::shared_ptr<utils::Point>& point, point::Selector& selector, bool withUpdate) {
						if (withUpdate)
						getEditor()->updateCurves();
					}, [this](point::Selector& selector) {
						getEditor()->update();
					});

	splitLayerPlot->setEndCallBack(
			[splitLayerPlot, splitLayerButtonsRight, this](bool expanded) {
				if (expanded) {
					getEditor()->update();

					splitLayerPlot->setConstrainedLayer(std::make_shared<ConstrainedLayer>(Window::pannelWidth, 0.f, splitLayerButtonsRight));
				}
			});

	splitLayerPlot->setStartCallBack(
			[splitLayerPlot](bool expanded) {
				splitLayerPlot->setConstrainedLayer(std::make_shared<ConstrainedLayer>(Window::pannelWidth, 0.f, std::make_shared<window::EmptyLayer>(window::Layer::LeftBorder)));
			});

	this->splitLayerPlot = splitLayerPlot;
}

const std::shared_ptr<Editor>& Window::getEditor() const {
	return editor;
}

Window::~Window() {
}

unsigned int Window::getHeight() const {
	return height;
}

void Window::setHeight(unsigned int height) {
	this->height = height;
}

unsigned int Window::getWidth() const {
	return width;
}

void Window::setWidth(unsigned int width) {
	this->width = width;
}

void Window::clearPlot() {
	get3dPlotLayer()->clear();
	modelPoints.clear();
	scenePoints.clear();
	labelisationBoxes.clear();
}

void Window::addBoxToPlot(const std::shared_ptr<utils::Box>& box,
		unsigned long long int boxIndex) {
	plot3d->addBoxToPlot(box);

	if (displayLabelisationBoxesFlag)
		box->display();

	box->setCallBack(
			[this](const sf::Event& event, bool clicked, const Vector3d& beggin, const Vector3d& end) {
				if (event.type == sf::Event::MouseButtonReleased)
				if (clicked) {
					editor->setInEdition(true);
				}
			});

	if (std::dynamic_pointer_cast<utils::ResizableBox>(box)) {
		std::static_pointer_cast<utils::ResizableBox>(box)->setDeleteCallBack(
				[this](utils::ResizableBox& box) {
					editor->setInEdition(true);
				});

		std::static_pointer_cast<utils::ResizableBox>(box)->setRenameCallBack(
				[this](utils::ResizableBox& box) {
					renameLabelisationBox(box);
				});
	}

	box->setChangeCallback(
			[this, boxIndex, box]() {
				if (std::dynamic_pointer_cast<utils::ResizableBox>(box)) {
					if (!std::static_pointer_cast<utils::ResizableBox>(box)->isResized() && !std::static_pointer_cast<utils::ResizableBox>(box)->isDeleted() && !std::static_pointer_cast<utils::ResizableBox>(box)->isRenamed())
					return;

					if (std::static_pointer_cast<utils::ResizableBox>(box)->isDeleted())
					LabeliseAccessor<LabeliseAccessorTypes::RemoveLabelisationBox>::access(*this, &Labeliser::removeLabelisationBox, boxIndex);
					else
					LabeliseAccessor<LabeliseAccessorTypes::UpdateLabelisationBox>::access(*this, &Labeliser::updateLabelisationBox, boxIndex, box->getExtr1(), box->getExtr2(), box->getName());
					modelSettingsChanged = true;
				}
			});

	labelisationBoxes.push_back(box);
}

void Window::addPointToPlot(const std::shared_ptr<utils::Point>& point) {
	bool isModel = std::dynamic_pointer_cast<utils::ModelPoint>(point)
			!= nullptr;
	bool isScene = false;

	if (isModel) {
		if (std::find(modelPoints.begin(), modelPoints.end(), point)
				!= modelPoints.end())
			return;
	} else {
		isScene = std::dynamic_pointer_cast<utils::ScenePoint>(point)
				!= nullptr;

		if (isScene) {
			if (std::find(scenePoints.begin(), scenePoints.end(), point)
					!= scenePoints.end())
				return;

			if (point->getLabel().substr(0, 8) == "outlier_")
				point->setColor(outlierColor);
		} else if (std::find(predictionSpherePoints.begin(),
				predictionSpherePoints.end(), point)
				!= predictionSpherePoints.end())
			return;
	}

	if (displayMarkerGroupsFlag && (isModel || isScene)) {
		try {
			const auto& markerGroups =
					window::Window::LabeliseAccessor<
							window::Window::LabeliseAccessorTypes::GetMarkerGroups>::access(
							*this, &Labeliser::getMarkerGroups,
							point->getLabel());

			for (const auto& group : markerGroups)
				if (isModel)
					std::static_pointer_cast<utils::ModelPoint>(point)->addGroup(
							false, *group.second);
				else
					std::static_pointer_cast<utils::ScenePoint>(point)->addGroup(
							false, *group.second);
		} catch (...) {
		}
	}

	plot3d->addPointToPlot(point);

	if (isModel || isScene)
		point->setCallBack(
				std::make_shared<std::function<void(const sf::Event&, bool)>>(
						[this, point](const sf::Event& event, bool ctrlEnable) {
							if (event.type == sf::Event::MouseButtonReleased) {
								if (ctrlEnable)
								plot3d->getSelector()->triggerPoint(point);
								else {
									plot3d->getSelector()->unselectAll();
									plot3d->getSelector()->selectPoint(point);
								}
							} else if (event.type == sf::Event::MouseMoved) {
								utils::windows::Cursor::setCursor(utils::windows::Cursor::MOUSE);
							}
						}));

	if (isModel) {
		modelPoints.push_back(
				std::static_pointer_cast<utils::ModelPoint>(point));

		if (!displayModelPointFlag)
			point->hide();
	} else if (isScene) {
		scenePoints.push_back(
				std::static_pointer_cast<utils::ScenePoint>(point));

		std::shared_ptr<window::TextLayer> layer = std::make_shared<
				window::TextLayer>("error", 24);
		std::shared_ptr<std::string> label = std::make_shared<std::string>(
				"first@1");

		point->setLabelDrawer(
				[point, layer, label] (const std::shared_ptr<sf::RenderTexture>& renderTexture, float& width, float& height) {
					std::shared_ptr<utils::ScenePoint> point_ = std::static_pointer_cast<utils::ScenePoint>(point);

					if (point_->getLabel().size() > 6 && point_->getLabel().substr(0, 7) == "outlier")
					throw exception::EmptyLabelDrawerFunctionException();

					if (*label != point_->getLabel()) {
						layer->setText(point_->getLabel());
						*label = point_->getLabel();
					}

					if (label->substr(0, sceneLabelUnlabelisedPrefix.size()) == sceneLabelUnlabelisedPrefix || label->substr(0, 8) == "outlier_")
					throw exception::EmptyLabelDrawerFunctionException();

					constexpr float xMargin = 10.f;
					constexpr float yMargin = 5.f;

					layer->setWidthMax(width - 2.f * xMargin);
					float textWidth = layer->getTextWidth();

					if (textWidth + xMargin * 2.f < width)
					width = textWidth + xMargin * 2.f;

					height = layer->getHeight() + yMargin * 2.f;

					sf::RectangleShape rect;
					rect.setFillColor(sf::Color(255, 255, 255));
					rect.setOutlineThickness(-1.f);
					rect.setOutlineColor(sf::Color(0, 0, 0));
					rect.setSize(sf::Vector2f(width, height));
					renderTexture->draw(rect);

					layer->draw(renderTexture, xMargin, yMargin, width - 2.f * xMargin, height - 2.f * yMargin);
				});

		if (!displayModelPointFlag && displayLabelsFlag)
			std::static_pointer_cast<utils::ScenePoint>(point)->displayLabel();
	} else {
		predictionSpherePoints.push_back(
				std::static_pointer_cast<utils::SpherePoint>(point));

		if (!displayPredictionSpheresFlag)
			point->hide();
	}
}

std::shared_ptr<Plot3d> Window::get3dPlotLayer() {
	return plot3d;
}

std::shared_ptr<Plot2d> Window::get2dXPlotLayer() {
	return plot2dX;
}

std::shared_ptr<Plot2d> Window::get2dYPlotLayer() {
	return plot2dY;
}

std::shared_ptr<Plot2d> Window::get2dZPlotLayer() {
	return plot2dZ;
}

std::shared_ptr<window::SplitLayer> Window::getSplitPlotLayer() {
	return splitLayerPlot;
}

void Window::addLineToPlot(const std::shared_ptr<utils::Line>& line) {
	get3dPlotLayer()->addLineToPlot(line);

	if (!displayModelPointFlag)
		line->hide();
}

void Window::setMatches() {
	const std::vector<std::shared_ptr<utils::Point>>& points =
			plot3d->getPoints();

	for (unsigned int sceneIndex = 0; sceneIndex < nbScenePoints;
			++sceneIndex) {
		std::shared_ptr<utils::Point> scenePoint = points[sceneIndex];

		for (unsigned int modelIndex = 0; modelIndex < nbModelPoints;
				++modelIndex) {
			std::shared_ptr<utils::Point> modelPoint = points[nbScenePoints
					+ modelIndex];

			if (scenePoint->getLabel() == modelPoint->getLabel()) {
				std::shared_ptr<utils::Line> line = utils::Line::createLine(
						scenePoint, modelPoint, oldLabellisedLinkColor,
						0.0005f);
				addLineToPlot(line);
			}
		}
	}
}

void Window::initializePlot(bool withMatches) {
	clearPlot();

	vnl_matrix<double> inputScene;
	std::vector<std::string> inputSceneLabels;
	std::unordered_map<std::string, unsigned int> incompletePoints =
			std::unordered_map<std::string, unsigned int>();
	vnl_matrix<double> inputModel;
	std::vector<std::string> inputModelLabels;
	const std::unordered_map<std::string, std::tuple<::Vector3d, double>>& predictionSpheres =
			window::Window::LabeliseAccessor<
					window::Window::LabeliseAccessorTypes::GetCurrentPredictionPoints>::access(
					*this, &Labeliser::getCurrentPredictionPoints);
	const std::unordered_map<unsigned long long int,
			std::tuple<std::string, labeliser::Box>>& labelisationBoxes =
			window::Window::LabeliseAccessor<
					window::Window::LabeliseAccessorTypes::GetLabelisationBoxes>::access(
					*this, &Labeliser::getLabelisationBoxes);

	window::Window::LabeliseAccessor<
			window::Window::LabeliseAccessorTypes::GetInputSceneDatas>::access(
			*this, &Labeliser::getInputSceneDatas, inputScene, inputSceneLabels,
			incompletePoints);
	window::Window::LabeliseAccessor<
			window::Window::LabeliseAccessorTypes::GetInputModelDatas>::access(
			*this, &Labeliser::getInputModelDatas, inputModel,
			inputModelLabels);

	nbScenePoints = inputScene.rows();
	nbModelPoints = inputModel.rows();

	for (unsigned int i = 0; i < inputScene.rows(); ++i) {
		std::shared_ptr<utils::ScenePoint> point = std::make_shared<
				utils::ScenePoint>(inputScene(i, 0), inputScene(i, 1),
				inputScene(i, 2),
				inputSceneLabels[i].substr(0, 8) == "outlier_" ?
						outlierColor : sceneColor, 0.003f, inputSceneLabels[i]);

		addPointToPlot(point);
	}

	for (unsigned int i = 0; i < inputModel.rows(); ++i) {
		std::shared_ptr<utils::Point> point =
				std::make_shared<utils::ModelPoint>(inputModel(i, 0),
						inputModel(i, 1), inputModel(i, 2), modelColor, 0.003f,
						inputModelLabels[i]);

		try {
			incompletePoints.at(inputModelLabels[i]);
			point->setColor(window::Window::incompletePointColor);
		} catch (...) {
		}

		addPointToPlot(point);
	}

	for (const auto& it : predictionSpheres) {
		std::shared_ptr<utils::Point> point = std::make_shared<
				utils::SpherePoint>(std::get<0>(it.second),
				predictionSphereColor, std::get<1>(it.second));
		addPointToPlot(point);
	}

	for (const auto& it : labelisationBoxes) {
		auto box = std::make_shared<utils::ResizableBox>(std::get<1>(it.second),
				std::get<0>(it.second) == "outlier" ?
						window::Window::supressionBoxColor :
						window::Window::labelisationBoxColor, true,
				std::get<0>(it.second));
		addBoxToPlot(box, it.first);
	}

	labBoxUUID = LabeliseAccessor<
			LabeliseAccessorTypes::GetLabelisationBoxesUUID>::access(*this,
			&Labeliser::getLabelisationBoxesUUID);

	if (withMatches)
		setMatches();
}

std::shared_ptr<window::WindowLayer> &Window::getFirstLayer() {
	return layer;
}

const std::vector<std::shared_ptr<utils::ModelPoint> >& Window::getModelPoints() const {
	return modelPoints;
}

const std::vector<std::shared_ptr<utils::ScenePoint> >& Window::getScenePoints() const {
	return scenePoints;
}

const std::vector<std::shared_ptr<utils::SpherePoint> >& Window::getPredictionSpherePoints() const {
	return predictionSpherePoints;
}

const std::vector<std::shared_ptr<utils::Box> >& Window::getLabelisationBoxes() const {
	return labelisationBoxes;
}

const std::shared_ptr<point::Selector>& Window::getSelector() const {
	return selector;
}

unsigned int Window::getGapFramesSizeMin() const {
	return gapFramesSizeMin;
}

double Window::getAccelerationMaxErrors() const {
	return accelerationMax;
}

double Window::getFrameRate() const {
	return frameRate;
}

void Window::labeliserThreadAccessor(
		const std::function<void(const std::shared_ptr<Labeliser>&)>& thread) {
	Window& window = *this;

	std::shared_ptr<std::thread> currentThread =
			std::make_shared<std::thread>(
					[&window, thread]() {
						std::shared_ptr<Labeliser> labeliser = window.getLabeliser();

						try {
							std::lock_guard<std::mutex> lock (window.labeliserLock);
							thread(labeliser);
						} catch (const std::exception& e) {
							std::cerr << "Error : fatal error in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
							e.what();
						}

						window.dettachThread(std::this_thread::get_id());
					});

	attachThread(currentThread);
}

void Window::update(
		Observable<const std::shared_ptr<window::observable::Event>&>& observable,
		const std::shared_ptr<window::observable::Event>& arg) {
	std::lock_guard<std::mutex> lock(windowLock);
	labeliserLock.unlock();

	double probaMin = std::numeric_limits<double>::max();

	try {
		if (std::dynamic_pointer_cast<
				window::observable::LabellisationEndedEvent>(arg) != nullptr) {
			std::shared_ptr<window::observable::LabellisationEndedEvent> event =
					std::static_pointer_cast<
							window::observable::LabellisationEndedEvent>(arg);
			initializePlot(false);
			const std::vector<std::shared_ptr<utils::Point>>& points =
					plot3d->getPoints();

			for (const auto& corres : event->getCorespondances())
				for (const auto& point : points)
					if (point->getLabel() == corres.getSceneName()) {
						point->setLabel(corres.getModelName());

						if (point->getColor() == window::Window::sceneColor) {
							point->setColor(window::Window::labellisedColor);
							point->setSize(window::Window::labellisedSize);
						}

						probaMin = std::min(probaMin, corres.getProba());

						break;
					}

			setMatches();
			selector->endSelection();

			if (labeliserMenu->isFirstLabelisation())
				validator->start(SERIALIZER->getValidationFirstLabelisationText(), SERIALIZER->getLabelisationText());
				else if (!labeliserMenu->isAutomaticModeEnable())
				validator->start(SERIALIZER->getValidationLabelisationText(), SERIALIZER->getLabelisationText());
				else
				validator->start(SERIALIZER->getAutoModeText(), SERIALIZER->getAutoModeText(), probaMin <= this->probaMin); //bug on auto stop
			}
		} catch (const std::exception& e) {
			labeliserLock.lock();
			throw e;
		}

	labeliserLock.lock();
}

void Window::run(const std::string sceneFilePath) {
	window = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(this->width, this->height), softwareName,
			sf::Style::Default, sf::ContextSettings(24, 8, 8, 3, 3));

	window->setPosition(sf::Vector2i(0, 0));
	window->setVerticalSyncEnabled(true);
	window->setTitle("LabTools : " + sceneFilePath);
	ShowWindow(window->getSystemHandle(), SW_MINIMIZE);
	ShowWindow(window->getSystemHandle(), SW_SHOWMAXIMIZED);

	sf::Event event;

	window->setActive(true);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glDisable(GL_LIGHTING);

	while (window->isOpen()) {
		sf::Event event;
		{
			std::lock_guard<std::mutex> lock(windowLock);

			deleteEndedThreads();

			while (window->pollEvent(event)) {
				ShowCursor(true);
				utils::windows::Cursor::setCursor(
						utils::windows::Cursor::DEFAULT);

				if (event.type == sf::Event::Closed) {
					bool labelisationEnded = false;

					try {
						windowLock.unlock();
						window::Window::LabeliseAccessor<
								window::Window::LabeliseAccessorTypes::GetLostPointFrame>::access(
								*this, &Labeliser::getNextLostPointFrame);
						windowLock.lock();
					} catch (...) {
						try {
							windowLock.unlock();
							window::Window::LabeliseAccessor<
									window::Window::LabeliseAccessorTypes::GetLostPointFrame>::access(
									*this,
									&Labeliser::getPreviousLostPointFrame);
							windowLock.lock();
						} catch (...) {
							labelisationEnded = true;
						}
					}

					int result;

					if (!labelisationEnded)
						result = MessageBox(window->getSystemHandle(),
						SERIALIZER->getLabelisationNotEndedCore().c_str(),
						SERIALIZER->getLabelisationNotEndedTitle().c_str(), MB_YESNO);
						else
						result = IDYES;

					if (result == IDYES) {
						result = MessageBox(window->getSystemHandle(),
								SERIALIZER->getSaveBeforeExitCore().c_str(),
						SERIALIZER->getSaveBeforeExitTitle().c_str(), MB_YESNOCANCEL);

						bool closeFlag = true;

						if (result == IDYES) {
							windowLock.unlock();
							std::shared_ptr<std::string> modelSettingsFilePath =
							std::make_shared<std::string>(
							window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetDefaultModelSettingsPath>::access(
									*this, &Labeliser::getDefaultModelSettingsPath));
							windowLock.lock();

							std::shared_ptr<std::string> sceneFilePath = std::make_shared<std::string>();

							SplashScreenSaver splashScreenSaver(modelSettingsFilePath, sceneFilePath, modelSettingsChanged);
							{
								std::unique_lock<std::mutex> locker = std::unique_lock<std::mutex>(*splashScreenSaver.mutex);
								ShowWindow(window->getSystemHandle(), SW_HIDE);
								splashScreenSaver.condition_variable->wait(locker);
							}

							closeFlag = *splashScreenSaver.getProgramCloser();

							if (!*splashScreenSaver.getCloser()) {
								if (modelSettingsChanged && *modelSettingsFilePath != "") {
									windowLock.unlock();
									window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::SaveModelSettingsToFile>::access(
									*this, &Labeliser::saveModelSettingsToFile, window->getSystemHandle(), *modelSettingsFilePath);
									windowLock.lock();
								}
								windowLock.unlock();
								window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::SaveToFile>::access(*this,
								&Labeliser::saveToFile, *sceneFilePath, splashScreenSaver.getLoadingPercentage());
								windowLock.lock();

								/*todo retour std::unique_lock<std::mutex> locker = std::unique_lock<std::mutex>(*splashScreenSaver.mutex);
								 splashScreenSaver.condition_variable->wait(locker);*/

								closeFlag = true;
							}

						}

						if (result == IDCANCEL) {
							ShowWindow(window->getSystemHandle(), SW_SHOW);
							continue;
						}

						if (closeFlag)
						window->close();
						else
						ShowWindow(window->getSystemHandle(), SW_SHOW);
					}
				}

				if (event.type == sf::Event::Resized) {
					bool minReached = false;
					unsigned int width = event.size.width;
					unsigned int height = event.size.height;

					if (width < minWidth) {
						width = minWidth;
						minReached = true;
					}

					if (height < minHeight) {
						height = minHeight;
						minReached = true;
					}

					if (minReached)
						window->setSize(
								sf::Vector2u(this->width = width, this->height =
										height));

					sf::FloatRect visibleArea(0, 0, width, height);
					window->setView(sf::View(visibleArea));
				}

				try {
					layer->pollEvent(event, window);
				} catch (const exception::StopPollEventException& e) {
				} catch (...) {
					std::cerr << "Error: fatal error occured in file : "
							<< __FILE__ << ", at line : " << __LINE__
							<< std::endl;
				}
			}

			controller->update();
			layer->update();

			glDepthMask(GL_TRUE);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			glDepthMask(GL_FALSE);
			window->clear(sf::Color(255, 255, 255));
			layer->draw(window);
			window->display();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	{
		std::lock_guard<std::mutex> lock(windowLock);

		while (true) {
			if (threads.size() == 0)
				break;

			std::shared_ptr<std::thread> thread = threads.begin()->second;

			windowLock.unlock();
			labeliserMenu->exitAutomaticMode = true;
			validator->unPause();
			thread->join();
			windowLock.lock();

			threads.erase(threads.begin());
		}
	}
}
} /* namespace window */
