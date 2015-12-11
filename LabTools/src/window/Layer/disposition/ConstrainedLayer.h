/*
 * ConstrainedLayer.h
 *
 *  Created on: 12 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_DISPOSITION_CONSTRAINEDLAYER_H_
#define SRC_WINDOW_LAYER_DISPOSITION_CONSTRAINEDLAYER_H_

#include <memory>
#include <functional>

#include "../Layer.h"

namespace window {

class ConstrainedLayer: public Layer {
public:
	ConstrainedLayer(float width, float height, const std::shared_ptr<Layer>& layer);
	ConstrainedLayer(float width, const std::function<float(float, float, float, float)>& heightConstraint,
			const std::shared_ptr<Layer>& layer);
	ConstrainedLayer(const std::function<float(float, float, float, float)>& widthConstraint, float height,
			const std::shared_ptr<Layer>& layer);
	ConstrainedLayer(const std::function<float(float, float, float, float)>& widthConstraint,
			const std::function<float(float, float, float, float)>& heightConstraint, const std::shared_ptr<Layer>& layer);
	virtual ~ConstrainedLayer();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void update() override;
	bool grabEvent(const sf::Event& event, float x, float y, float width, float height) const override;

	const std::shared_ptr<Layer>& getChild() const;
	float getHeight(float x, float y, float width, float height) const;
	float getWidth(float x, float y, float width, float height) const;

private:
	std::shared_ptr<Layer> child;
	std::function<float(float, float, float, float)> heightConstraint;
	std::function<float(float, float, float, float)> widthConstraint;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_DISPOSITION_CONSTRAINEDLAYER_H_ */
