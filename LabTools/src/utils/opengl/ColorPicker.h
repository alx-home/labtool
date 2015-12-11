/*
 * ColorPicker.h
 *
 *  Created on: 6 févr. 2016
 *      Author: alex
 */

#ifndef SRC_UTILS_OPENGL_COLORPICKER_H_
#define SRC_UTILS_OPENGL_COLORPICKER_H_

#include <SFML/Graphics/Color.hpp>
#include <array>

class ColorPicker {
public:
	ColorPicker();
	virtual ~ColorPicker();

	sf::Color pickColor();

	static sf::Color hslToRgb(double h, double s, double l);

private:
	unsigned int index;
	static std::array<unsigned int, 14> hIndex;
	static std::array<unsigned int, 6> lIndex;
};

#endif /* SRC_UTILS_OPENGL_COLORPICKER_H_ */
