/*
 * EmptyLayer.h
 *
 *  Created on: 10 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_EMPTYLAYER_H_
#define SRC_WINDOW_LAYER_EMPTYLAYER_H_

#include "Layer.h"

namespace window {

class EmptyLayer: public Layer {
public:
	EmptyLayer(const uint8_t& borders = Layer::NoBorders);
	virtual ~EmptyLayer();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void update() override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_EMPTYLAYER_H_ */
