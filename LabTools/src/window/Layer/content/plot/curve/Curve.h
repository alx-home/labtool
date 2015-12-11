/*
 * Curve.h
 *
 *  Created on: 10 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_PLOT_CURVE_CURVE_H_
#define SRC_WINDOW_LAYER_CONTENT_PLOT_CURVE_CURVE_H_

#include <SFML/Graphics/Color.hpp>
#include <limits>
#include <memory>
#include <tuple>
#include <vector>

#include "../../../../../utils/math/Vector.h"

namespace sf {
class RenderTarget;
} /* namespace sf */

namespace utils {
class Line;
class Point;
} /* namespace utils */

namespace utils {

class Curve {
public:
	typedef enum {
		X, Y, Z
	} Axis;

	Curve(const sf::Color& color, float linkSize, Axis axis, bool showGapFrames = false, unsigned int gapFrameSizeMin = 0,
			bool showAccelerationMaxErrors = false, double accelerationMax = 0, double frameRate = 0);
	virtual ~Curve();

	void addPoint(const std::shared_ptr<utils::Point>& point);
	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height, double max, double timeRatio,
			double ratio, unsigned int jump, unsigned int beggin, unsigned int end, bool firstPass) const;
	const std::vector<std::shared_ptr<utils::Point> >& getPoints() const;
	std::tuple<double, double> getMinMax() const;

private:
	std::vector<std::shared_ptr<utils::Point>> points = std::vector<std::shared_ptr<utils::Point>>();
	sf::Color color;
	float linkSize;
	Axis axis;
	bool showGapFrames;
	bool showAccelerationMaxErrors;
	unsigned int gapFrameSizeMin;
	double accelerationMax;
	double frameRate;
	std::vector<unsigned int> gapFrames = std::vector<unsigned int>();
	std::vector<unsigned int> accelerationErrors = std::vector<unsigned int>();
	::Vector3d lastNotNanPoint = ::Vector3d::center;
	::Vector3d lastLastNotNanPoint = ::Vector3d::center;
	unsigned int lastNotNanFrame = std::numeric_limits<unsigned int>::max();
	unsigned int lastLastNotNanFrame = std::numeric_limits<unsigned int>::max();
};

} /* namespace utils */

#endif /* SRC_WINDOW_LAYER_CONTENT_PLOT_CURVE_CURVE_H_ */
