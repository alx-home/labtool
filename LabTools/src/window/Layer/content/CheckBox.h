/*
 * CheckBox.h
 *
 *  Created on: 26 janv. 2016
 *      Author: alex
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_CHECKBOX_H_
#define SRC_WINDOW_LAYER_CONTENT_CHECKBOX_H_

#include <functional>
#include <memory>

#include "../Layer.h"

namespace window {

class CheckBox: public Layer {
public:
	CheckBox();
	virtual ~CheckBox();

	virtual void draw(const std::shared_ptr<sf::RenderTarget>& window, float x,
			float y, float width, float height);
	virtual void pollEvent(const sf::Event& event, float x, float y,
			float width, float height);
	virtual void update();
	virtual bool grabEvent(const sf::Event& event, float x, float y,
			float width, float height) const;

	void disable();
	void enable();
	void setCallback(const std::function<void(bool checked)>& callback);
	void check(bool flag = true);
	bool isChecked() const;

private:
	static std::unique_ptr<sf::Texture> texture;
	bool checked = false;
	bool inside = false;
	bool disableFlag = false;
	std::function<void(bool checked)> callback = [](bool) {};
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_CHECKBOX_H_ */
