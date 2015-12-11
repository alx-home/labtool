/*
 * Popup.h
 *
 *  Created on: 26 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_MOUSEPOPUP_H_
#define SRC_WINDOW_LAYER_CONTENT_MOUSEPOPUP_H_

#include <cmath>
#include <cstdint>
#include <memory>
#include <vector>

#include "../../disposition/StakeLayer.h"
#include "../../Layer.h"

namespace window {
class GridLayer;
} /* namespace window */

namespace window {

class MousePopup: public Layer {
public:
	MousePopup(float width, const std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer>>>&content, float xPos = INFINITY, float yPos = INFINITY, uint8_t borders = Layer::NoBorders);
	virtual ~MousePopup();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void update() override;
	bool grabEvent(const sf::Event& event, float x, float y, float width, float height) const override;

	float getXpos() const;
	float getYpos() const;
	void disable();

protected:
	std::shared_ptr<StakeLayer> content = std::shared_ptr<StakeLayer>();
	float xPos;
	float yPos;
	bool displayFlag = false;
	float popupWidth;
	unsigned short timeStamp = 0;
	static constexpr unsigned short timeStampMax = 10;
};

}/* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_MOUSEPOPUP_H_ */
