/*
 * Pannel.cpp
 *
 *  Created on: 9 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "GridLayer.h"

namespace window {

GridLayer::GridLayer(const uint8_t& borders, unsigned short nbElems, bool horizontalConstraint,
		const std::vector<std::shared_ptr<Layer>>& layers) :
		Layer(borders), layers(layers), nbElems(nbElems), horizontalConstraint(horizontalConstraint) {
}

GridLayer::~GridLayer() {
}

void GridLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	Layer::draw(window, x, y, width, height);

	unsigned int j, nbElemsJ, nb;
	j = 0;

	{
		float tmp = layers.size() / nbElems;
		nbElemsJ = tmp;

		if (tmp - ((float) nbElemsJ) != 0.f)
			++nbElemsJ;
	}

	for (unsigned int i = 0; i < nbElems; ++i) {
		nb = i + j * nbElemsJ;

		if (nb >= layers.size())
			return;

		if (horizontalConstraint)
			layers[nb]->draw(window, x + i * width / nbElems, y + j * height / nbElemsJ, width / nbElems, height / nbElemsJ);
		else
			layers[nb]->draw(window, x + j * width / nbElemsJ, y + i * height / nbElems, width / nbElemsJ, height / nbElems);

		if (i == nbElems - 1)
			++j;
	}
}

void GridLayer::update() {
	for (const auto& layer : layers)
		layer->update();
}

void GridLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	unsigned int j, nbElemsJ, nb;
	j = 0;

	{
		float tmp = layers.size() / nbElems;
		nbElemsJ = tmp;

		if (tmp - ((float) nbElemsJ) != 0.f)
			++nbElemsJ;
	}

	for (unsigned int i = 0; i < nbElems; ++i) {
		nb = i + j * nbElemsJ;

		if (nb >= layers.size())
			return;

		if (horizontalConstraint)
			layers[nb]->pollEvent(event, x + i * width / nbElems, y + j * height / nbElemsJ, width / nbElems, height / nbElemsJ);
		else
			layers[nb]->pollEvent(event, x + j * width / nbElemsJ, y + i * height / nbElems, width / nbElemsJ, height / nbElems);

		if (i == nbElems - 1)
			++j;
	}
}

} /* namespace window */
