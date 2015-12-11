/*
 * PopupLayer.cpp
 *
 *  Created on: 26 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "PopupLayer.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <exception>
#include <iostream>

#include "ConstrainedLayer.h"

namespace window {

PopupLayer::PopupLayer(const std::shared_ptr<Layer>& background, const std::shared_ptr<Layer>& popup, bool backgroundDisable) :
		background(background), Layer(Layer::NoBorders), popup(popup), backgroundDisable(backgroundDisable) {
}

PopupLayer::~PopupLayer() {
}

void PopupLayer::update() {
	popup->update();
}

std::shared_ptr<Layer> PopupLayer::getBackgroundLayer() const {
	return background;
}

void PopupLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	background->draw(window, x, y, width, height);
	if (backgroundDisable) {
		sf::RectangleShape rect(sf::Vector2f(width, height));
		rect.setFillColor(sf::Color(0, 0, 0, 50));
		rect.setOrigin(x, y);
		window->draw(rect);
	}

	popup->draw(window, x, y, width, height);
}

void PopupLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	popup->pollEvent(event, x, y, width, height);

	if (!backgroundDisable && !popup->grabEvent(event, x, y, width, height))
		background->pollEvent(event, x, y, width, height);
}

} /* namespace utils */
