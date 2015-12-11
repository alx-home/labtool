/*
 * MarginLayer.h
 *
 *  Created on: 11 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_DISPOSITION_SCROLLLAYER_H_
#define SRC_WINDOW_LAYER_DISPOSITION_SCROLLLAYER_H_

#include <cstdint>
#include <memory>

#include "../Layer.h"

namespace window {
class ConstrainedLayer;
} /* namespace window */

namespace window {

class ScrollLayer: public Layer {
public:
	typedef enum {
		Top = 00, Bottom = Top << 1, Left = Bottom << 1, Right = Left << 1
	} Disposition;

	ScrollLayer(const std::shared_ptr<ConstrainedLayer>& child, Disposition disposition, uint8_t borders = 0x0);
	virtual ~ScrollLayer();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void update() override;

private:
	std::shared_ptr<ConstrainedLayer> child;
	Disposition disposition;
	double posPercentage = 0.0;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_DISPOSITION_SCROLLLAYER_H_ */
