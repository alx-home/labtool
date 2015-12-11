/*
 * MousePopup.cpp
 *
 *  Created on: 26 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "MousePopup.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <exception>
#include <iostream>

#include "../../Layer.h"

namespace window {

MousePopup::MousePopup(float width, const std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>>& content, float xPos, float yPos, uint8_t borders) :
Layer(borders), xPos(xPos), yPos(yPos), popupWidth(width) {
	if (xPos != INFINITY && yPos != INFINITY)
	displayFlag = true;

	this->content = std::make_shared<StakeLayer>(Layer::BottomBorder, content);
}

MousePopup::~MousePopup() {
}

void MousePopup::update() {
	content->update();
}

void MousePopup::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	if (timeStamp < timeStampMax)
		++timeStamp;

	if (!displayFlag)
		return;

	if (xPos < 0)
		xPos = 0.f;

	if (yPos < 0)
		yPos = 0.f;

	if (xPos > x + width - popupWidth)
		xPos = x + width - popupWidth;

	float popupHeight = content->getHeight(x, y, popupWidth, height);

	if (yPos > y + height - popupHeight)
		yPos = y + height - popupHeight;

	content->draw(window, this->xPos, this->yPos, this->popupWidth, popupHeight);
}

float MousePopup::getXpos() const {
	return xPos;
}

float MousePopup::getYpos() const {
	return yPos;
}

void MousePopup::disable() {
	displayFlag = false;
}

bool MousePopup::grabEvent(const sf::Event& event, float x, float y, float width, float height) const {
	if (!displayFlag)
		return false;

	float popupHeight = content->getHeight(x, y, popupWidth, height);

	switch (event.type) {
	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased:
		return event.mouseButton.x > xPos && event.mouseButton.x < xPos + popupWidth && event.mouseButton.y > yPos
				&& event.mouseButton.y < yPos + popupHeight;

	default:
		return false;
	}
}

void MousePopup::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	if (xPos < 0)
		xPos = 0.f;

	if (yPos < 0)
		yPos = 0.f;

	if (xPos > x + width - popupWidth)
		xPos = x + width - popupWidth;

	float popupHeight = content->getHeight(x, y, popupWidth, height);

	if (yPos > y + height - popupHeight)
		yPos = y + height - popupHeight;

	if (displayFlag)
		content->pollEvent(event, this->xPos, this->yPos, this->popupWidth, popupHeight);

	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Button::Middle)
			displayFlag = false;
		else if (event.mouseButton.x < xPos || event.mouseButton.x > xPos + popupWidth || event.mouseButton.y < yPos
				|| event.mouseButton.y > yPos + popupHeight)
			if (event.mouseButton.button == sf::Mouse::Button::Left)
				displayFlag = false;
			else if (event.mouseButton.button == sf::Mouse::Button::Right)
				displayFlag = false;

		timeStamp = 0;

		break;

	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Button::Right && !displayFlag
				&& (event.mouseButton.x > x && event.mouseButton.x < x + width && event.mouseButton.y > y
						&& event.mouseButton.y < y + height))
			if (timeStamp < timeStampMax) {
				displayFlag = true;
				xPos = event.mouseButton.x;
				yPos = event.mouseButton.y;
			}
		break;

	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Return)
			displayFlag = false;
		break;

	case sf::Event::Resized:
		displayFlag = false;
		break;

	default:
		break;
	}
}

} /* namespace window */
