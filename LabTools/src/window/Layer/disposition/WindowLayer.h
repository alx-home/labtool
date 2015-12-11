/*
 * FirstLayer.h
 *
 *  Created on: 9 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_WINDOWLAYER_H_
#define SRC_WINDOW_LAYER_WINDOWLAYER_H_

#include <memory>

#include "../Layer.h"

namespace window {

class WindowLayer: public Layer {
public:
	WindowLayer(const std::shared_ptr<Layer>& child);
	virtual ~WindowLayer();

	void draw(const std::shared_ptr<sf::RenderWindow>& window);
	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void update() override;
	void pollEvent(const sf::Event& event, const std::shared_ptr<sf::Window>& window);
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	const std::shared_ptr<Layer>& getChild() const;
	void setChild(const std::shared_ptr<Layer>& child);

protected:
	std::shared_ptr<Layer> child;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_WINDOWLAYER_H_ */
