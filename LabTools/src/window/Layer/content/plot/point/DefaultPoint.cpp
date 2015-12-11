/*
 * DefaultPoint.cpp
 *
 *  Created on: 19 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "DefaultPoint.h"

namespace utils {

DefaultPoint::DefaultPoint(const Vector3d& position, const sf::Color& color, float size, std::string label,
		const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack) :
		Point(position, color, size, label, callBack) {

}

DefaultPoint::DefaultPoint(double x, double y, double z, const sf::Color& color, float size, std::string label,
		const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack) :
		Point(x, y, z, color, size, label, callBack) {

}

DefaultPoint::~DefaultPoint() {
}

} /* namespace utils */
