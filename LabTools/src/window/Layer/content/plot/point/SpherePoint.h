/*
 * SpherePoint.h
 *
 *  Created on: 18 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_SPHEREPOINT_H_
#define SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_SPHEREPOINT_H_

#include "../../../../../utils/math/Vector.h"
#include "Point.h"

namespace utils {

class SpherePoint: public Point {
public:
	SpherePoint(const ::Vector3d& pos, const sf::Color& color, float rayon);
	virtual ~SpherePoint();

	virtual void draw3d() const override;
	bool isSelectable() override;
};

} /* namespace utils */

#endif /* SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_SPHEREPOINT_H_ */
