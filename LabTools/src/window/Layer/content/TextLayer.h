/*
 * TextLayer.h
 *
 *  Created on: 10 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_TEXTLAYER_H_
#define SRC_WINDOW_LAYER_TEXTLAYER_H_

#include <cstdint>
#include <functional>
#include <string>

#include "../Layer.h"

namespace window {

class TextLayer: public Layer {
public:
	enum {
		CENTERED = 0, LEFTALIGN = 01, RIGHTALIGN = LEFTALIGN << 1
	};

	TextLayer(const std::string& text = "", unsigned int size = 20, bool resizable = true, uint8_t alignment = LEFTALIGN,
			const sf::Color& textColor = sf::Color(0, 0, 0));
	virtual ~TextLayer();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;

	void setWidthMax(float width);
	virtual float getHeight() const;
	float getTextWidth() const;
	virtual const std::string& getText() const;
	virtual void setText(const std::string&);
	void update() override;
	void setMargin(unsigned short);

protected:
	float width = -1.f;
	float height = -1.f;
	float lastWidth = -1.f;
	float textWidth = 0.f;
	std::string text = "";
	unsigned int textSize;
	uint8_t alignment;
	bool resizable;
	std::vector<std::string> lines = std::vector<std::string>();
	float textHeight = 0.f;
	sf::Color textColor;
	unsigned short margin = 0.f;

	void updateTexture();
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_TEXTLAYER_H_ */
