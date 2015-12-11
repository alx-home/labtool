/*
 * SplitBarre.h
 *
 *  Created on: 2 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_BUTTONS_SPLITBAR_H_
#define SRC_WINDOW_LAYER_CONTENT_BUTTONS_SPLITBAR_H_

#include <memory>

#include "../../Layer.h"

namespace window {

class SplitBar: public Layer {
public:
	SplitBar();
	virtual ~SplitBar();

	virtual void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	virtual void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	virtual void update() override;
	float getHeight() const;
	void display();
	void hide();

private:
	bool displayFlag = true;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_BUTTONS_SPLITBAR_H_ */
