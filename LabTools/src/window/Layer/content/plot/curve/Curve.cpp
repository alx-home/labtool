/*
 * Curve.cpp
 *
 *  Created on: 10 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "Curve.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iterator>

#include "../../../../../utils/math/math.h"
#include "../line/Line.h"
#include "../point/Point.h"

namespace utils {

Curve::Curve(const sf::Color& color, float linkSize, Axis axis, bool showGapFrames, unsigned int gapFrameSizeMin,
		bool showAccelerationMaxErrors, double accelerationMax, double frameRate) :
		color(color), linkSize(linkSize), axis(axis), showGapFrames(showGapFrames), gapFrameSizeMin(gapFrameSizeMin), showAccelerationMaxErrors(
				showAccelerationMaxErrors), accelerationMax(accelerationMax), frameRate(frameRate) {
}

Curve::~Curve() {
}

std::tuple<double, double> Curve::getMinMax() const {
	double max = 0.;
	double min = std::numeric_limits<double>::max();

	for (const auto& point : points)
		if (point->getPosition()[axis] > max)
			max = point->getPosition()[axis];
		else if (point->getPosition()[axis] < min)
			min = point->getPosition()[axis];

	return std::tuple<double, double> { min, max };
}

void Curve::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height, double max, double timeRatio,
		double ratio, unsigned int jump, unsigned int beggin, unsigned int end, bool firstPass) const {

	if (firstPass) {
		if (showGapFrames)
			for (unsigned int i = 0; i < gapFrames.size(); i += 2) {
				auto frame = gapFrames[i];
				auto begginFrame = frame;
				unsigned int endFrame;

				if (i + 1 == gapFrames.size())
					endFrame = points.size() - end;
				else
					endFrame = gapFrames[i + 1];

				if (endFrame < beggin)
					continue;

				if (begginFrame > points.size() - end)
					break;

				double offsetm = ((double) begginFrame - beggin - 1) * timeRatio;
				double offsetM = ((double) endFrame - beggin) * timeRatio;

				if (offsetM - offsetm < 20) {
					double sizeLack = 10. - (offsetM - offsetm) / 2.;

					offsetm -= sizeLack;
					offsetM += sizeLack;
				}

				if (offsetm < 0)
					offsetm = 0;

				if (offsetM + x > width)
					offsetM = width - x;

				sf::RectangleShape rec;

				rec.setPosition(x + offsetm, y);
				rec.setSize(sf::Vector2f(offsetM - offsetm, height));
				rec.setFillColor(sf::Color(255, 0, 0, 120));

				window->draw(rec);
			}

		if (showAccelerationMaxErrors)
			for (auto frame = accelerationErrors.begin(); frame != accelerationErrors.end(); ++frame) {
				double offset = ((double) *frame - beggin) * timeRatio;
				double widthRect = 20.;
				offset -= 10.;

				if (offset < 0.)
					if (widthRect + offset > 0)
						offset = 0;
					else
						continue;

				if (offset > width)
					continue;

				if (widthRect + offset > width)
					widthRect = width - offset;

				sf::RectangleShape rec;

				rec.setPosition(x + offset, y);
				rec.setSize(sf::Vector2f(widthRect, height));
				rec.setFillColor(sf::Color(245, 100, 20, 120));

				window->draw(rec);
			}
	} else
		for (unsigned int time = beggin; time < points.size() - end;) {
			const auto& point = points[time];
			if (std::isnan(point->getPosition()[axis])) {
				++time;
				continue;
			}

			double xCoords = x + ((double) time) * timeRatio - beggin * timeRatio;
			double yCoords = y - (point->getPosition()[axis] - max) * ratio;
			point->draw2d(window, xCoords, yCoords, width, height);

			if (time + jump > points.size() - end - 1)
				break;

			unsigned int deltaTime = jump;

			if (std::isnan(points[time + jump]->getPosition()[axis])
					|| std::fabs(point->getPosition()[axis] - points[time + jump]->getPosition()[axis]) > 0.01)
				deltaTime = 6;

			time += deltaTime;

			if (time >= points.size() - end)
				time = points.size() - end - 1;

			const auto& point2 = points[time];

			double yCoords2 = y - (point2->getPosition()[axis] - max) * ratio;

			sf::RectangleShape line = sf::RectangleShape(
					sf::Vector2f(sqrt(pow(timeRatio * deltaTime, 2) + pow(yCoords2 - yCoords, 2)), linkSize));
			line.setPosition(xCoords, yCoords);
			line.setFillColor(color);
			line.setRotation(::math::radToDeg * atan2(yCoords2 - yCoords, timeRatio * deltaTime));
			window->draw(line);
		}

}

void Curve::addPoint(const std::shared_ptr<utils::Point>& point) {
	if (std::isnan(point->getPosition()[axis])) {
		if (gapFrames.size() % 2 == 0)
			gapFrames.push_back(points.size());
	} else if (gapFrames.size() % 2 == 1)
		if (points.size() - gapFrames.back() > gapFrameSizeMin)
			gapFrames.push_back(points.size());
		else
			gapFrames.erase(gapFrames.end() - 1);

	double speed1 = std::numeric_limits<double>::max();
	unsigned int speed1Index = 0;

	if (!std::isnan(point->getPosition()[axis])) {
		if (lastLastNotNanFrame != std::numeric_limits<unsigned int>::max()
				&& lastNotNanFrame != std::numeric_limits<unsigned int>::max()) {
			Vector3d speed1 = (point->getPosition() - lastNotNanPoint) * frameRate / (double) (points.size() - lastNotNanFrame);
			Vector3d speed2 = (lastNotNanPoint - lastLastNotNanPoint) * frameRate / (double) (lastNotNanFrame - lastLastNotNanFrame);

			Vector3d acceleration = (speed1 - speed2) / 2.;

			if (acceleration.getNorm() > accelerationMax) {
				accelerationErrors.push_back(lastNotNanFrame);
			}
		}

		lastLastNotNanFrame = lastNotNanFrame;
		lastNotNanFrame = points.size();

		lastLastNotNanPoint = lastNotNanPoint;
		lastNotNanPoint = point->getPosition();
	}

	points.push_back(point);
}

const std::vector<std::shared_ptr<utils::Point> >& Curve::getPoints() const {
	return points;
}

} /* namespace utils */
