/*
 * Layer.h
 *
 *  Created on: 30 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_LAYER_H_
#define SRC_WINDOW_LAYER_LAYER_H_

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>

namespace sf {
class Event;
class Window;
} /* namespace sf */

namespace window {

class Layer {
public:
	enum {
		NoBorders = 00,
		LeftBorder = 01,
		RightBorder = LeftBorder << 1,
		TopBorder = RightBorder << 1,
		BottomBorder = TopBorder << 1,
		AllBorders = LeftBorder | RightBorder | TopBorder | BottomBorder
	};

	virtual ~Layer();

	virtual void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height);
	virtual void pollEvent(const sf::Event& event, float x, float y, float width, float height) = 0;
	virtual void update() = 0;
	virtual bool grabEvent(const sf::Event& event, float x, float y, float width, float height) const;

	Layer& setBorders(uint8_t borders);

protected:
	uint8_t borders;

	Layer(const uint8_t& borders);
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_LAYER_H_ */
