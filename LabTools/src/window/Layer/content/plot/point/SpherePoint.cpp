/*
 * SpherePoint.cpp
 *
 *  Created on: 18 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "SpherePoint.h"

#include <GL/glew.h>
#include <vector>

#include "../../../../../utils/opengl/Draw.h"
#include "../../../../Window.h"

namespace utils {

SpherePoint::SpherePoint(const ::Vector3d& pos, const sf::Color& color, float rayon) :
		Point(pos[0], pos[1], pos[2], color, rayon) {
}

SpherePoint::~SpherePoint() {
}

void SpherePoint::draw3d() const {
	if (!displayFlag)
		return;

	glPushMatrix();
	{
		glTranslated(position[0], position[1], position[2]);

		glPushMatrix();
		{
			glScalef(size, size, size);

			utils::opengl::Draw::drawSphere(color, 1000 * size, false);

			if (selected) {
				constexpr float sizeSelecFactor = 2.f;

				glPushMatrix();
				{
					glScalef(sizeSelecFactor, sizeSelecFactor, sizeSelecFactor);
					utils::opengl::Draw::drawSphere(window::Window::selectColorPoint, 1000 * size * sizeSelecFactor);
				}
				glPopMatrix();
			}

			if (lines.size() > 1 || error)
				glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

bool SpherePoint::isSelectable() {
	return false;
}

} /* namespace utils */
