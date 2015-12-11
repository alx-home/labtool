/*
 * ColorMask.cpp
 *
 *  Created on: 7 févr. 2016
 *      Author: alex
 */

#include "ColorMask.h"

namespace utils {

ColorMask::ColorMask(sf::Color color, unsigned short priority, unsigned long long int id) :
		color(color), priority(priority), id(id) {
}

ColorMask::~ColorMask() {
}

sf::Color ColorMask::getColor() const {
	return color;
}

unsigned short ColorMask::getPriority() const {
	return priority;
}

unsigned long long int ColorMask::getId() const {
	return id;
}

} /* namespace utils */
