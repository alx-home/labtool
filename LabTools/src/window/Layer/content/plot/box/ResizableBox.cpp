/*
 * ResizableBox.cpp
 *
 *  Created on: 3 févr. 2016
 *      Author: alex
 */

#include "ResizableBox.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <cmath>

#include "../../../../../datas/Box.h"
#include "../../../../../utils/window/Cursor.h"
#include "../point/DefaultPoint.h"

namespace utils {

ResizableBox::ResizableBox(const labeliser::Box& box, sf::Color color, bool assumUnchanged, const std::string& name) :
		ResizableBox(box.getBeggin(), box.getEnd(), color, assumUnchanged, name) {
}

ResizableBox::ResizableBox(double x1, double y1, double z1, double x2, double y2, double z2, sf::Color color, bool assumUnchanged,
		const std::string& name) :
		Box(x1, y1, z1, x2, y2, z2, color, name) {

	Vector3d extr1 = Vector3d(getExtr1());
	Vector3d extr2 = Vector3d(getExtr2());

	setExremities(extr1, extr2, assumUnchanged);
	setCallBack([](const sf::Event&, bool, const Vector3d&, const Vector3d&) {});
}

ResizableBox::ResizableBox(const std::array<double, 3>& coords1, const std::array<double, 3>& coords2, sf::Color color, bool assumUnchanged,
		const std::string& name) :
		ResizableBox(coords1[0], coords1[1], coords1[2], coords2[0], coords2[1], coords2[2], color, assumUnchanged, name) {
}

ResizableBox::ResizableBox(const Vector3d& coords1, const Vector3d& coords2, sf::Color color, bool assumUnchanged, const std::string& name) :
		ResizableBox(coords1[0], coords1[1], coords1[2], coords2[0], coords2[1], coords2[2], color, assumUnchanged, name) {
}

ResizableBox::ResizableBox(const std::array<double, 6>& coords, sf::Color color, bool assumUnchanged, const std::string& name) :
		ResizableBox(coords[0], coords[1], coords[2], coords[3], coords[4], coords[5], color, assumUnchanged, name) {
}

ResizableBox::~ResizableBox() {
}

void ResizableBox::setExremities(Vector3d& extr1, Vector3d& extr2, bool assumUnchanged) {
	Box::setExtreminties(extr1, extr2);

	baryCenter = (extr1 + extr2) / 2.0;

	if (!assumUnchanged)
		resized = true;
}

void ResizableBox::setCallBack(const std::function<void(const sf::Event&, bool, const Vector3d&, const Vector3d&)>& callBack) {
	Box::callBack = [this, callBack](const sf::Event& event, bool ctrlEnable, const Vector3d& beggin, const Vector3d& end) {
		callBack(event, clicked, beggin, end);
		pollEvent(event, ctrlEnable, beggin, end);
	};
}

void ResizableBox::setChangeCallback(const std::function<void()>& callback) {
	Box::setChangeCallback([this, callback]() {
		if (resized || deleted || renamed)
		callback();
		resized = false;
	});
}

bool ResizableBox::isResized() const {
	return resized;
}

bool ResizableBox::isRenamed() const {
	return renamed;
}

void ResizableBox::setName(const std::string& name) {
	Box::setName(name);
	renamed = true;
}

void ResizableBox::setRenameCallBack(const std::function<void(ResizableBox&)>& onRename) {
	this->onRename = onRename;
}

void ResizableBox::setDeleteCallBack(const std::function<void(ResizableBox&)>& onDelete) {
	this->onDelete = onDelete;
}

bool ResizableBox::isDeleted() const {
	return deleted;
}

void ResizableBox::pollEvent(const sf::Event& event, bool ctrlEnable, const ::Vector3d& beggin, const ::Vector3d& end) {
	if (!Box::isDisplayed())
		return;

	if (boxIntersect || mouseOver || cornerIntersect)
		utils::windows::Cursor::setCursor(utils::windows::Cursor::MOUSE);

	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			clicked = false;

			if (outside)
				unselect();
		}
	} else if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			clicked = true;

			Vector3d extr1 = Vector3d(getExtr1());
			Vector3d extr2 = Vector3d(getExtr2());

			if (cornerIntersect) {
				dirResize.empty();
				double cornerIndexMod = cornerIndex % 4;

				if (cornerIndex < 4)
					dirResize[2] = extr1[2];
				else
					dirResize[2] = extr2[2];

				if (cornerIndexMod == 0 || cornerIndexMod == 1)
					dirResize[0] = extr1[0];
				else
					dirResize[0] = extr2[0];

				if (cornerIndexMod == 1 || cornerIndexMod == 2)
					dirResize[1] = extr2[1];
				else
					dirResize[1] = extr1[1];

				dirResize -= (extr1 + extr2) / 2.;
				dirResize.normalize();
			} else if (boxIntersect) {
				dirResize = baryCenter;
				double boxIndexMod = boxIndex % 4;

				if (boxIndex < 4)
					dirResize[2] = extr1[2];
				else if (boxIndex < 8)
					dirResize[2] = extr2[2];

				if (boxIndexMod == 0 || boxIndex == 9)
					dirResize[0] = extr1[0];
				else if (boxIndexMod == 2 || boxIndex == 11)
					dirResize[0] = extr2[0];

				if (boxIndexMod == 1 || boxIndex == 10)
					dirResize[1] = extr2[1];
				else if (boxIndexMod == 3 || boxIndex == 8)
					dirResize[1] = extr1[1];

				dirResize -= (extr1 + extr2) / 2.;
				dirResize.normalize();
			} else {
				dirResize = baryCenter;
				double boxIndexMod = boxIndex % 4;

				if (face == 0)
					dirResize[2] = extr1[2];
				else if (face == 5)
					dirResize[2] = extr2[2];

				if (face == 1)
					dirResize[0] = extr1[0];
				else if (face == 3)
					dirResize[0] = extr2[0];

				if (face == 2)
					dirResize[1] = extr2[1];
				else if (face == 4)
					dirResize[1] = extr1[1];

				dirResize -= (extr1 + extr2) / 2.;
				dirResize.normalize();
			}
		}
	} else if (event.type == sf::Event::MouseMoved) {
		if (clicked) {
			Vector3d vec;
			vec = end - beggin;
			vec.normalize();

			double dScalV = vec * dirResize;

			double t = (beggin - baryCenter) * (vec * dScalV - dirResize) / (pow(dScalV, 2) - 1);
			if (t <= 0)
				t = 0.000001;

			Vector3d extr1 = Vector3d(getExtr1());
			Vector3d extr2 = Vector3d(getExtr2());

			if (ctrlEnable) {
				if (dirResize[0] < 0) {
					double dist = extr1[0] - extr2[0];
					extr2[0] = dirResize[0] * t + baryCenter[0];
					extr1[0] = extr2[0] + dist;
				} else if (dirResize[0] > 0) {
					double dist = extr2[0] - extr1[0];
					extr1[0] = dirResize[0] * t + baryCenter[0];
					extr2[0] = extr1[0] + dist;
				}

				if (dirResize[1] < 0) {
					double dist = extr1[1] - extr2[1];
					extr2[1] = dirResize[1] * t + baryCenter[1];
					extr1[1] = extr2[1] + dist;
				} else if (dirResize[1] > 0) {
					double dist = extr2[1] - extr1[1];
					extr1[1] = dirResize[1] * t + baryCenter[1];
					extr2[1] = extr1[1] + dist;
				}

				if (dirResize[2] < 0) {
					double dist = extr1[2] - extr2[2];
					extr2[2] = dirResize[2] * t + baryCenter[2];
					extr1[2] = extr2[2] + dist;
				} else if (dirResize[2] > 0) {
					double dist = extr2[2] - extr1[2];
					extr1[2] = dirResize[2] * t + baryCenter[2];
					extr2[2] = extr1[2] + dist;
				}
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
				if (dirResize[0] < 0) {
					extr2[0] = dirResize[0] * t + baryCenter[0];
					extr1[0] = -dirResize[0] * t + baryCenter[0];
				} else if (dirResize[0] > 0) {
					extr1[0] = dirResize[0] * t + baryCenter[0];
					extr2[0] = -dirResize[0] * t + baryCenter[0];
				}

				if (dirResize[1] < 0) {
					extr2[1] = dirResize[1] * t + baryCenter[1];
					extr1[1] = -dirResize[1] * t + baryCenter[1];
				} else if (dirResize[1] > 0) {
					extr1[1] = dirResize[1] * t + baryCenter[1];
					extr2[1] = -dirResize[1] * t + baryCenter[1];
				}

				if (dirResize[2] < 0) {
					extr2[2] = dirResize[2] * t + baryCenter[2];
					extr1[2] = -dirResize[2] * t + baryCenter[2];
				} else if (dirResize[2] > 0) {
					extr1[2] = dirResize[2] * t + baryCenter[2];
					extr2[2] = -dirResize[2] * t + baryCenter[2];
				}
			} else {
				if (dirResize[0] < 0)
					extr2[0] = dirResize[0] * t + baryCenter[0];
				else if (dirResize[0] > 0)
					extr1[0] = dirResize[0] * t + baryCenter[0];

				if (dirResize[1] < 0)
					extr2[1] = dirResize[1] * t + baryCenter[1];
				else if (dirResize[1] > 0)
					extr1[1] = dirResize[1] * t + baryCenter[1];

				if (dirResize[2] < 0)
					extr2[2] = dirResize[2] * t + baryCenter[2];
				else if (dirResize[2] > 0)
					extr1[2] = dirResize[2] * t + baryCenter[2];
			}

			setExremities(extr1, extr2);
		}
	} else if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::R) {
			if (ctrlEnable) {
				onRename(*this);
			}
		} else if (event.key.code == sf::Keyboard::Delete) {
			if (!deleted) {
				deleted = true;
				color.a = 20;
				onDelete(*this);
			}
		}
	}
}

