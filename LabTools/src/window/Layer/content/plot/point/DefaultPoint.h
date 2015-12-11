/*
 * DefaultPoint.h
 *
 *  Created on: 19 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_DEFAULTPOINT_H_
#define SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_DEFAULTPOINT_H_

#include "Point.h"

namespace utils {

class DefaultPoint: public Point {
public:
	DefaultPoint(const Vector3d& position, const sf::Color& color, float size, std::string label = "",
			const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack = nullptr);
	DefaultPoint(double x, double y, double z, const sf::Color& color, float size, std::string label = "",
			const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack = nullptr);

	virtual ~DefaultPoint();
};

} /* namespace utils */

#endif /* SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_DEFAULTPOINT_H_ */
