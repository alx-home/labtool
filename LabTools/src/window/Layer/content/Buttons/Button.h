/*
 * Button.h
 *
 *  Created on: 12 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_BUTTON_H_
#define SRC_WINDOW_LAYER_CONTENT_BUTTON_H_

#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>
#include <memory>
#include <string>

#include "../TextLayer.h"

namespace window {

class Button: public TextLayer {
public:
	static constexpr float margin = 10.f;

	Button(bool resizable, const std::string& text, unsigned int size, const std::function<void(float)>& callBack = [](float) {},
			bool maintenable = false);
	virtual ~Button();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void setCallBack(const std::function<void(float time)>& callBack);
	void addKeyListener(std::vector<sf::Keyboard::Key> key);
	const std::function<void(float time)>& getCallBack();
	void hide();
	void display();
	bool isHidded();
	bool isDisable();
	void disable();
	void enable();
	float getHeight() const override;
	float getWidth() const;
	void update() override;
	void trigger(float);
	void lockHided();
	void unlockHided();

protected:
	enum {
		DEFAULT, CLICKED, MOUSEOVER, DISABLE
	} state { DEFAULT }, lastState { CLICKED };
	bool mouseClicked = false;
	std::function<void(float)> callBack;
	bool hidded = false;
	bool maintenable;
	unsigned int timestamp = 0;
	unsigned int minTimeStamp = 30;
	unsigned int maxTimeStamp = 10000;
	std::string text = "";
	sf::RectangleShape buttons2;
	sf::RectangleShape buttons1;
	std::vector<std::vector<sf::Keyboard::Key>> keyListeners = std::vector<std::vector<sf::Keyboard::Key>>();
	unsigned int lockers = 0;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_BUTTON_H_ */