std::tuple<Vector3d, double> ResizableBox::getIntersection(const Vector3d& beggin, const Vector3d& vec) {
	if (!Box::isDisplayed())
		return std::tuple<Vector3d, double>(Vector3d(), std::numeric_limits<double>::max());

	std::tuple<Vector3d, double> result;
	std::get<0>(result) = Vector3d( { 0.0, 0.0, 0.0 });
	std::get<1>(result) = std::numeric_limits<double>::max();

	std::tuple<Vector3d, double> inter;

	if (!clicked)
		unselect();

	unsigned short index = 0;

	result = Box::getIntersection(beggin, vec);

	static std::array<std::array<unsigned short, 4>, 6> corners = { std::array<unsigned short, 4> { 0, 1, 2, 3 }, std::array<unsigned short,
			4> { 0, 1, 5, 4 }, std::array<unsigned short, 4> { 1, 2, 6, 5 }, std::array<unsigned short, 4> { 2, 3, 7, 6 }, std::array<
			unsigned short, 4> { 0, 3, 7, 4 }, std::array<unsigned short, 4> { 4, 5, 6, 7 } };

	static std::array<std::array<unsigned short, 4>, 6> vertexes = { std::array<unsigned short, 4> { 0, 1, 2, 3 }, std::array<
			unsigned short, 4> { 0, 9, 4, 8 }, std::array<unsigned short, 4> { 1, 10, 5, 9 },
			std::array<unsigned short, 4> { 2, 11, 6, 10 }, std::array<unsigned short, 4> { 3, 11, 7, 8 }, std::array<unsigned short, 4> {
					4, 5, 6, 7 } };

	if (!clicked)
		if (std::get<1>(result) != std::numeric_limits<double>::max()) {
			auto& point = std::get<0>(result);
			std::array<unsigned short, 4>& faceCorners = corners[face];
			double faceSize = std::min((A[faceCorners[1]] - A[faceCorners[0]]).getNorm(),
					(A[faceCorners[2]] - A[faceCorners[1]]).getNorm());

			for (unsigned int i = 0; i < 4; ++i)
				if ((A[faceCorners[i]] - point).getNorm() < faceSize * 0.2) {
					cornerIntersect = true;
					cornerIndex = faceCorners[i];
					break;
				}

			if (!cornerIntersect)
				for (unsigned int i = 0; i < 4; ++i) {
					auto vertex = (A[faceCorners[(i + 1) % 4]] - A[faceCorners[i]]).normalized();
					auto point2 = point - A[faceCorners[i]];

					if ((point2 - (point2 * vertex) * vertex).getNorm() < faceSize * 0.2) {
						boxIntersect = true;
						boxIndex = vertexes[face][i];
						break;
					}
				}

			if (!boxIntersect)
				mouseOver = true;

		}

	outside = std::get<1>(result) == std::numeric_limits<double>::max();

	if (clicked)
		return std::tuple<Vector3d, double> { std::get<0>(lastResult), 0.0 };

	lastResult = result;

	return result;
}

