/*
 * Legend.h
 *
 *  Created on: 21 déc. 2015
 *      Author: alex
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_POPUP_LEGEND_H_
#define SRC_WINDOW_LAYER_CONTENT_POPUP_LEGEND_H_

#include <memory>

#include "../plot/Plot3d.h"

namespace window {

class Legend: public Layer {
public:
	Legend(float x, float y, float width, float height);
	virtual ~Legend();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void update() override;
	bool grabEvent(const sf::Event& event, float x, float y, float width, float height) const override;

	void hide();
	void display();

private:
	float x;
	float y;
	float width;
	float height;
	Plot3d plot;
	bool hidded = false;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_POPUP_LEGEND_H_ */
