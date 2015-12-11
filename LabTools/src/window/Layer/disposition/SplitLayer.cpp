/*
 * SplitLayer.cpp
 *
 *  Created on: 9 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "SplitLayer.h"

#include <functional>

namespace window {

SplitLayer::SplitLayer(const std::shared_ptr<Layer>& unConstrainedLayer, const std::shared_ptr<ConstrainedLayer>& constrainedLayer,
		bool cutOnXAxis, bool leftOrTopConstrained, bool expanded, const std::function<void(bool)>& onAnimationEnded,
		const std::function<void(bool)>& onAnimationStarted, const uint8_t& borders, float deltaSplitAnimation) :
		unConstrainedLayer(unConstrainedLayer), constrainedLayer(constrainedLayer), leftOrTopConstraint(leftOrTopConstrained), cutOnXAxis(
				cutOnXAxis), Layer(borders), deltaSplitAnimation(deltaSplitAnimation), onAnimationEnded(onAnimationEnded), onAnimationStarted(
				onAnimationStarted), expand(expanded), splitPos(expanded ? 100.f : 0.f) {
}

SplitLayer::~SplitLayer() {
}

void SplitLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	animateSplit();

	Layer::draw(window, x, y, width, height);

	if (cutOnXAxis) {
		float splitPos = constrainedLayer->getWidth(x, y, width, height) * this->splitPos / 100.f;

		if (leftOrTopConstraint) {
			constrainedLayer->draw(window, x, y, splitPos, height);
			unConstrainedLayer->draw(window, x + splitPos, y, width - splitPos, height);
		} else {
			unConstrainedLayer->draw(window, x, y, width - splitPos, height);
			constrainedLayer->draw(window, x + width - splitPos, y, splitPos, height);
		}
	} else {
		float splitPos = constrainedLayer->getHeight(x, y, width, height) * this->splitPos / 100.f;

		if (leftOrTopConstraint) {
			constrainedLayer->draw(window, x, y, width, splitPos);
			unConstrainedLayer->draw(window, x, y + splitPos, width, height - splitPos);
		} else {
			unConstrainedLayer->draw(window, x, y, width, height - splitPos);
			constrainedLayer->draw(window, x, y + height - splitPos, width, splitPos);
		}
	}
}

void SplitLayer::update() {
	constrainedLayer->update();
	unConstrainedLayer->update();
}

void SplitLayer::expandSplit() {
	if (!expand)
		inAnimation = true;
	expand = true;
}

void SplitLayer::retractSplit() {
	if (expand)
		inAnimation = true;
	expand = false;
}

void SplitLayer::animateSplit() {
	if (expand && inAnimation) {
		if (splitPos == 100.f) {
			onAnimationEnded(expand);
			inAnimation = false;
			return;
		} else if (splitPos == 0)
			onAnimationStarted(expand);

		inAnimation = true;

		splitPos += deltaSplitAnimation;

		if (splitPos > 100.f)
			splitPos = 100.f;
	} else if (inAnimation) {
		if (splitPos == 0) {
			onAnimationEnded(expand);
			inAnimation = false;
			return;
		} else if (splitPos == 100.f)
			onAnimationStarted(expand);

		inAnimation = true;

		splitPos -= deltaSplitAnimation;

		if (splitPos < 0)
			splitPos = 0.f;
	}
}

bool SplitLayer::isExpanded () const {
	return expand;
}

std::shared_ptr<ConstrainedLayer> SplitLayer::getConstrainedLayer() const {
	return constrainedLayer;
}

std::shared_ptr<Layer> SplitLayer::getUnConstrainedLayer() const {
	return unConstrainedLayer;
}

void SplitLayer::setConstrainedLayer(const std::shared_ptr<ConstrainedLayer>& layer) {
	this->constrainedLayer = layer;
}

void SplitLayer::setUnConstrainedLayer(const std::shared_ptr<Layer>& layer) {
	this->unConstrainedLayer = layer;
}

void SplitLayer::setEndCallBack(const std::function<void(bool)>& onAnimationEnded) {
	this->onAnimationEnded = onAnimationEnded;
}

void SplitLayer::setStartCallBack(const std::function<void(bool)>& onAnimationStarted) {
	this->onAnimationStarted = onAnimationStarted;
}

void SplitLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	if (cutOnXAxis) {
		float splitPos = constrainedLayer->getWidth(x, y, width, height) * this->splitPos / 100.f;

		if (leftOrTopConstraint) {
			constrainedLayer->pollEvent(event, x, y, splitPos, height);
			unConstrainedLayer->pollEvent(event, x + splitPos, y, width - splitPos, height);
		} else {
			unConstrainedLayer->pollEvent(event, x, y, width - splitPos, height);
			constrainedLayer->pollEvent(event, x + width - splitPos, y, splitPos, height);
		}
	} else {
		float splitPos = constrainedLayer->getHeight(x, y, width, height) * this->splitPos / 100.f;

		if (leftOrTopConstraint) {
			constrainedLayer->pollEvent(event, x, y, width, splitPos);
			unConstrainedLayer->pollEvent(event, x, y + splitPos, width, height - splitPos);
		} else {
			unConstrainedLayer->pollEvent(event, x, y, width, height - splitPos);
			constrainedLayer->pollEvent(event, x, y + height - splitPos, width, splitPos);
		}
	}
}

} /* namespace window */
