/*
 * EmptyLayer.cpp
 *
 *  Created on: 10 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "EmptyLayer.h"

#include <cstdint>

namespace window {

EmptyLayer::EmptyLayer(const uint8_t& borders) :
		Layer(borders) {
}

EmptyLayer::~EmptyLayer() {
}

void EmptyLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	Layer::draw(window, x, y, width, height);
}

void EmptyLayer::update() {
}

void EmptyLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {

}

}
/* namespace window */
