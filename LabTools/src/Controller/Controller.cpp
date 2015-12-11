/*
 * Controller.cpp
 *
 *  Created on: 4 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "Controller.h"

#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <string>
#include <vector>

#include "../labeliserMenu/LabeliserMenu.h"
#include "../labellise.hpp"
#include "../Language/LanguageLoader.h"
#include "../window/Layer/content/Buttons/Button.h"
#include "../window/Layer/content/TextLayer.h"
#include "../window/Layer/disposition/CenteredLayer.h"
#include "../window/Layer/disposition/ConstrainedLayer.h"
#include "../window/Layer/disposition/SplitLayer.h"
#include "../window/Layer/disposition/StakeLayer.h"
#include "../window/Layer/Layer.h"
#include "../window/Window.cxx"
#include "../window/Window.h"

namespace window {

Controller::Controller(const std::shared_ptr<CenteredLayer>& frameInfo, const std::shared_ptr<Button>& prevFrame,
		const std::shared_ptr<Button>& nextFrame, const std::shared_ptr<Button>& prevLabelisationFrame,
		const std::shared_ptr<Button>& nextLabelisationFrame, const std::shared_ptr<Button>& forwardPlay,
		const std::shared_ptr<Button>& backwardPlay, const std::shared_ptr<Button>& pause, unsigned int nbFrames, Window& window,
		const std::shared_ptr<LabeliserMenu>& labeliserMenu) :
		frameInfo(frameInfo), nextLabelisationFrame(nextLabelisationFrame), prevLabelisationFrame(prevLabelisationFrame), nextFrame(
				nextFrame), prevFrame(prevFrame), forwardPlay(forwardPlay), backwardPlay(backwardPlay), pause(pause), nbFrames(nbFrames), window(
				window), labeliserMenu(labeliserMenu) {
}

Controller::~Controller() {
}

std::shared_ptr<Controller> Controller::create(std::shared_ptr<SplitLayer>& splitLayerBottom,
		std::shared_ptr<SplitLayer>& splitLayerTopMenu, unsigned int nbFrames, const std::shared_ptr<Button>& validate,
		const std::shared_ptr<Button>& cancel, Window& window, const std::shared_ptr<LabeliserMenu>& labeliserMenu) {
	struct make_shared_enabler: public Controller {
		make_shared_enabler(const std::shared_ptr<CenteredLayer>& frameInfo, const std::shared_ptr<Button>& prevFrame,
				const std::shared_ptr<Button>& nextFrame, const std::shared_ptr<Button>& prevLabelisationFrame,
				const std::shared_ptr<Button>& nextLabelisationFrame, const std::shared_ptr<Button>& forwardPlay,
				const std::shared_ptr<Button>& backwardPlay, const std::shared_ptr<Button>& pause, unsigned int nbFrames, Window& window,
				const std::shared_ptr<LabeliserMenu>& labeliserMenu) :
				Controller(frameInfo, prevFrame, nextFrame, prevLabelisationFrame, nextLabelisationFrame, forwardPlay, backwardPlay, pause,
						nbFrames, window, labeliserMenu) {
		}
	};

	std::shared_ptr<CenteredLayer> topMenuCenter;
	std::shared_ptr<window::StakeLayer> menuLayer;

	std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer> > > topMenu = std::make_shared<
			std::vector<std::shared_ptr<ConstrainedLayer> > >();

	std::shared_ptr<Button> prevFrame, nextFrame, prevLabelisationFrame, nextLabelisationFrame, forwardPlay, backwardPlay, pause;
	std::shared_ptr<CenteredLayer> frameInfos;

	prevLabelisationFrame = std::make_shared<Button>(-1.f, "<<<", 20, nullptr, true);
	nextLabelisationFrame = std::make_shared<Button>(-1.f, ">>>", 20, nullptr, true);
	forwardPlay = std::make_shared<Button>(-1.f, ">", 20, nullptr, true);
	backwardPlay = std::make_shared<Button>(-1.f, "<", 20, nullptr, true);
	pause = std::make_shared<Button>(-1.f, "||", 20, nullptr, true);
	prevFrame = std::make_shared<Button>(-1.f, "<<", 20, nullptr, true);
	nextFrame = std::make_shared<Button>(-1.f, ">>", 20, nullptr, true);

	backwardPlay->disable();

	unsigned int nbScenePoints = window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetNbPoints>::access(window,
			&Labeliser::getNbScenePoints);

	unsigned int nbModelPoints = window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetNbPoints>::access(window,
			&Labeliser::getNbModelPoints);

	std::shared_ptr<TextLayer> text = std::make_shared<TextLayer>(
	SERIALIZER->getFrameNbr()+ "1/" + std::to_string(nbFrames) + "," + SERIALIZER->getNbPoints() + " : " + std::to_string(nbScenePoints) + " / "
	+ std::to_string(nbModelPoints) + " ", 20, false, TextLayer::CENTERED);

	frameInfos = std::make_shared<CenteredLayer>(std::make_shared<ConstrainedLayer>([text](float x, float y, float width, float height) {
		return text->getTextWidth();
	}, [text](float x, float y, float width, float height) {
		return text->getHeight();
	}, text));

	prevFrame->disable();
	prevLabelisationFrame->disable();
	pause->disable();

	std::shared_ptr<Controller> controller = std::make_shared<make_shared_enabler>(frameInfos, prevFrame, nextFrame, prevLabelisationFrame,
			nextLabelisationFrame, forwardPlay, backwardPlay, pause, nbFrames, window, labeliserMenu);

	forwardPlay->setCallBack([controller](float time) {
		controller->forwardRun();
	});

	backwardPlay->setCallBack([controller](float time) {
		controller->backwardRun();
	});

	pause->setCallBack([controller](float time) {
		controller->stop();
	});

	pause->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::Escape });

	nextFrame->setCallBack([controller](float time) {
		controller->stop();
		controller->goToNext(time);
	});

	prevFrame->setCallBack([controller](float time) {
		controller->stop();
		controller->goToPrev(time);
	});

	nextLabelisationFrame->setCallBack([controller](float time) {
		controller->stop();
		controller->goToNextLabelisationFrame(time);
	});

	prevLabelisationFrame->setCallBack([controller](float time) {
		controller->stop();
		controller->goToPrevLabelisationFrame(time);
	});

	std::function<float(float, float, float, float)> buttonsHeight = [topMenu](float x, float y, float width, float height) {
		height = 0.f;
		for (auto layer : *topMenu)
		if (std::dynamic_pointer_cast<Button>(layer->getChild()) != nullptr) {
			if (std::static_pointer_cast<Button>(layer->getChild())->getHeight() > height)
			height = std::static_pointer_cast<Button>(layer->getChild())->getHeight();
		}

		return height + 5.f;
	};

	topMenu->push_back(std::make_shared<ConstrainedLayer>([prevLabelisationFrame](float x, float y, float width, float height) {
		return prevLabelisationFrame->getWidth();
	}, buttonsHeight, prevLabelisationFrame));

	topMenu->push_back(std::make_shared<ConstrainedLayer>([prevFrame](float x, float y, float width, float height) {
		return prevFrame->getWidth();
	}, buttonsHeight, prevFrame));

	topMenu->push_back(std::make_shared<ConstrainedLayer>([backwardPlay](float x, float y, float width, float height) {
		return backwardPlay->getWidth();
	}, buttonsHeight, backwardPlay));

	topMenu->push_back(std::make_shared<ConstrainedLayer>([pause](float x, float y, float width, float height) {
		return pause->getWidth();
	}, buttonsHeight, pause));

	topMenu->push_back(std::make_shared<ConstrainedLayer>([forwardPlay](float x, float y, float width, float height) {
		return forwardPlay->getWidth();
	}, buttonsHeight, forwardPlay));

	topMenu->push_back(std::make_shared<ConstrainedLayer>([nextFrame](float x, float y, float width, float height) {
		return nextFrame->getWidth();
	}, buttonsHeight, nextFrame));

	topMenu->push_back(std::make_shared<ConstrainedLayer>([nextLabelisationFrame](float x, float y, float width, float height) {
		return nextLabelisationFrame->getWidth();
	}, buttonsHeight, nextLabelisationFrame));

	topMenu->push_back(std::make_shared<ConstrainedLayer>([validate](float x, float y, float width, float height) {
		return validate->getWidth();
	}, buttonsHeight, validate));

	topMenu->push_back(std::make_shared<ConstrainedLayer>([cancel](float x, float y, float width, float height) {
		return cancel->getWidth();
	}, buttonsHeight, cancel));

	menuLayer = std::make_shared<window::StakeLayer>(window::Layer::NoBorders, topMenu);

	topMenuCenter = std::make_shared<CenteredLayer>(
			std::make_shared<ConstrainedLayer>([menuLayer](float x, float y, float width, float height) {
				return menuLayer->getWidth(x, y, width, height);
			}, [menuLayer](float x, float y, float width, float height) {
				return menuLayer->getHeight(x, y, width, height);
			}, menuLayer), window::Layer::BottomBorder);

	auto frameInfoCenter = std::make_shared<CenteredLayer>(
			std::make_shared<ConstrainedLayer>([frameInfos](float x, float y, float width, float height) {
				return width;
			}, [frameInfos](float x, float y, float width, float height) {
				return frameInfos->getChild()->getHeight(x, y, width, height);
			}, frameInfos));

	auto splitLayerTopMenuCenter = std::make_shared<SplitLayer>(topMenuCenter,
			std::make_shared<ConstrainedLayer>([frameInfos](float x, float y, float width, float height) {
				return width;
			}, [frameInfos](float x, float y, float width, float height) {
				return frameInfos->getChild()->getHeight(x, y, width, height);
			}, frameInfoCenter), false);

	splitLayerTopMenu = std::make_shared<window::SplitLayer>(splitLayerBottom,
			std::make_shared<ConstrainedLayer>(0.f, [frameInfos, menuLayer](float x, float y, float width, float height) {
				return frameInfos->getChild()->getHeight(x, y, width, height) + menuLayer->getHeight(x, y, width, height);
			}, splitLayerTopMenuCenter), false, true, true);

	return controller;
}

void Controller::update() {
	if (running)
		if (forward)
			goToNext((speed == 1 ? 1 : 4.f) * speed);
		else
			goToPrev((speed == 1 ? 1 : 4.f) * speed);
}

void Controller::forwardRun() {
	running = true;
	pause->enable();
	backwardPlay->enable();
	backwardPlay->setText("<");

	if (forwardPlay->getText() == ">" || !forward)
		speed = 1;
	else
		++speed;

	forward = true;

	forwardPlay->setText(std::to_string(speed + 1) + ">");
}

void Controller::backwardRun() {
	running = true;
	pause->enable();
	forwardPlay->enable();
	forwardPlay->setText(">");

	if (backwardPlay->getText() == ">" || forward)
		speed = 1;
	else
		++speed;

	forward = false;

	backwardPlay->setText("<" + std::to_string(speed + 1));
}

void Controller::stop() {
	running = false;
	forward = true;
	forwardPlay->setText(">");
	backwardPlay->setText("<");
	pause->disable();
}

unsigned int Controller::getCurrentFrame() const {
	return currentFrame;
}

unsigned int Controller::getNbFrames() const {
	return nbFrames;
}

void Controller::goTo(unsigned int frame, bool bypassLock) {
	if (isDisable && !bypassLock)
		return;

	if (frame > currentFrame) {
		currentFrame = frame - 1;
		goToNext(1.f, bypassLock);
	} else if (frame != currentFrame) {
		currentFrame = frame + 1;
		goToPrev(1.f, bypassLock);
	}
}

void Controller::goToPrev(float time, bool bypassLock) {
	if (isDisable && !bypassLock)
		return;

	if (!running && !isDisable) {
		forwardPlay->enable();
		backwardPlay->enable();
	}

	float frame = currentFrame - time;

	if (!isDisable)
		nextFrame->enable();

	if (frame < 2.f) {
		prevFrame->disable();
		frame = 0;
		backwardPlay->disable();
		backwardPlay->setText("<");
	}

	currentFrame = frame;

	window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::SetCurrentFrame>::access(window, &Labeliser::setCurrentFrame,
			currentFrame);

	unsigned int nbScenePoints = window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetNbPoints>::access(window,
			&Labeliser::getNbScenePoints);

	unsigned int nbModelPoints = window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetNbPoints>::access(window,
			&Labeliser::getNbModelPoints);

	std::static_pointer_cast<TextLayer>(frameInfo->getChild()->getChild())->setText(
	SERIALIZER->getFrameNbr()+ std::to_string(currentFrame + 1) + "/" + std::to_string(nbFrames) + "," + SERIALIZER->getNbPoints() + " : "
	+ std::to_string(nbScenePoints) + " / " + std::to_string(nbModelPoints) + " ");
	if (!isDisable) {
		try {
			window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetLostPointFrame>::access(window,
					&Labeliser::getPreviousLostPointFrame);
			prevLabelisationFrame->enable();
		} catch (...) {
			if (modelFrame != UINT_MAX || currentFrame == 0)
				prevLabelisationFrame->disable();
			else
				prevLabelisationFrame->enable();
		}

		try {
			window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetLostPointFrame>::access(window,
					&Labeliser::getNextLostPointFrame);
			nextLabelisationFrame->enable();
		} catch (...) {
			nextLabelisationFrame->disable();
		}
	}

	window.initializePlot();
	window.getSelector()->updateSelection();
	labeliserMenu->update(currentFrame);
}

void Controller::goToNext(float time, bool bypassLock) {
	if (isDisable && !bypassLock)
		return;

	if (!running && !isDisable) {
		forwardPlay->enable();
		backwardPlay->enable();
	}

	float frame = currentFrame + time;
	if (!isDisable)
		prevFrame->enable();

	if (frame > nbFrames - 2) {
		stop();
		forwardPlay->disable();
		forwardPlay->setText(">");
		frame = nbFrames - 1;
		nextFrame->disable();
	}

	currentFrame = frame;

	window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::SetCurrentFrame>::access(window, &Labeliser::setCurrentFrame,
			currentFrame);

	unsigned int nbScenePoints = window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetNbPoints>::access(window,
			&Labeliser::getNbScenePoints);

	unsigned int nbModelPoints = window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetNbPoints>::access(window,
			&Labeliser::getNbModelPoints);

	std::static_pointer_cast<TextLayer>(frameInfo->getChild()->getChild())->setText(
	SERIALIZER->getFrameNbr()+ std::to_string(currentFrame + 1) + "/" + std::to_string(nbFrames) + "," + SERIALIZER->getNbPoints() + " : "
	+ std::to_string(nbScenePoints) + " / " + std::to_string(nbModelPoints) + " ");
	if (!isDisable) {
		try {
			window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetLostPointFrame>::access(window,
					&Labeliser::getPreviousLostPointFrame);
			prevLabelisationFrame->enable();
		} catch (...) {
			if (modelFrame != UINT_MAX || currentFrame == 0)
				prevLabelisationFrame->disable();
			else
				prevLabelisationFrame->enable();
		}

		try {
			window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetLostPointFrame>::access(window,
					&Labeliser::getNextLostPointFrame);
			nextLabelisationFrame->enable();
		} catch (...) {
			nextLabelisationFrame->disable();
		}
	}

	window.initializePlot();
	window.getSelector()->updateSelection();
	labeliserMenu->update(currentFrame);
}

unsigned int Controller::getModelFrame() const {
	return modelFrame;
}

void Controller::setModelFrame(unsigned int frame) {
	this->modelFrame = frame;
}

void Controller::goToPrevLabelisationFrame(float time, bool bypassLock) {
	unsigned int frame;

	try {
		frame = window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetLostPointFrame>::access(window,
				&Labeliser::getPreviousLostPointFrame);
	} catch (...) {
		if (modelFrame == UINT_MAX)
			frame = 0;
		else {
			prevLabelisationFrame->disable();
			return;
		}
	}

	goTo(frame, bypassLock);
}

void Controller::goToNextLabelisationFrame(float time, bool bypassLock) {
	unsigned int frame;

	try {
		frame = window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::GetLostPointFrame>::access(window,
				&Labeliser::getNextLostPointFrame);
	} catch (...) {
		nextLabelisationFrame->disable();
		return;
	}

	goTo(frame, bypassLock);
}

void Controller::disable() {
	isDisable = true;

	stop();
	forwardPlay->disable();
	backwardPlay->disable();
	nextLabelisationFrame->disable();
	prevLabelisationFrame->disable();
	nextFrame->disable();
	prevFrame->disable();
}

void Controller::enable() {
	isDisable = false;

	forwardPlay->enable();
	backwardPlay->enable();
	pause->disable();

	goToNext(0.f);
	goToPrev(0.f);
}

} /* namespace window */
