/*
 * Popup.h
 *
 *  Created on: 26 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_POPUP_H_
#define SRC_WINDOW_LAYER_CONTENT_POPUP_H_

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

#include "../../disposition/ConstrainedLayer.h"
#include "../../Layer.h"
#include "../Buttons/Button.h"

namespace window {

class Popup: public Layer {
public:
	Popup(const std::shared_ptr<ConstrainedLayer>& content);
	virtual ~Popup();

	float getWidth(float x, float y, float width, float height);
	float getHeight(float x, float y, float width, float height);

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void update() override;

protected:
	std::shared_ptr<ConstrainedLayer> content;
	float xPos = 0.f;
	float yPos = 0.f;
	bool initialised = false;
	static constexpr float ligneWidth = 1.f;
	static constexpr float ligneWidth2 = 2.f;
	static constexpr float margin = 10.f + ligneWidth;
	bool clicked = false;
	float clickX = 0.f;
	float clickY = 0.f;
	float xInit = 0.f;
	float yInit = 0.f;
	float lastHeight = 0;
	float lastWidth = 0;
	sf::RectangleShape boxContent;
	sf::RectangleShape selectionBox;
	Button exitButton = Button(false, "X", 12);
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_POPUP_H_ */
