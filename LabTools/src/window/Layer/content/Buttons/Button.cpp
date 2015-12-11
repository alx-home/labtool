/*
 * Button.cpp
 *
 *  Created on: 12 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "Button.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <exception>
#include <iostream>

namespace window {

constexpr float Button::margin;

Button::Button(bool resizable, const std::string& text, unsigned int size, const std::function<void(float)>& callBack, bool maintenable) :
		TextLayer(text, size, resizable, TextLayer::CENTERED, sf::Color(50.f, 50.f, 50.f)), callBack(callBack), maintenable(maintenable), buttons1(), buttons2() {
	buttons2.setOutlineThickness(-1);
	buttons2.setOutlineColor(sf::Color(100, 100, 100, 255));
	buttons1.setOutlineColor(sf::Color(200, 200, 200, 255));
}

Button::~Button() {
}

void Button::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	if (hidded)
		return;

	buttons2.setSize(sf::Vector2f(width, height));
	buttons2.setPosition(x, y);

	buttons1.setSize(sf::Vector2f(width - 2.f, height - 2.f));
	buttons1.setPosition(x + 1.f, y + 1.f);

	if (lastState != state) {
		lastState = state;

		if (state == DISABLE)
			buttons2.setFillColor(sf::Color(200, 200, 200, 255));
		else if (state == DEFAULT)
			buttons2.setFillColor(sf::Color(240, 240, 240, 255));
		else if (state == MOUSEOVER)
			buttons2.setFillColor(sf::Color(230, 230, 230, 255));
		else
			buttons2.setFillColor(sf::Color(220, 220, 220, 255));
	}

	window->draw(buttons1);
	window->draw(buttons2);
	if (margin * 2. < width)
		TextLayer::draw(window, x + margin, y + (height - TextLayer::height) / 2.f, width - 2.f * margin, height);
	else
		TextLayer::draw(window, x + (width - TextLayer::getTextWidth()) / 2., y + (height - TextLayer::height) / 2.f, width, height);
}

void Button::update() {
	if (maintenable) {
		if (timestamp < maxTimeStamp)
			++timestamp;

		if (timestamp > minTimeStamp) {
			if (state == CLICKED)
				callBack(1.f);//exp((timestamp - minTimeStamp) / 20.0));
		}
	}
}

void Button::lockHided() {
	++lockers;
	hide();
}

void Button::unlockHided() {
	if (lockers > 0)
		--lockers;

	display();
}

void Button::trigger(float timestamp) {
	callBack(timestamp);
}

void Button::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	if (hidded || (state == DISABLE))
		return;

	if (event.type == sf::Event::MouseMoved)
		if (event.mouseMove.x < x + width && event.mouseMove.x > x && event.mouseMove.y < y + height && event.mouseMove.y > y)
			if (mouseClicked)
				state = CLICKED;
			else
				state = MOUSEOVER;
		else
			state = DEFAULT;
	else if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (event.mouseButton.x < x + width && event.mouseButton.x > x && event.mouseButton.y < y + height && event.mouseButton.y > y) {
				state = CLICKED;
				timestamp = 0;
			}

			mouseClicked = true;
		}
	} else if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left)
			if (event.mouseButton.x < x + width && event.mouseButton.x > x && event.mouseButton.y < y + height && event.mouseButton.y > y) {
				state = MOUSEOVER;
				std::clog << ("[event][button]\"" + TextLayer::text + "\", clicked") << std::endl;
				callBack(1);
			} else
				state = DEFAULT;

		mouseClicked = false;
	} else if (event.type == sf::Event::KeyPressed) {
		for (auto key : keyListeners)
			if (event.key.code == key.back()) {
				bool breaker = false;

				for (auto subKey : key)
					if (!sf::Keyboard::isKeyPressed(subKey)) {
						breaker = true;
						break;
					}

				if (!breaker)
					callBack(1);
				break;
			}
	}
}

void Button::disable() {
	state = DISABLE;
	mouseClicked = false;
}

void Button::enable() {
	if (state == DISABLE)
		state = DEFAULT;
}

void Button::display() {
	hidded = lockers != 0;
}

void Button::hide() {
	hidded = true;
}

bool Button::isHidded() {
	return hidded;
}

bool Button::isDisable() {
	return state == DISABLE;
}

float Button::getHeight() const {
	if (hidded)
		return 0;

	return TextLayer::getHeight();
}

float Button::getWidth() const {
	if (hidded)
		return 0;

	return TextLayer::getTextWidth() + 2.f * margin + 4.f;
}

void Button::setCallBack(const std::function<void(float time)>& callBack) {
	this->callBack = callBack;
}

void Button::addKeyListener(std::vector<sf::Keyboard::Key> key) {
	if (std::find(keyListeners.begin(), keyListeners.end(), key) == keyListeners.end())
		keyListeners.push_back(key);
}

const std::function<void(float time)>& Button::getCallBack() {
	return callBack;
}

} /* namespace window */
