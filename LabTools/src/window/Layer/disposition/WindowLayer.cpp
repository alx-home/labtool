/*
 * FirstLayer.cpp
 *
 *  Created on: 9 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "WindowLayer.h"

#include <SFML/Graphics.hpp>

namespace window {

WindowLayer::WindowLayer(const std::shared_ptr<Layer>& child) :
		Layer(0x0), child(child) {
}

void WindowLayer::draw(const std::shared_ptr<sf::RenderWindow>& window) {
	draw(window, 0.f, 0.f, window->getSize().x, window->getSize().y);
}

void WindowLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	child->draw(window, x, y, width, height);
}

void WindowLayer::update() {
	child->update();
}

void WindowLayer::pollEvent(const sf::Event& event, const std::shared_ptr<sf::Window>& window) {
	pollEvent(event, 0.f, 0.f, window->getSize().x, window->getSize().y);
}

void WindowLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	child->pollEvent(event, x, y, width, height);
}

void WindowLayer::setChild(const std::shared_ptr<Layer>& child) {
	this->child = child;
}

const std::shared_ptr<Layer>& WindowLayer::getChild() const {
	return child;
}

WindowLayer::~WindowLayer() {
}

} /* namespace window */
