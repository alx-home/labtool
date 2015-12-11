/*
 * ConstrainedLayer.cpp
 *
 *  Created on: 12 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "ConstrainedLayer.h"

#include <functional>

namespace window {

ConstrainedLayer::ConstrainedLayer(float width, float height, const std::shared_ptr<Layer>& layer) :
		Layer(Layer::NoBorders), child(layer), widthConstraint([width](float x, float y, float width_, float height) {return width;}), heightConstraint(
				[height](float x, float y, float width, float height_) {return height;}) {
}

ConstrainedLayer::ConstrainedLayer(float width, const std::function<float(float, float, float, float)>& heightConstraint,
		const std::shared_ptr<Layer>& layer) :
		Layer(Layer::NoBorders), child(layer), heightConstraint(heightConstraint), widthConstraint(
				[width](float x, float y, float width_, float height) {return width;}) {

}

ConstrainedLayer::ConstrainedLayer(const std::function<float(float, float, float, float)>& widthConstraint, float height,
		const std::shared_ptr<Layer>& layer) :
		Layer(Layer::NoBorders), child(layer), widthConstraint(widthConstraint), heightConstraint(
				[height](float x, float y, float width, float height_) {return height;}) {

}

ConstrainedLayer::ConstrainedLayer(const std::function<float(float, float, float, float)>& widthConstraint,
		const std::function<float(float, float, float, float)>& heightConstraint, const std::shared_ptr<Layer>& layer) :
		Layer(Layer::NoBorders), child(layer), widthConstraint(widthConstraint), heightConstraint(heightConstraint) {

}

ConstrainedLayer::~ConstrainedLayer() {
}

void ConstrainedLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	child->draw(window, x, y, width, height);
}

void ConstrainedLayer::update() {
	child->update();
}

bool ConstrainedLayer::grabEvent(const sf::Event& event, float x, float y, float width, float height) const {
	return child->grabEvent(event, x, y, width, height);
}

void ConstrainedLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	child->pollEvent(event, x, y, width, height);
}

const std::shared_ptr<Layer>& ConstrainedLayer::getChild() const {
	return child;
}

float ConstrainedLayer::getHeight(float x, float y, float width, float height) const {
	return heightConstraint(x, y, width, height);
}

float ConstrainedLayer::getWidth(float x, float y, float width, float height) const {
	return widthConstraint(x, y, width, height);
}

}
/* namespace window */
