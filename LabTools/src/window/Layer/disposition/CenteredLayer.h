/*
 * CenteredLayer.h
 *
 *  Created on: 17 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_DISPOSITION_CENTEREDLAYER_H_
#define SRC_WINDOW_LAYER_DISPOSITION_CENTEREDLAYER_H_

#include <memory>

#include "../Layer.h"
#include "ConstrainedLayer.h"

namespace window {

class CenteredLayer: public Layer {
public:
	CenteredLayer(const std::shared_ptr<ConstrainedLayer>& child,
			uint8_t borders = Layer::NoBorders);
	virtual ~CenteredLayer();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y,
			float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width,
			float height) override;
	void update() override;
	const std::shared_ptr<ConstrainedLayer>& getChild() const;
	void setChild(const std::shared_ptr<ConstrainedLayer>& child);

private:
	std::shared_ptr<ConstrainedLayer> child;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_DISPOSITION_CENTEREDLAYER_H_ */
