/*
 * MarginLayer.cpp
 *
 *  Created on: 11 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "MarginLayer.h"

namespace window {

MarginLayer::MarginLayer(const std::shared_ptr<Layer>& child, float leftMargin, float rightMargin, float topMargin, float bottomMargin,
		uint8_t borders) :
		Layer(borders), child(child), leftMargin(leftMargin), rightMargin(rightMargin), bottomMargin(bottomMargin), topMargin(topMargin) {
}

MarginLayer::~MarginLayer() {
}

void MarginLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	child->draw(window, x + leftMargin, y + topMargin, width - (leftMargin + rightMargin), height - (topMargin + bottomMargin));
}

void MarginLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	child->pollEvent(event, x + leftMargin, y + topMargin, width - (leftMargin + rightMargin), height - (topMargin + bottomMargin));
}

void MarginLayer::update() {
}

}
/* namespace window */
