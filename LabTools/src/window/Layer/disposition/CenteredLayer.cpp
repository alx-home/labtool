/*
 * CenteredLayer.cpp
 *
 *  Created on: 17 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "CenteredLayer.h"

namespace window {

CenteredLayer::CenteredLayer(const std::shared_ptr<ConstrainedLayer>& child,
		uint8_t borders) :
		Layer(borders), child(child) {
}

CenteredLayer::~CenteredLayer() {
}

void CenteredLayer::draw(const std::shared_ptr<sf::RenderTarget>& window,
		float x, float y, float width, float height) {
	float widthChild = child->getWidth(x, y, width, height);
	float heightChild = child->getHeight(x, y, width, height);

	Layer::draw(window, x, y, width, height);

	child->draw(window, x + (int)(width - widthChild) / 2.f,
			y + (int)(height - heightChild) / 2.f, widthChild, heightChild);
}

void CenteredLayer::pollEvent(const sf::Event& event, float x, float y,
		float width, float height) {
	float widthChild = child->getWidth(x, y, width, height);
	float heightChild = child->getHeight(x, y, width, height);

	child->pollEvent(event, x + (int)(width - widthChild) / 2.f,
			y + (int)(height - heightChild) / 2.f, widthChild, heightChild);
}

void CenteredLayer::update() {
	child->update();
}

const std::shared_ptr<ConstrainedLayer>& CenteredLayer::getChild() const {
	return child;
}

void CenteredLayer::setChild(const std::shared_ptr<ConstrainedLayer>& child) {
	this->child = child;
}

} /* namespace window */
