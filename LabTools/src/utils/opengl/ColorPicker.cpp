/*
 * ColorPicker.cpp
 *
 *  Created on: 6 févr. 2016
 *      Author: alex
 */

#include "ColorPicker.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

std::array<unsigned int, 14> ColorPicker::hIndex = std::array<unsigned int, 14> { 0, 20, 40, 60, 90, 140, 160,
		190, 210, 230, 260, 280, 300, 350 };

std::array<unsigned int, 6> ColorPicker::lIndex = std::array<unsigned int, 6> { 50, 60, 70, 40, 30, 20 };

ColorPicker::ColorPicker() :
		index(0) {
}

ColorPicker::~ColorPicker() {
}

sf::Color ColorPicker::pickColor() {
	constexpr unsigned short step = 5;

	sf::Color color = hslToRgb(hIndex[(index * step) % hIndex.size() + std::floor(index * step / hIndex.size())], 100.,
			lIndex[std::floor(index / hIndex.size())] / 100.);
	++index;
	index %= hIndex.size() * lIndex.size();

	return color;
}

sf::Color ColorPicker::hslToRgb(double hue, double saturation, double lightness) {
	double chroma = (1. - std::fabs(2. * lightness - 1.)) * saturation;
	double x = chroma * (1. - std::fabs(std::fmod(hue / 60., 2.) - 1.));
	double m = lightness - chroma * 0.5;
	float r, g, b;

	if (hue < 60) {
		r = chroma;
		g = x;
		b = 0;
	} else if (hue < 120) {
		r = x;
		g = chroma;
		b = 0;
	} else if (hue < 180) {
		r = 0;
		g = chroma;
		b = x;
	} else if (hue < 240) {
		r = 0;
		g = x;
		b = chroma;
	} else if (hue < 300) {
		r = x;
		g = 0;
		b = chroma;
	} else {
		r = chroma;
		g = 0;
		b = x;
	}

	return sf::Color(r + m, g + m, b + m);
}
