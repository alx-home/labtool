/*
 * Stake.cpp
 *
 *  Created on: 9 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "StakeLayer.h"

namespace window {

StakeLayer::StakeLayer(const uint8_t& borders, const std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>>&layers) :
Layer(borders), layers(layers) {
}

const std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>>& StakeLayer::getSubLayers() {
	return layers;
}

StakeLayer::~StakeLayer() {
}

void StakeLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	Layer::draw(window, x, y, width, height);

	float widthAccu = 0.f;
	float heightMax = 0.f;
	float heightAccu = 0.f;
	float layerWidth = 0.f;
	float layerHeight = 0.f;

	for (auto layer : *layers) {
		layerWidth = layer->getWidth(x, y, width, height);
		layerHeight = layer->getHeight(x, y, width, height);

		if (widthAccu + layerWidth > width) {
			widthAccu = 0.f;
			heightAccu += heightMax;
			heightMax = 0.f;

		}

		if (layerHeight > heightMax)
			heightMax = layerHeight;

		layer->draw(window, x + widthAccu, y + heightAccu, layerWidth, layerHeight);
		widthAccu += layerWidth;
	}
}

void StakeLayer::update() {
	for (auto layer : *layers)
		layer->update();
}

float StakeLayer::getWidth(float x, float y, float width, float height) {
	float widthAccu = 0.f;
	float layerWidth = 0.f;
	float layerHeight = 0.f;

	for (auto layer : *layers) {
		layerWidth = layer->getWidth(x, y, width, height);
		layerHeight = layer->getHeight(x, y, width, height);

		if (widthAccu + layerWidth > width) {
			return width;
		}

		widthAccu += layerWidth;
	}

	return widthAccu;
}

float StakeLayer::getHeight(float x, float y, float width, float height) {
	float widthAccu = 0.f;
	float heightMax = 0.f;
	float heightAccu = 0.f;
	float layerWidth = 0.f;
	float layerHeight = 0.f;

	for (auto layer : *layers) {
		layerWidth = layer->getWidth(x, y, width, height);
		layerHeight = layer->getHeight(x, y, width, height);

		if (widthAccu + layerWidth > width) {
			widthAccu = 0.f;
			heightAccu += heightMax;
			heightMax = 0.f;

		}

		if (layerHeight > heightMax)
			heightMax = layerHeight;

		widthAccu += layerWidth;
	}

	return heightAccu + heightMax;
}

void StakeLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	float widthAcc = 0.f;
	float heightMax = 0.f;
	float heightAcc = 0.f;
	float layerWidth = 0.f;
	float layerHeight = 0.f;

	for (auto layer : *layers) {
		layerWidth = layer->getWidth(x, y, width, height);
		layerHeight = layer->getHeight(x, y, width, height);

		if (widthAcc + layerWidth > width) {
			widthAcc = 0.f;
			heightAcc += heightMax;
			heightMax = 0.f;

		}

		if (layerHeight > heightMax)
			heightMax = layerHeight;

		layer->pollEvent(event, x + widthAcc, y + heightAcc, layerWidth, layerHeight);
		widthAcc += layerWidth;
	}
}

} /* namespace window */
