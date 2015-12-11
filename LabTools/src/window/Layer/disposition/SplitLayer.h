/*
 * SplitLayer.h
 *
 *  Created on: 9 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_SPLITLAYER_H_
#define SRC_WINDOW_LAYER_SPLITLAYER_H_

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

#include "../Layer.h"
#include "ConstrainedLayer.h"

namespace window {
class Annimation;
} /* namespace window */

namespace window {

class SplitLayer: public Layer {
public:
	SplitLayer(const std::shared_ptr<Layer>& unConstrainedLayer, const std::shared_ptr<ConstrainedLayer>& constrainedLayer,
			bool cutOnXAxis = true, bool leftOrTopConstrained = true, bool expanded = true,
			const std::function<void(bool)>& onAnimationEnded = [](bool expanded) {}, const std::function<void(bool)>& onAnimationStarted =
					[](bool expanded) {}, const uint8_t& borders = 0x0, float deltaSplitAnimation = 30.f);
	virtual ~SplitLayer();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void update() override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void addAnnimation(const std::shared_ptr<Annimation>& animation);
	void expandSplit();
	void retractSplit();
	void setStartCallBack(const std::function<void(bool)>& onAnimationStarted = [](bool expanded) {});
	void setEndCallBack(const std::function<void(bool)>& onAnimationEnded = [](bool expanded) {});
	void setConstrainedLayer(const std::shared_ptr<ConstrainedLayer>& layer);
	void setUnConstrainedLayer(const std::shared_ptr<Layer>& layer);
	std::shared_ptr<ConstrainedLayer> getConstrainedLayer() const;
	std::shared_ptr<Layer> getUnConstrainedLayer() const;
	bool isExpanded () const;

protected:
	std::shared_ptr<ConstrainedLayer> constrainedLayer;
	std::shared_ptr<Layer> unConstrainedLayer;
	bool leftOrTopConstraint;
	bool cutOnXAxis;
	float splitPos = 0.f;
	float deltaSplitAnimation;
	bool inAnimation = false;
	bool expand = false;
	std::vector<std::shared_ptr<Annimation>> animations = std::vector<std::shared_ptr<Annimation>>();
	std::function<void(bool)> onAnimationEnded;
	std::function<void(bool)> onAnimationStarted;

	void animateSplit();
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_SPLITLAYER_H_ */
