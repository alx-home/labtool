/*
 * Stake.h
 *
 *  Created on: 9 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_STAKE_H_
#define SRC_WINDOW_LAYER_STAKE_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "ConstrainedLayer.h"
#include "../Layer.h"

namespace window {

class StakeLayer: public Layer {
public:
	StakeLayer(const uint8_t& borders, const std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>>&layers);
	const std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>>& getSubLayers();

	virtual ~StakeLayer();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void update() override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	float getWidth (float x, float y, float width, float height);
	float getHeight (float x, float y, float width, float height);

protected:
	std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>> layers;
};

}
/* namespace window */

#endif /* SRC_WINDOW_LAYER_STAKE_H_ */
