/*
 * SplitBarre.cpp
 *
 *  Created on: 2 févr. 2016
 *      Author: Alexandre GARCIN
 */

 #include<cmath>
 
#include "SplitBar.h"

namespace window {

SplitBar::SplitBar() :
		Layer(NoBorders) {
}

SplitBar::~SplitBar() {
}

void SplitBar::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	if (!displayFlag)
		return;
	sf::RectangleShape rec(sf::Vector2f(width, height));
	rec.setPosition(x, y);
	rec.setFillColor(sf::Color(240, 240, 240, 80));

	window->draw(rec);

	rec.setPosition(x + 2, std::floor(y + (int) height / 2.f) + 0.2f);
	rec.setSize(sf::Vector2f(width - 4, 1));
	rec.setFillColor(sf::Color(120, 120, 120, 255));

	window->draw(rec);
}

void SplitBar::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
}

void SplitBar::update() {
}

float SplitBar::getHeight() const {
	return 10.f;
}
void SplitBar::display() {
	displayFlag = true;
}

void SplitBar::hide() {
	displayFlag = false;
}

} /* namespace window */
