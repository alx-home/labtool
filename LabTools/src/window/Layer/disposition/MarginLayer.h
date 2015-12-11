/*
 * MarginLayer.h
 *
 *  Created on: 11 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_DISPOSITION_MARGINLAYER_H_
#define SRC_WINDOW_LAYER_DISPOSITION_MARGINLAYER_H_

#include <cstdint>
#include <memory>

#include "../Layer.h"

namespace window {

class MarginLayer: public Layer {
public:
	MarginLayer(const std::shared_ptr<Layer>& child, float leftMargin, float rightMargin, float topMargin, float bottomMargin,
			uint8_t borders = 0x0);
	virtual ~MarginLayer();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void update() override;

private:
	std::shared_ptr<Layer> child;
	float leftMargin;
	float rightMargin;
	float topMargin;
	float bottomMargin;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_DISPOSITION_MARGINLAYER_H_ */
