/*
 * Popup.cpp
 *
 *  Created on: 26 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "Popup.h"

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

Popup::Popup(const std::shared_ptr<ConstrainedLayer>& content) :
		content(content), Layer(Layer::NoBorders), boxContent(), selectionBox() {
	boxContent.setFillColor(sf::Color(255, 255, 255, 255));
	boxContent.setOutlineThickness(-ligneWidth);
	boxContent.setOutlineColor(sf::Color(0, 0, 0, 255));

	selectionBox.setFillColor(sf::Color(0, 0, 0, 40));
	selectionBox.setOutlineThickness(0);
}

Popup::~Popup() {
}

float Popup::getWidth(float x, float y, float width, float height) {
	return content->getWidth(x, y, width, height);
}

float Popup::getHeight(float x, float y, float width, float height) {
	return content->getHeight(x, y, width, height);
}

void Popup::update() {
	content->update();
}

void Popup::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {

	const float& popupWidth = getWidth(x, y, width, height);
	const float& popupHeight = getHeight(x, y, width, height);

	if (!initialised) {
		xPos = x + (width - popupWidth) / 2.0;
		yPos = y + (height - (popupHeight)) / 2.0;
		initialised = true;
	}

	if (xPos < 0)
		xPos = 0.f;

	if (yPos < margin)
		yPos = margin;

	if (xPos > x + width - popupWidth)
		xPos = x + width - popupWidth;

	if (yPos > y + height - popupHeight)
		yPos = y + height - popupHeight;

	if (lastWidth != popupWidth || lastHeight != popupHeight) {
		lastWidth = popupWidth;
		lastHeight = popupHeight;

		boxContent.setSize(sf::Vector2f(popupWidth + ligneWidth2, popupHeight + margin));
		selectionBox.setSize(sf::Vector2f(popupWidth, margin - ligneWidth));
	}

	boxContent.setPosition(xPos, yPos - margin);
	selectionBox.setPosition(xPos + ligneWidth, yPos + ligneWidth - margin);

	window->draw(boxContent);
	window->draw(selectionBox);

	exitButton.draw(window, xPos + popupWidth - margin, yPos - margin, margin, margin);

	content->draw(window, xPos, yPos, popupWidth, popupHeight);
}

void Popup::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	const float& popupWidth = getWidth(x, y, width, height);
	const float& popupHeight = getHeight(x, y, width, height);

	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left && (event.mouseButton.x > xPos) && (event.mouseButton.x < xPos + popupWidth)
				&& (event.mouseButton.y > yPos - margin) && (event.mouseButton.y < yPos)) {
			clicked = true;
			clickX = event.mouseButton.x;
			clickY = event.mouseButton.y;
			xInit = xPos;
			yInit = yPos;
		}
		break;

	case sf::Event::MouseButtonReleased:
		clicked = false;
		break;

	case sf::Event::MouseMoved:
		if (clicked) {
			xPos = event.mouseMove.x - clickX + xInit;
			yPos = event.mouseMove.y - clickY + yInit;
		}
		break;

	default:
		break;
	}

	content->pollEvent(event, xPos, yPos, popupWidth, popupHeight);

	sf::Event event2 = event;

	exitButton.setCallBack([popupWidth, popupHeight, event2, this](float) {
		const_cast<sf::Event::EventType&>(event2.type) = sf::Event::KeyReleased;
		const_cast<sf::Event::KeyEvent&>(event2.key) = sf::Event::KeyEvent {
			sf::Keyboard::Escape,
			sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt),
			sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl),
			sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift),
			sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem) || sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem)
		};

		content->pollEvent(event2, xPos, yPos, popupWidth, popupHeight);
	});

	exitButton.pollEvent(event, xPos + popupWidth - margin, yPos - margin, margin, margin);
}

} /* namespace window */
