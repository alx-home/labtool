/*
 * Pannel.h
 *
 *  Created on: 9 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_GRID_H_
#define SRC_WINDOW_LAYER_GRID_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "../Layer.h"

namespace window {

class GridLayer: public Layer {
public:
	GridLayer(const uint8_t& borders, unsigned short nbElems, bool horizontalConstraint, const std::vector<std::shared_ptr<Layer>>& layers);
	virtual ~GridLayer();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void update() override;

protected:
	std::vector<std::shared_ptr<Layer>> layers;
	unsigned short nbElems;
	bool horizontalConstraint;
};

}
/* namespace window */

#endif /* SRC_WINDOW_LAYER_GRID_H_ */
