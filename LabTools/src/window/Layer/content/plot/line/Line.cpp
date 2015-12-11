/*
 * Point.cpp
 *
 *  Created on: 5 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "Line.h"

#include <GL/glew.h>
#include <functional>
#include <vector>

#include "../../../../Window.h"
#include "../point/Point.h"

namespace utils {

Line::Line(const std::shared_ptr<Point>& pointA, const std::shared_ptr<Point>& pointB, const sf::Color& linkColor, float linkSize) :
		pointA(pointA), pointB(pointB), linkColor(linkColor), linkSize(linkSize) {
}

Line::~Line() {
}

std::shared_ptr<Line> Line::createLine(const std::shared_ptr<Point>& pointA, const std::shared_ptr<Point>& pointB,
		const sf::Color& linkColor, float linkSize) {
	for (const auto& line : pointA->getLines())
		if (line->getPointA() == pointB || line->getPointB() == pointA)
			return line;

	struct make_shared_enabler: public Line {
		make_shared_enabler(const std::shared_ptr<Point>& pointA, const std::shared_ptr<Point>& pointB, const sf::Color& linkColor,
				float linkSize) :
				Line(pointA, pointB, linkColor, linkSize) {
		}
	};
	std::shared_ptr<Line> ptr = std::make_shared<make_shared_enabler>(pointA, pointB, linkColor, linkSize);
	pointA->linkPointTo(pointB, linkColor, linkSize, ptr);
	pointB->linkPointTo(pointA, linkColor, linkSize, ptr);

	return ptr;
}

void Line::clear() {
	pointA->unlinkPointTo(*this);
	pointB->unlinkPointTo(*this);
	suppressed = true;
}

bool Line::isSuppressed() {
	return suppressed;
}

bool Line::isDisplayed() {
	return displayFlag;
}

void Line::hide() {
	displayFlag = false;
}

void Line::display() {
	displayFlag = true;
}

void Line::draw(double zoom) const {
	if (!displayFlag)
		return;

	std::array<GLdouble, 16> modelview = std::array<GLdouble, 16>();

	glGetDoublev(GL_MODELVIEW_MATRIX, const_cast<GLdouble*>(&modelview.front()));

	glPushMatrix();
	{
		double size = linkSize;

		::Vector3d dir, view;

		dir = pointA->getPosition() - pointB->getPosition();
		view[0] = modelview[2];
		view[1] = modelview[6];
		view[2] = modelview[10];

		dir = view ^ dir;
		dir.normalize();

		std::function<void(const Vector3d&, const Vector3d&, const Vector3d&)> draw =
				[](const Vector3d& pointA, const Vector3d& pointB, const Vector3d& offset) {
					glBegin(GL_QUADS);
					{
						glVertex3d(pointA[0] + offset[0],
								pointA[1] + offset[1],
								pointA[2] + offset[2]);
						glVertex3d(pointB[0] + offset[0],
								pointB[1] + offset[1],
								pointB[2] + offset[2]);
						glVertex3d(pointB[0] - offset[0],
								pointB[1] - offset[1],
								pointB[2] - offset[2]);
						glVertex3d(pointA[0] - offset[0],
								pointA[1] - offset[1],
								pointA[2] - offset[2]);
					}
					glEnd();
				};

		sf::Color color;

		if (pointA->isSelected() || pointB->isSelected()) {
			color = ::window::Window::selectColorLine;
			size *= 2.;
		} else if (pointA->getColor() == window::Window::labellisedColor || pointB->getColor() == window::Window::labellisedColor) {
			color = ::window::Window::labelisedColorLine;
			size *= 2.;
		} else
			color = linkColor;

		dir *= size * zoom;

		glColor4ub(color.r, color.g, color.b, color.a);

		draw(pointA->getPosition(), pointB->getPosition(), dir);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		{
			glColor4ub(color.r, color.g, color.b, 40);

			draw(pointA->getPosition(), pointB->getPosition(), dir);
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glPopMatrix();
}

sf::Color Line::getLinkColor() const {
	return linkColor;
}

void Line::setLinkColor(sf::Color color) {
	linkColor = color;
}

void Line::setLinkSize(float size) {
	linkSize = size;
}

float Line::getLinkSize() const {
	return linkSize;
}

const std::shared_ptr<Point>& Line::getPointA() const {
	return pointA;
}

const std::shared_ptr<Point>& Line::getPointB() const {
	return pointB;
}

} /* namespace plot */
