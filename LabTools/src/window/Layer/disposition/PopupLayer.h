/*
 * PopupLayer.h
 *
 *  Created on: 26 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_DISPOSITION_POPUPLAYER_H_
#define SRC_WINDOW_LAYER_DISPOSITION_POPUPLAYER_H_

#include <memory>

#include "../Layer.h"

namespace window {
class ConstrainedLayer;
} /* namespace window */

namespace window {

class PopupLayer: public Layer {
public:
	PopupLayer(const std::shared_ptr<Layer>& background, const std::shared_ptr<Layer>& popup, bool backgroundDisable = true);
	virtual ~PopupLayer();

	void addPopup(const std::shared_ptr<Layer>& popup);
	std::shared_ptr<Layer> getBackgroundLayer() const;

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void update() override;

protected:
	std::shared_ptr<Layer> background;
	std::shared_ptr<Layer> popup;
	bool backgroundDisable;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_DISPOSITION_POPUPLAYER_H_ */
