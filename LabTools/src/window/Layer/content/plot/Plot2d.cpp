/*
 * Plot2d.cpp
 *
 *  Created on: 2 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "Plot2d.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <tuple>

#include "../../../Window.h"
#include "curve/Curve.h"
#include "line/Line.h"
#include "point/Point.h"
#include "point/Selector.h"

namespace window {

constexpr float Plot2d::scale;

Plot2d::Plot2d(window::Window& window, const sf::Color& backgroud, const uint8_t& borders) :
		backgroud(backgroud), Layer(borders), xAxisLine(utils::Line::createLine(axisCenter, xAxisPoint, sf::Color(255, 0, 0), 0.0001f)), yAxisLine(
				utils::Line::createLine(axisCenter, yAxisPoint, sf::Color(0, 255, 0), 0.0001f)), window(window) {
}

Plot2d::~Plot2d() {
}

void Plot2d::setSelector(const std::shared_ptr<point::Selector>& selector) {
	this->selector = selector;
}

void Plot2d::update() {
}

void Plot2d::hideAxis() {
	showAxis = false;
}

void Plot2d::displayAxis() {
	showAxis = true;
}

const std::vector<std::shared_ptr<utils::Point>>& Plot2d::getPoints() const {
	return points;
}

void Plot2d::disable() {
	disableFlag = true;
}

void Plot2d::enable() {
	disableFlag = false;
}

const std::shared_ptr<point::Selector>& Plot2d::getSelector() {
	return selector;
}

void Plot2d::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	switch (event.type) {
	case sf::Event::MouseWheelScrolled:
		if (!insidePlot)
			break;

		if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
			constexpr double cst = 2. / exp(pow(1. / 2., 2));
			zoom += (event.mouseWheelScroll.delta < 0 ? -1. : 1.) * exp(pow(((double) event.mouseWheelScroll.delta / 2.), 2)) * cst;

			if (zoom < 1)
				zoom = 1;
			else if (zoom > 200)
				zoom = 200;

			translation = 0;
		}
		break;

	case sf::Event::MouseMoved:
		insidePlot = !(event.mouseMove.x > width + x || event.mouseMove.x < x || event.mouseMove.y > height + y || event.mouseMove.y < y);

		if (inTranslation) {
			translation = lastTranslation + (event.mouseMove.x - xInit) * window.getController()->getNbFrames() / width;
			long int frame = window.getController()->getCurrentFrame() + translation;

			if (frame < 1) {
				translation = -window.getController()->getCurrentFrame();
				xInit = event.mouseMove.x;
				lastTranslation = translation;
			} else if (frame > window.getController()->getNbFrames()) {
				translation = window.getController()->getNbFrames() - window.getController()->getCurrentFrame();
				xInit = event.mouseMove.x;
				lastTranslation = translation;
			}

		} else if (inFrameTranslation) {
			int frame = beggin + (event.mouseMove.x - x) * (window.getController()->getNbFrames() - end - beggin) / width;

			if (frame < 0)
				frame = 0;

			window.getController()->goTo(frame);
		} else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
				&& (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
			constexpr double exp1 = exp(pow(1. / 50., 2));
			double zoomScale = exp(pow(zoom / 50., 2)) - exp1 + 1.;
			double timeRatio = width * zoomScale / this->window.getController()->getNbFrames();

			int frame = beggin + (event.mouseMove.x - x) * (window.getController()->getNbFrames() - end - beggin) / width;

			if (frame < 0)
				frame = 0;

			if (this->window.getEditor()->getFirstSelection() != std::numeric_limits<unsigned int>::max()) {
				if (this->window.getEditor()->getLastSelection() == std::numeric_limits<unsigned int>::max())
					window.getEditor()->setFirstSelection(frame);
				else
					window.getEditor()->setLastSelection(frame);
			}
		}

		break;

	case sf::Event::MouseButtonPressed:
		if (!insidePlot) {
			inTranslation = false;
			inFrameTranslation = false;
			translation = lastTranslation = 0;
			/*if (event.mouseButton.button == sf::Mouse::Left)
			 zoom = 1;*/
			break;
		}

		switch (event.mouseButton.button) {
		case sf::Mouse::Right:
			if (inFrameTranslation)
				break;

			inTranslation = true;
			lastTranslation = translation;
			xInit = event.mouseButton.x;
			break;

		case sf::Mouse::Left:
			if (inTranslation)
				break;

			//inFrameTranslation = true;
			translation = 0;
			constexpr double exp1 = exp(pow(1. / 50., 2));
			double zoomScale = exp(pow(zoom / 50., 2)) - exp1 + 1.;
			double timeRatio = width * zoomScale / this->window.getController()->getNbFrames();

			int frame = beggin + (event.mouseButton.x - x) * (window.getController()->getNbFrames() - end - beggin) / width;

			if (frame < 0)
				frame = 0;

			unsigned int firstSelection = this->window.getEditor()->getFirstSelection();
			unsigned int lastSelection = this->window.getEditor()->getLastSelection();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
				if (firstSelection == std::numeric_limits<unsigned int>::max())
					firstSelection = frame;
				else if (lastSelection == std::numeric_limits<unsigned int>::max())
					lastSelection = frame;
				else {
					firstSelection = frame;
					lastSelection = std::numeric_limits<unsigned int>::max();
				}
			} else {
				window.getController()->goTo(frame);
			}

			window.getEditor()->setLastSelection(lastSelection);
			window.getEditor()->setFirstSelection(firstSelection);

			break;
		}
		break;

	case sf::Event::MouseButtonReleased:
		inTranslation = false;
		inFrameTranslation = false;
		break;

	default:
		break;
	}
}

