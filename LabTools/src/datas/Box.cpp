/*
 * Box.cpp
 *
 *  Created on: 10 févr. 2016
 *      Author: alex
 */

#include "Box.h"

namespace labeliser {

Box::Box(const Vector3d& beggin, const Vector3d& end) :
		beggin(beggin), end(end) {
}

Box::~Box() {
}

const Vector3d& Box::getBeggin() const {
	return beggin;
}

const Vector3d& Box::getEnd() const {
	return end;
}

bool Box::isInside(const Vector3d& point) const {
	Vector3d vec = point - beggin;
	Vector3d x, y, z;

	x[0] = end[0] - beggin[0];
	y[1] = end[1] - beggin[1];
	z[2] = end[2] - beggin[2];

	double xNorm = x.normalize();
	double yNorm = y.normalize();
	double zNorm = z.normalize();

	double projx = vec * x;
	double projy = vec * y;
	double projz = vec * z;

	return projx > 0 && projy > 0 && projz > 0 && projx < xNorm && projy < yNorm && projz < zNorm;
}

void Box::setBeggin(const Vector3d& beggin) {
	this->beggin = beggin;
}

void Box::setEnd(const Vector3d& end) {
	this->end = end;
}

}  // namespace labeliser
