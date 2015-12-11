/*
 * ScrollLayer.cpp
 *
 *  Created on: 11 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "ScrollLayer.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "ConstrainedLayer.h"

namespace window {

ScrollLayer::ScrollLayer(const std::shared_ptr<ConstrainedLayer>& child, Disposition disposition, uint8_t borders) :
		Layer(borders), child(child), disposition(disposition) {
}

ScrollLayer::~ScrollLayer() {
}

void ScrollLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	if (disposition & (Left | Right)) {
		if (height >= child->getHeight(x, y, width, height))
			child->draw(window, x, y, width, height);
		else {
			double delta = height - child->getHeight(x, y, width, height);

			child->draw(window, x, y + delta * posPercentage, width, height);

			if (disposition & Left) {
				sf::RectangleShape rec(sf::Vector2f(2., height * (1. - delta) - 6.));
				rec.setPosition(x + 4., y + 4.);
				rec.setFillColor(sf::Color(0, 0, 255, 200));
			}
		}
	}
}

void ScrollLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	child->pollEvent(event, x, y, width, height);
}

void ScrollLayer::update() {
}

}
/* namespace window */