void Plot2d::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	Layer::draw(window, x, y, width, height);

	/*for (auto point = this->points.end() - 1; point != this->points.begin() - 1; --point)
	 if ((*point)->isSuppressed())
	 this->points.erase(point);
	 */

	sf::RectangleShape rec = sf::RectangleShape(sf::Vector2f(width, height));
	rec.setPosition(x, y);
	rec.setFillColor(sf::Color(0, 0, 0, 200));

	window->draw(rec);

	double min = 0;
	double max = 0;
	double nbPointsMax = 0;

	for (const auto& curve : curves) {
		auto minMax = curve->getMinMax();

		if (std::get<0>(minMax) < min)
			min = std::get<0>(minMax);

		if (std::get<1>(minMax) > max)
			max = std::get<1>(minMax);

		double nbPoints = curve->getPoints().size();

		if (nbPoints > nbPointsMax)
			nbPointsMax = nbPoints;
	}

	constexpr double exp1 = exp(pow(1. / 50., 2));
	double zoomScale = exp(pow(zoom / 50., 2)) - exp1 + 1.;
	double ratio = (height - 20.f) / (max - min);
	double timeRatio = width * zoomScale / this->window.getController()->getNbFrames();
	unsigned int jump = std::ceil(5. / timeRatio);

	sf::RectangleShape line = sf::RectangleShape(sf::Vector2f(width, 1.));
	/*if (ratio * max < height - 20.f)
	 line.setPosition(x, y + ratio * max + 10.f);
	 else if (ratio * max > 0)
	 line.setPosition(x, y + height - 10.f);
	 else
	 line.setPosition(x, y + 10.f);

	 line.setFillColor(sf::Color(0, 0, 255, 200));
	 line.setOutlineColor(sf::Color(0, 0, 255, 80));*/
	line.setOutlineThickness(1.);
	//window->draw(line);

	line.setFillColor(sf::Color(255, 255, 255, 80));
	line.setOutlineColor(sf::Color(0, 0, 0, 80));

	line.setPosition(x, y);
	window->draw(line);

	double splitBarPos = (this->window.getController()->getCurrentFrame() + 1 + translation) * width
			/ this->window.getController()->getNbFrames();

	beggin = std::floor(splitBarPos * (zoomScale - 1.) / timeRatio);
	{
		int end = std::floor((width - splitBarPos) * (zoomScale - 1.) / timeRatio);

		if (end < 0)
			this->end = 0;
		else
			this->end = end;
	}

	for (const auto& curve : curves)
		curve->draw(window, x, y + 10.f, width, height - 20.f, max, timeRatio, ratio, jump, beggin, end, true);

	for (const auto& curve : curves)
		curve->draw(window, x, y + 10.f, width, height - 20.f, max, timeRatio, ratio, jump, beggin, end, false);

	double splitBarPos2 = (this->window.getController()->getCurrentFrame() - beggin) * timeRatio;

	if (splitBarPos2 > 0 && splitBarPos2 < width) {
		line.setPosition(sf::Vector2f(x + splitBarPos2, y));
		line.setSize(sf::Vector2f(1., height));
		window->draw(line);
	}

	unsigned int firstSelection = this->window.getEditor()->getFirstSelection();
	unsigned int lastSelection = this->window.getEditor()->getLastSelection();

	double firstSelectionPos = (((long int) firstSelection) - (long int) beggin) * timeRatio;
	double lastSelectionPos = (((long int) lastSelection) - (long int) beggin) * timeRatio;

	sf::RectangleShape rect(sf::Vector2f(6., height));

	if (firstSelection != std::numeric_limits<unsigned int>::max() && (firstSelectionPos > 0 && firstSelectionPos < width)) {
		rect.setFillColor(sf::Color(0, 160, 230, 80));
		rect.setPosition(x + firstSelectionPos - 2., y);
		window->draw(rect);
		rect.move(1., 0);
		rect.setSize(sf::Vector2f(4., height));
		rect.setFillColor(sf::Color(0, 160, 230, 150));
		window->draw(rect);
	}

	if (lastSelection != std::numeric_limits<unsigned int>::max() && (lastSelectionPos > 0 && lastSelectionPos < width)) {
		sf::RectangleShape rect(sf::Vector2f(6., height));
		rect.setFillColor(sf::Color(0, 160, 230, 80));
		rect.setPosition(x + lastSelectionPos - 2., y);
		window->draw(rect);
		rect.move(1., 0);
		rect.setSize(sf::Vector2f(4., height));
		rect.setFillColor(sf::Color(0, 160, 230, 150));
		window->draw(rect);
	}

	if (firstSelection != std::numeric_limits<unsigned int>::max() && lastSelection != std::numeric_limits<unsigned int>::max()) {
		if (firstSelectionPos > lastSelectionPos) {
			double tmp = firstSelectionPos;
			firstSelectionPos = lastSelectionPos;
			lastSelectionPos = tmp;
		}

		if ((firstSelectionPos < width) && (lastSelectionPos > 0)) {
			if (firstSelectionPos < 0)
				firstSelectionPos = 0;

			if (lastSelectionPos > width)
				lastSelectionPos = width;

			rect.setFillColor(sf::Color(0, 160, 230, 150));
			rect.setSize(sf::Vector2f(lastSelectionPos - firstSelectionPos, height));
			rect.setPosition(x + firstSelectionPos, y);
			window->draw(rect);
		}
	}
}

void Plot2d::addLineToPlot(const std::shared_ptr<utils::Line>& line) {
	lines.push_back(line);
}

void Plot2d::addPointToPlot(const std::shared_ptr<utils::Point>& point) {
	this->points.push_back(point);
}

void Plot2d::addCurveToPlot(const std::shared_ptr<utils::Curve>& curve) {
	this->curves.push_back(curve);
}

void Plot2d::clear() {
	zoom = 1.;
	points.clear();
	lines.clear();
	curves.clear();
}

} /* namespace window */
