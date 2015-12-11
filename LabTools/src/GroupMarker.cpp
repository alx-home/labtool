/*
 * MarkerGroup.cpp
 *
 *  Created on: 6 févr. 2016
 *      Author: alex
 */

#include "GroupMarker.h"

#include <exception>
#include <iostream>
#include <iterator>

ColorPicker GroupMarker::colorPicker = ColorPicker();
utils::UUID GroupMarker::uuidSeeder = utils::UUID();

GroupMarker::GroupMarker(double globalMargin) :
		globalMargin(globalMargin) {

	color = sf::Color(color.r, color.g, color.b, 255);
}

GroupMarker::GroupMarker(const GroupMarker& group) :
		globalMargin(group.getGlobalMargin()), color(group.getColor()), uuid(group.getUUID()), markers(group.getMarkers()) {
}

GroupMarker::~GroupMarker() {
}

unsigned long long int GroupMarker::getUUID() const {
	return uuid;
}

void GroupMarker::addMarker(const std::string& name, double margin) {
	markers[name] = margin;
}

double GroupMarker::getGlobalMargin() const {
	return globalMargin;
}

double GroupMarker::getMargin(const std::string& label) const {
	try {
		return markers.at(label);
	} catch (...) {
		return getGlobalMargin();
	}
}

const std::unordered_map<std::string, double>& GroupMarker::getMarkers() const {
	return markers;
}

void GroupMarker::setMarkerMargin(const std::string& label, double margin) {
	try {
		markers.at(label) = margin;
	} catch (...) {
		std::cerr << "Error: error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
	}
}

void GroupMarker::eraseMarker(const std::string& label) {
	markers.erase(label);
}

sf::Color GroupMarker::getColor() const {
	return color;
}
