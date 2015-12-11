/*
 * Plot3d.cpp
 *
 *  Created on: 2 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "Plot3d.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vxl/core/vnl/algo/vnl_matrix_inverse.h>
#include <vxl/core/vnl/vnl_matrix.h>
#include <iostream>
#include <cmath>
#include <iterator>

#include "line/Line.h"
#include "point/exception/EmptyLabelDrawerFunctionException.h"
#include "point/Point.h"
#include "point/ScenePoint.h"
#include "box/Box.h"
#include "point/Selector.h"
#include "../../../../utils/window/Cursor.h"
#include "../../../../utils/math/math.h"

namespace window {

constexpr float Plot3d::scale;

Plot3d::Plot3d(const Vector3d& camera, const Vector3d& cameraCenter, float xTrans, float yTrans, float zTrans, const sf::Color& backgroud,
		const uint8_t& borders) :
		backgroud(backgroud), Layer(borders), xAxisLine(utils::Line::createLine(axisCenter, xAxisPoint, sf::Color(255, 0, 0), 0.0001f)), yAxisLine(
				utils::Line::createLine(axisCenter, yAxisPoint, sf::Color(0, 255, 0), 0.0001f)), zAxisLine(
				utils::Line::createLine(axisCenter, zAxisPoint, sf::Color(0, 0, 255), 0.0001f)), camera(camera), rotations(), translation(
				cameraCenter) {
	cameraUp = camera;
	cameraUp.normalize();
	cameraUp = (cameraUp ^ Vector3d::zAxis) ^ cameraUp;
	cameraUp.normalize();
}

void Plot3d::setSelector(const std::shared_ptr<point::Selector>& selector) {
	this->selector = selector;
}

void Plot3d::update() {
}

void Plot3d::hideAxis() {
	showAxis = false;
}

void Plot3d::displayAxis() {
	showAxis = true;
}

const std::vector<std::shared_ptr<utils::Point>>& Plot3d::getPoints() const {
	return points;
}

std::array<Vector3d, 2> Plot3d::getViewFinder(double x, double y, double width, double height, double xCoord, double yCoord) const {
	GLdouble windowCoordX, windowCoordY, windowCoordZ;

	Vector3d beggin;
	Vector3d end;

	windowCoordX = viewport[0] + xCoord + x;
	windowCoordY = height + viewport[1] - yCoord + y;

	gluUnProject(windowCoordX, windowCoordY, 0, &modelview.front(), &projection.front(), &viewport.front(), &beggin[0], &beggin[1],
			&beggin[2]);

	gluUnProject(windowCoordX, windowCoordY, 1, &modelview.front(), &projection.front(), &viewport.front(), &end[0], &end[1], &end[2]);

	return {beggin, end};
}

void Plot3d::disable() {
	disableFlag = true;
}

void Plot3d::enable() {
	disableFlag = false;
}

const std::shared_ptr<point::Selector>& Plot3d::getSelector() {
	return selector;
}

void Plot3d::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		switch (event.mouseButton.button) {
		case sf::Mouse::Right:
			if (state && (InTranslation | Animated))
				break;

			if (!insidePlot)
				break;

			state |= InRotation;
			cameraInit = camera;
			cameraUpInit = cameraUp;
			xInit = event.mouseButton.x;
			yInit = event.mouseButton.y;
			break;

		case sf::Mouse::Middle:
			if (state && (InRotation | Animated))
				break;

			if (!insidePlot)
				break;

			state |= InTranslation;
			transTimeStamp = 0;
			cameraInit = translation;
			xInit = event.mouseButton.x;
			yInit = event.mouseButton.y;
			break;

		case sf::Mouse::Left: {
			if (((state & InRotation) || (state & InTranslation)) && !(state & Animated))
				break;

			if (!insidePlot)
				break;

			if (disableFlag)
				break;

			std::array<Vector3d, 2> vec = getViewFinder(x, y, width, height, event.mouseButton.x, event.mouseButton.y);
			std::tuple<std::shared_ptr<utils::Point>, double> point = getNearestPoint(vec[0], vec[1]);
			std::tuple<std::shared_ptr<utils::Box>, double> box = getNearestBox(vec[0], vec[1]);

			if (std::get<1>(point) > std::get<1>(box))
				std::get<0>(point) = nullptr;
			else if (std::get<0>(box) != nullptr) {
				std::get<0>(box)->unselect();
				std::get<0>(box) = nullptr;
			}

			bool ctrlEnable = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

			if (std::get<0>(point) != nullptr && std::get<0>(point)->getCallBack() != nullptr)
				(*std::get<0>(point)->getCallBack())(event, ctrlEnable);
			else {
				if (std::get<0>(point) == nullptr && selector != nullptr && !ctrlEnable)
					selector->endSelection();

				if (std::get<0>(box) != nullptr)
					std::get<0>(box)->getCallBack()(event, ctrlEnable, vec[0], vec[1]);
			}
		}
			break;

		default:
			break;
		}
		break;

	case sf::Event::MouseButtonReleased:
		switch (event.mouseButton.button) {
		case sf::Mouse::Right:
			if (!(state & Animated))
				state &= ~InRotation;
			break;

		case sf::Mouse::Middle: {
			if (!(state & Animated))
				state &= ~InTranslation;
		}
			break;

		case sf::Mouse::Left: {

			if (((state & InRotation) || (state & InTranslation)) && !(state & Animated))
				break;

			if (!insidePlot)
				break;

			if (disableFlag)
				break;

			std::array<Vector3d, 2> vec = getViewFinder(x, y, width, height, event.mouseButton.x, event.mouseButton.y);
			std::tuple<std::shared_ptr<utils::Point>, double> point = getNearestPoint(vec[0], vec[1]);
			std::tuple<std::shared_ptr<utils::Box>, double> box = getNearestBox(vec[0], vec[1]);

			if (std::get<1>(point) > std::get<1>(box))
				std::get<0>(point) = nullptr;
			else if (std::get<0>(box) != nullptr) {
				std::get<0>(box)->unselect();
				std::get<0>(box) = nullptr;
			}

			bool ctrlEnable = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

			if (std::get<0>(point) != nullptr && std::get<0>(point)->getCallBack() != nullptr)
				(*std::get<0>(point)->getCallBack())(event, ctrlEnable);
			else {
				if (std::get<0>(point) == nullptr && selector != nullptr && !ctrlEnable)
					selector->endSelection();

				if (std::get<0>(box) != nullptr)
					std::get<0>(box)->getCallBack()(event, ctrlEnable, vec[0], vec[1]);
			}
		}
			break;

		default:
			break;
		}
		break;

	case sf::Event::MouseMoved:
		insidePlot = !(event.mouseMove.x > width + x || event.mouseMove.x < x || event.mouseMove.y > height + y || event.mouseMove.y < y);

		if ((state & InRotation) && (state & ~Animated)) {
			constexpr float inv360 = 1.f / 360.f;

			camera = cameraInit;
			cameraUp = cameraUpInit;
			rotateCamera(Vector3d::zAxis, (xInit - event.mouseMove.x) * 0.005);
			Vector3d camX = Vector3d(camera).normalized() ^ cameraUp;
			camX.normalize();
			rotateCamera(camX, (yInit - event.mouseMove.y) * 0.005);

		} else if ((state & InTranslation) && (state & ~Animated)) {
			if (transTimeStamp < transTimeStampMax)
				break;

			constexpr double cst = 1.2;
			translation = cameraInit;
			double xView = (event.mouseMove.x - xInit) / width * cst * exp(pow(this->zoom / 26.4, 2));
			double yView = (yInit - event.mouseMove.y) / height * cst * exp(pow(this->zoom / 26.4, 2));

			Vector3d camX, camY;

			Vector3d camAxis = camera.normalized();
			camX = camAxis ^ cameraUp;
			camX.normalize();
			camY = camX ^ camAxis;
			camY *= yView * cst;
			camX *= xView * cst;

			translation += camX + camY;

		} else {

			if (disableFlag)
				break;

			if (!insidePlot)
				break;

			std::array<Vector3d, 2> vec = getViewFinder(x, y, width, height, event.mouseMove.x, event.mouseMove.y);
			std::tuple<std::shared_ptr<utils::Point>, double> point = getNearestPoint(vec[0], vec[1]);
			boxSelected = getNearestBox(vec[0], vec[1]);

			if (std::get<1>(point) > std::get<1>(boxSelected))
				std::get<0>(point) = nullptr;
			else if (std::get<0>(boxSelected) != nullptr) {
				std::get<0>(boxSelected)->unselect();
				std::get<0>(boxSelected) = nullptr;
			}

			bool ctrlEnable = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

			if (std::get<0>(point) != nullptr && std::get<0>(point)->getCallBack() != nullptr)
				(*std::get<0>(point)->getCallBack())(event, ctrlEnable);
			else if (std::get<0>(boxSelected) != nullptr)
				std::get<0>(boxSelected)->getCallBack()(event, ctrlEnable, vec[0], vec[1]);
		}
		break;

	case sf::Event::MouseWheelScrolled:
		if (!insidePlot)
			break;

		if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			if (zoom - event.mouseWheelScroll.delta > 0)
				zoom -= event.mouseWheelScroll.delta;
			else
				zoom = 0;
		break;

	case sf::Event::KeyPressed: {
		bool ctrlEnable = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

		if (std::get<0>(boxSelected) != nullptr)
			std::get<0>(boxSelected)->getCallBack()(event, ctrlEnable, Vector3d::center, Vector3d::center);
	}

		switch (event.key.code) {
		case sf::Keyboard::C:
			if (state == Default)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
					state = Animated | InTranslation;

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
						translationEnd = Vector3d::center;

						for (const auto& point : points)
							translationEnd -= point->getPosition();

						translationEnd /= points.size() / 10.;
					} else
						translationEnd = Vector3d::center;

					translationInit = translation;
					animTimeStamp = 0;
				}
			break;

		case sf::Keyboard::X:
			if (state == Default)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
					Vector3d axis = Vector3d::xAxis;
					std::tuple<double, Vector3d> rot;
					cameraInit = camera;
					cameraUpInit = cameraUp;
					animTimeStamp = 0;
					state = Animated | InRotation;
					Vector3d camUp = cameraUpInit;
					Vector3d cam = cameraInit;

					if (camera != axis) {
						if (camera == -axis)
							rot = std::tuple<double, Vector3d> { M_PI, cameraUp };
						else
							rot = cameraInit.getRotationWith(axis);

						rotations.push_back(rot);

						camUp.rotate(std::get<1>(rot), std::get<0>(rot));
						cam.rotate(std::get<1>(rot), std::get<0>(rot));
					}

					if (camUp != Vector3d::zAxis) {
						if (camUp == -Vector3d::zAxis)
							rot = std::tuple<double, Vector3d> { M_PI, cam };
						else
							rot = camUp.getRotationWith(Vector3d::zAxis);

						rotations.push_back(rot);
					}
				}
			break;

		case sf::Keyboard::Y:
			if (state == Default)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
					Vector3d axis = Vector3d::yAxis;
					std::tuple<double, Vector3d> rot;
					cameraInit = camera;
					cameraUpInit = cameraUp;
					animTimeStamp = 0;
					state = Animated | InRotation;
					Vector3d camUp = cameraUpInit;
					Vector3d cam = cameraInit;

					if (camera != axis) {
						if (camera == -axis)
							rot = std::tuple<double, Vector3d> { M_PI, cameraUp };
						else
							rot = cameraInit.getRotationWith(axis);

						rotations.push_back(rot);

						camUp.rotate(std::get<1>(rot), std::get<0>(rot));
						cam.rotate(std::get<1>(rot), std::get<0>(rot));
					}

					if (camUp != Vector3d::zAxis) {
						if (camUp == -Vector3d::zAxis)
							rot = std::tuple<double, Vector3d> { M_PI, cam };
						else
							rot = camUp.getRotationWith(Vector3d::zAxis);

						rotations.push_back(rot);
					}
				}
			break;

		case sf::Keyboard::Z:
			if (state == Default)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
					Vector3d axis = Vector3d::zAxis;
					std::tuple<double, Vector3d> rot;
					cameraInit = camera;
					cameraUpInit = cameraUp;
					animTimeStamp = 0;
					state = Animated | InRotation;
					Vector3d camUp = cameraUpInit;
					Vector3d cam = cameraInit;

					if (camera != axis) {
						if (camera == -axis)
							rot = std::tuple<double, Vector3d> { M_PI, cameraUp };
						else
							rot = cameraInit.getRotationWith(axis);

						rotations.push_back(rot);

						camUp.rotate(std::get<1>(rot), std::get<0>(rot));
						cam.rotate(std::get<1>(rot), std::get<0>(rot));
					}

					if (camUp != Vector3d::yAxis) {
						if (camUp == -Vector3d::yAxis)
							rot = std::tuple<double, Vector3d> { M_PI, cam };
						else
							rot = camUp.getRotationWith(Vector3d::yAxis);

						rotations.push_back(rot);
					}
				}
			break;
		}
		break;

	case sf::Event::KeyReleased:
		break;

	default:
		break;
	}
}

std::tuple<std::shared_ptr<utils::Box>, double> Plot3d::getNearestBox(const Vector3d& beggin, const Vector3d& end) {
	Vector3d vec;
	vec = end - beggin;
	vec.normalize();

	double tmin = std::numeric_limits<double>::max();
	std::shared_ptr<utils::Box> box = nullptr;

	for (auto boxIt : boxes) {
		if (!boxIt->isDisplayed() || !boxIt->isSelectable())
			continue;

		std::tuple<Vector3d, double> inter = boxIt->getIntersection(beggin, vec);

		if (std::get<1>(inter) < tmin) {
			tmin = std::get<1>(inter);

			if (box != nullptr)
				box->unselect();

			box = boxIt;
		} else
			boxIt->unselect();
	}

	return std::tuple<std::shared_ptr<utils::Box>, double> { box, tmin };
}

std::tuple<std::shared_ptr<utils::Point>, double> Plot3d::getNearestPoint(const Vector3d& beggin, const Vector3d& end) {
	Vector3d vec;
	vec = end - beggin;
	vec.normalize();

	double tmin = std::numeric_limits<double>::max();
	std::shared_ptr<utils::Point> point = nullptr;

	for (auto pointIt : points) {
		if (!pointIt->isDisplayed() || !pointIt->isSelectable())
			continue;

		std::tuple<Vector3d, double> inter =
				utils::Box(Vector3d( { 1.0, -1.0, 1.0 }) * (double) pointIt->getSize() + pointIt->getPosition(),
						Vector3d( { -1.0, 1.0, -1.0 }) * (double) pointIt->getSize() + pointIt->getPosition(), sf::Color(0, 0, 0), "").getIntersection(
						beggin, vec);

		if (std::get<1>(inter) < tmin) {
			tmin = std::get<1>(inter);

			point = pointIt;
		}
	}

	return std::tuple<std::shared_ptr<utils::Point>, double> { point, tmin };
}

void Plot3d::rotateCamera(const Vector3d& axis, double angle) {
	if (std::isnan(axis.getNorm()))
		return;
	camera.rotate(axis, angle);
	cameraUp.rotate(axis, angle);
}

void Plot3d::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	if (transTimeStamp < transTimeStampMax)
		++transTimeStamp;

	if (animTimeStamp < animTimeStampMax)
		++animTimeStamp;

	if (state & Animated) {
		constexpr double expM1 = exp(-1.);
		constexpr double cst = 1. / (1. - exp(-1.));
		double fact = 1. - (exp(-pow(((double) animTimeStamp) / animTimeStampMax, 2)) - expM1) * cst;

		if (state & InRotation) {
			camera = cameraInit;
			cameraUp = cameraUpInit;

			for (const auto& rot : rotations)
				rotateCamera(std::get<1>(rot), std::get<0>(rot) * fact);

			if (animTimeStamp == animTimeStampMax) {
				state = Default;
				rotations.clear();
			}
		} else if (state & InTranslation) {
			translation = translationInit + (translationEnd - translationInit) * fact;
			if (animTimeStamp == animTimeStampMax)
				state = Default;
		}
	}

	sf::Vector2u windowSize = window->getSize();

	Layer::draw(window, x, y, width, height);

	window->popGLStates();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.f, width / height, 1.f, 500.f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(x, windowSize.y - (height + y), width, height);
		glLoadIdentity();

		double zoom = exp(pow(this->zoom / 26.4, 2)) * 0.1;
		gluLookAt(camera[0] * zoom - translation[0], camera[1] * zoom - translation[1], camera[2] * zoom - translation[2], -translation[0],
				-translation[1], -translation[2], cameraUp[0], cameraUp[1], cameraUp[2]);

		glPushMatrix();
		{
			glScalef(scale, scale, scale);

			for (auto point = this->points.end() - 1; point != this->points.begin() - 1; --point)
				if ((*point)->isSuppressed())
					this->points.erase(point);
				else
					(*point)->draw3d();

			::Vector3d cameraRight = camera ^ cameraUp;
			cameraRight.normalize();

			for (auto point = this->points.end() - 1; point != this->points.begin() - 1; --point)
				if ((*point)->isLabelEnable())
					try {
						(*point)->drawLabel(window, cameraRight, cameraUp, width, height);
					} catch (const exception::EmptyLabelDrawerFunctionException&) {
					}

			glGetDoublev(GL_MODELVIEW_MATRIX, const_cast<GLdouble*>(&modelview.front()));
			glGetDoublev(GL_PROJECTION_MATRIX, const_cast<GLdouble*>(&projection.front()));
			glGetIntegerv(GL_VIEWPORT, const_cast<GLint*>(&viewport.front()));

			for (auto line = this->lines.end() - 1; line != this->lines.begin() - 1; --line)
				if ((*line)->isSuppressed())
					this->lines.erase(line);
				else
					(*line)->draw(zoom);

			for (auto box : boxes) {
				glDepthMask(GL_FALSE);
				box->draw(modelview, zoom);
				glDepthMask(GL_TRUE);
			}
			/*if (showAxis) {
			 xAxisLine->draw(modelview, zoom);
			 yAxisLine->draw(modelview, zoom);
			 zAxisLine->draw(modelview, zoom);
			 }*/

		}
		glPopMatrix();

		if (showAxis) {
			glPushMatrix();
			{
				glLoadIdentity();
				Vector3d camera = this->camera;
				camera.normalize();

				camera *= 10.;

				gluLookAt(camera[0], camera[1], camera[2], 0, 0, 0, cameraUp[0], cameraUp[1], cameraUp[2]);

				glScalef(scale, scale, scale);

				constexpr double expInit = exp(125.f / 50.f);

				xAxisLine->draw(expInit);
				yAxisLine->draw(expInit);
				zAxisLine->draw(expInit);
			}
			glPopMatrix();
		}

		glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);
	}
	glPopMatrix();
	glFlush();

	window->pushGLStates();
}

void Plot3d::addLineToPlot(const std::shared_ptr<utils::Line>& line) {
	lines.push_back(line);
}

void Plot3d::addPointToPlot(const std::shared_ptr<utils::Point>& point) {
	this->points.push_back(point);
}

void Plot3d::addBoxToPlot(const std::shared_ptr<utils::Box>& box) {
	this->boxes.push_back(box);
}

void Plot3d::clear() {
	points.clear();
	lines.clear();
	boxes.clear();
}

Plot3d::~Plot3d() {
}

} /* namespace window */