void ResizableBox::draw(const std::array<GLdouble, 16>& modelview, double zoom) const {
	if (!Box::displayFlag)
		return;

	glDepthMask(GL_TRUE);

	if (boxIntersect || mouseOver || cornerIntersect) {
		++const_cast<unsigned int&>(timeStamp);

		constexpr unsigned int maxTimeStamp = 30;

		const_cast<unsigned int&>(timeStamp) %= maxTimeStamp;

		glPushMatrix();
		{
			if (boxIntersect) {
				double boxIndexMod4 = boxIndex % 4;

				if (boxIndexMod4 == 0 || boxIndex == 9)
					glTranslated(x1, 0., 0.);
				else if (boxIndexMod4 == 2 || boxIndex == 11)
					glTranslated(x2, 0., 0.);
				else
					glTranslated((x1 + x2) / 2., 0., 0.);

				if (boxIndex == 3 || boxIndex == 7 || boxIndex == 8 || boxIndex == 11)
					glTranslated(0., y1, 0.);
				else if (boxIndex == 1 || boxIndex == 5 || boxIndex == 9 || boxIndex == 10)
					glTranslated(0., y2, 0.);
				else
					glTranslated(0., (y2 + y1) / 2., 0.);

				if (boxIndex < 4)
					glTranslated(0., 0., z1);
				else if (boxIndex < 8)
					glTranslated(0., 0., z2);
				else
					glTranslated(0., 0., (z1 + z2) / 2.);
			} else if (cornerIntersect) {
				if (cornerIndex < 2 || cornerIndex == 4 || cornerIndex == 5)
					glTranslated(x1, 0., 0.);
				else
					glTranslated(x2, 0., 0.);

				if (cornerIndex == 1 || cornerIndex == 2 || cornerIndex == 5 || cornerIndex == 6)
					glTranslated(0., y2, 0.);
				else
					glTranslated(0., y1, 0.);

				if (cornerIndex < 4)
					glTranslated(0., 0., z1);
				else
					glTranslated(0., 0., z2);
			} else {
				if (face == 0)
					glTranslated(0., 0., z1);
				else if (face == 5)
					glTranslated(0., 0., z2);
				else
					glTranslated(0., 0., (z1 + z2) / 2.);

				if (face == 1)
					glTranslated(x1, 0., 0.);
				else if (face == 3)
					glTranslated(x2, 0., 0.);
				else
					glTranslated((x1 + x2) / 2., 0., 0.);

				if (face == 4)
					glTranslated(0., y1, 0.);
				else if (face == 2)
					glTranslated(0., y2, 0.);
				else
					glTranslated(0., (y1 + y2) / 2., 0.);
			}

			constexpr double sqrt2D2 = sqrt(2.) / 2.;
			Vector3d arrow;

			if (boxIntersect) {
				glRotated(-90.0 * (boxIndex % 4), 0.0, 0.0, 1.0);

				if (boxIndex < 4)
					glRotated(-45.0, 0.0, 1.0, 0.0);
				else if (boxIndex < 8)
					glRotated(45.0, 0.0, 1.0, 0.0);
				else {
					glRotated(45.0, 0.0, 0.0, 1.0);
					glRotated(90.0, 1.0, 0.0, 0.0);
				}
			} else if (cornerIntersect) {
				glRotated(-90.0 * ((cornerIndex + 1) % 4), 0.0, 0.0, 1.0);

				glRotated(-45.0, 0.0, 0.0, 1.0);

				if (cornerIndex < 4)
					glRotated(225.0, 0.0, 1.0, 0.0);
				else
					glRotated(135.0, 0.0, 1.0, 0.0);

			} else {
				if (face != 0 && face != 5)
					glRotated(-90.0 * (face - 1), 0.0, 0.0, 1.0);
				else if (face == 0)
					glRotated(-90.0, 0.0, 1.0, 0.0);
				else
					glRotated(90.0, 0.0, 1.0, 0.0);
			}

			auto b1 = Box(Vector3d( { 0.0, -0.001, -0.001 }), Vector3d( { 0.02, 0.001, 0.001 }), color, "");
			b1.display();

			double norm = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)) * 5.;
			double anim = exp(-pow(timeStamp - maxTimeStamp / 2.0, 2) / maxTimeStamp) / 40.0;

			if (clicked)
				anim = 0.03;

			glScaled(norm, norm, norm);

			glPushMatrix();
			{
				glRotated(180.0, 0.0, 0.0, 1.0);
				drawArrow(norm, anim, modelview, zoom, b1);
			}
			glPopMatrix();
			b1.setColor(sf::Color(color.r / 4., color.g / 4., color.b / 4., color.a * (clicked ? 1.0 / 4.0 : 20.0 * (0.025 - anim))));
			drawArrow(norm, anim, modelview, zoom, b1);
		}
		glPopMatrix();

	} else
		const_cast<bool&>(clicked) = false;

	Box::draw(modelview, zoom);
}

void ResizableBox::drawArrow(double norm, double anim, const std::array<GLdouble, 16>& modelview, double zoom, Box& box) const {
	glPushMatrix();
	{
		glTranslated(-0.02 - anim, 0.0, 0.0);
		glRotated(45.0, 0.0, 1.0, 0.0);
		box.draw(modelview, zoom);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(-0.02 - anim, 0.0, 0.0);
		glRotated(-45.0, 0.0, 1.0, 0.0);
		box.draw(modelview, zoom);
	}
	glPopMatrix();
}

} /* namespace utils */
