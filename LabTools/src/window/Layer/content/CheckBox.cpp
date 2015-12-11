/*
 * CheckBox.cpp
 *
 *  Created on: 26 janv. 2016
 *      Author: alex
 */

#include "CheckBox.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <array>
#include <exception>
#include <iostream>

#include "../../../resources/classes/CheckTexture.h"

namespace sf {
class RenderTarget;
} /* namespace sf */

namespace window {

std::unique_ptr<sf::Texture> CheckBox::texture = nullptr;

CheckBox::CheckBox() :
		Layer(Layer::AllBorders) {
	if (!texture) {
		texture = std::move(std::unique_ptr<sf::Texture>(new sf::Texture()));

		if (!texture->loadFromMemory(&resources::CheckTexture::datas, resources::CheckTexture::datas.size())) {
			std::cerr << "Error: fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
			throw std::exception(); //todo exceptions
		}
	}
}

CheckBox::~CheckBox() {
}

void CheckBox::disable() {
	disableFlag = true;
}

void CheckBox::enable() {
	disableFlag = false;
}

void CheckBox::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	Layer::draw(window, x, y, width, height);

	sf::RectangleShape shape;

	shape.setOutlineThickness(-1.f);
	shape.setOutlineColor(sf::Color(0, 0, 0));
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));

	window->draw(shape);

	shape.move(1.f, 1.f);

	shape.setSize(sf::Vector2f(width - 1.f, height - 1.f));
	shape.setOutlineColor(sf::Color(0, 0, 0, 80));

	window->draw(shape);

	shape.setOutlineThickness(0.f);
	shape.setOutlineColor(sf::Color(0, 0, 0, 0));

	if (checked || inside) {
		shape.setTexture(&*texture);

		if (inside)
			if (checked)
				shape.setFillColor(sf::Color(0, 0, 0, 0));
			else
				shape.setFillColor(sf::Color(45, 145, 239, 80));
		else if (checked)
			shape.setFillColor(sf::Color(45, 145, 239));
		else
			shape.setFillColor(sf::Color(255, 255, 255, 255));

		window->draw(shape);
		shape.setOutlineThickness(0.f);
		shape.setFillColor(sf::Color(shape.getFillColor().r, shape.getFillColor().g, shape.getFillColor().b, 80));
		shape.move(1.f, 1.f);

		window->draw(shape);
	}

	if (disableFlag) {
		sf::RectangleShape shape2;
		shape2.setFillColor(sf::Color(0, 0, 0, 80));
		shape2.setPosition(x, y);
		shape2.setSize(sf::Vector2f(width, height));
		window->draw(shape2);
	}
}

void CheckBox::setCallback(const std::function<void(bool checked)>& callback) {
	this->callback = callback;
}

void CheckBox::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	if (disableFlag)
		return;

	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x > x && event.mouseButton.y > y
				&& event.mouseButton.x < x + width && event.mouseButton.y < y + height)
			check(!checked);
	} else if (event.type == sf::Event::MouseMoved)
		if (event.mouseMove.x > x && event.mouseMove.y > y && event.mouseMove.x < x + width && event.mouseMove.y < y + height)
			inside = true;
		else
			inside = false;
}

void CheckBox::update() {
}

void CheckBox::check(bool flag) {
	checked = flag;

	callback(checked);
}

bool CheckBox::isChecked() const {
	return checked;
}

bool CheckBox::grabEvent(const sf::Event& event, float x, float y, float width, float height) const {
	return false;
}

} /* namespace window */
