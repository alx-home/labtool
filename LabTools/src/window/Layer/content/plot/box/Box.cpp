/*
 * Box.cpp
 *
 *  Created on: 25 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "Box.h"

#include <cmath>
#include <limits>

#include "../../../../../utils/opengl/Draw.h"
#include "../point/Point.h"

namespace utils {

Box::Box(double x1, double y1, double z1, double x2, double y2, double z2, sf::Color color, const std::string& name) :
		x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2), color(color), name(name) {
	setExtreminties(::Vector3d( { x1, y1, z1 }), ::Vector3d( { x2, y2, z2 }));
}

Box::Box(const std::array<double, 3>& coords1, const std::array<double, 3>& coords2, sf::Color color, const std::string& name) :
		Box(coords1[0], coords1[1], coords1[2], coords2[0], coords2[1], coords2[2], color, name) {
}

Box::Box(const Vector3d& coords1, const Vector3d& coords2, sf::Color color, const std::string& name) :
		Box(coords1[0], coords1[1], coords1[2], coords2[0], coords2[1], coords2[2], color, name) {
}

Box::Box(const std::array<double, 6>& coords, sf::Color color, const std::string& name) :
		Box(coords[0], coords[1], coords[2], coords[3], coords[4], coords[5], color, name) {
}

Box::~Box() {
}

void Box::setName(const std::string& name) {
	this->name = name;
}

void Box::setExtreminties(const ::Vector3d& extr1, const ::Vector3d& extr2) {
	if (extr1[0] < extr2[0]) {
		double temp = extr1[0];
		extr1[0] = extr2[0];
		extr2[0] = temp;
	}

	if (extr1[1] < extr2[1]) {
		double temp = extr1[1];
		extr1[1] = extr2[1];
		extr2[1] = temp;
	}

	if (extr1[2] < extr2[2]) {
		double temp = extr1[2];
		extr1[2] = extr2[2];
		extr2[2] = temp;
	}

	x1 = extr1[0];
	y1 = extr1[1];
	z1 = extr1[2];
	x2 = extr2[0];
	y2 = extr2[1];
	z2 = extr2[2];

	A[0] = A[1] = A[3] = A[4] = extr1;
	A[1][1] = extr2[1];
	A[2] = A[1];
	A[2][0] = extr2[0];
	A[3][0] = extr2[0];
	A[4][2] = extr2[2];
	A[5] = A[4];
	A[5][1] = extr2[1];
	A[6] = A[5];
	A[6][0] = extr2[0];
	A[7] = A[4];
	A[7][0] = extr2[0];
}

void Box::draw(const std::array<GLdouble, 16>& modelview, double zoom) const {
	if (!displayFlag)
		return;

	glPushMatrix();
	{
		float xScale = 0.5f * (x2 - x1);
		float yScale = 0.5f * (y2 - y1);
		float zScale = 0.5f * (z2 - z1);

		glTranslatef(x1 + xScale, y1 + yScale, z1 + zScale);
		glScalef(xScale, yScale, zScale);

		utils::opengl::Draw::drawCube(color);

	}
	glPopMatrix();
}

bool Box::isSelectable() const {
	return selectable;
}

bool Box::isDisplayed() const {
	return displayFlag;
}

void Box::display() {
	displayFlag = true;
}

void Box::hide() {
	displayFlag = false;
}

std::array<double, 3> Box::getExtr1() const {
	return std::array<double, 3> { x1, y1, z1 };
}

std::array<double, 3> Box::getExtr2() const {
	return std::array<double, 3> { x2, y2, z2 };
}

const std::function<void(const sf::Event&, bool, const Vector3d& beggin, const Vector3d& vec)>& Box::getCallBack() const {
	return callBack;
}

void Box::setCallBack(const std::function<void(const sf::Event&, bool, const Vector3d&, const Vector3d&)>& callBack) {
	this->callBack = callBack;
}

void Box::unselect() {
	boxIntersect = false;
	mouseOver = false;
	cornerIntersect = false;
}

std::tuple<Vector3d, double> Box::getIntersection(const Vector3d& beggin, const Vector3d& vec) {
	double tmin = std::numeric_limits<double>::max();

	Vector3d P, POut, extr1, extr2;

	extr1 = Vector3d(getExtr1());
	extr2 = Vector3d(getExtr2());

	std::array<Vector3d, 6> n { Vector3d( { 0.0, 0.0, 1.0 }), Vector3d( { 1.0, 0.0, 0.0 }), Vector3d( { 0.0, 1.0, 0.0 }), Vector3d( { -1.0,
			0.0, 0.0 }), Vector3d( { 0.0, -1.0, 0.0 }), Vector3d( { 0.0, 0.0, -1.0 }) };
	std::array<std::array<unsigned short, 4>, 6> indexes { std::array<unsigned short, 4> { 0, 1, 2, 3 }, std::array<unsigned short, 4> { 0,
			1, 5, 4 }, std::array<unsigned short, 4> { 1, 2, 6, 5 }, std::array<unsigned short, 4> { 2, 3, 7, 6 }, std::array<
			unsigned short, 4> { 0, 3, 7, 4 }, std::array<unsigned short, 4> { 4, 5, 6, 7 } };
	double t;

	for (unsigned short i = 0; i < 6; ++i) {
		t = (A[i] - beggin) * n[i] / (vec * n[i]);
		P = beggin + t * vec;

		if (t < 0)
			continue;

		bool inside = true;

		for (unsigned short j = 0; j < 4; ++j) {
			Vector3d edge = A[indexes[i][(j + 1) % 4]] - A[indexes[i][j]];
			double scalarMult = (P - A[indexes[i][j]]) * edge;

			if (scalarMult < 0 || fabs(scalarMult) > pow(edge.getNorm(), 2)) {
				inside = false;
				break;
			}
		}

		if (inside) {
			bool breaker = tmin != std::numeric_limits<double>::max();

			if (fabs(t) < tmin) {
				tmin = fabs(t);
				POut = P;
				if (!clicked)
					face = i;
			}

			if (breaker)
				return std::tuple<Vector3d, double>(POut, t);
		}
	}

	return std::tuple<Vector3d, double>(Vector3d(), std::numeric_limits<double>::max());
}

void Box::setColor(sf::Color color) {
	this->color = color;
}

void Box::applyChanges() {
	this->changeCallback();
}

void Box::setChangeCallback(const std::function<void()>& callback) {
	this->changeCallback = callback;
}

const std::string& Box::getName() const {
	return name;
}

} /* namespace utils */
