/*
 * Layer.cpp
 *
 *  Created on: 30 oct. 2015
 *      Author: Alexandre GARCIN
 */

#include "Layer.h"

#include <GL/glew.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

namespace window {

Layer::Layer(const uint8_t& borders) :
		borders(borders) {
}

Layer::~Layer() {
}

void Layer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	if (borders == NoBorders)
		return;

	window->popGLStates();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		glLoadIdentity();
		glOrtho(0, 0, width, height, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glViewport(x, window->getSize().y - (height + y), width, height);
			glLoadIdentity();

			constexpr float borderSize = 3.f;
			glLineWidth(borderSize);

			glBegin(GL_LINES);
			{
				glColor3f(0.3f, 0.3f, 0.3f);

				if (borders & RightBorder) {
					glVertex2d(1.f, -1.f);
					glVertex2d(1.f, 1.f);
				}

				if (borders & LeftBorder) {
					glVertex2d(-1.f, -1.f);
					glVertex2d(-1.f, 1.f);
				}

				if (borders & TopBorder) {
					glVertex2d(1.f, 1.f);
					glVertex2d(-1.f, 1.f);
				}

				if (borders & BottomBorder) {
					glVertex2d(-1.f, -1.f);
					glVertex2d(1.f, -1.f);
				}
			}
			glEnd();
		}
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
	}
	glPopMatrix();

	window->pushGLStates();
}

bool Layer::grabEvent(const sf::Event& event, float x, float y, float width, float height) const {
	return false;
}

Layer& Layer::setBorders(uint8_t borders) {
	this->borders = borders;
	return *this;
}

} /* namespace window */
