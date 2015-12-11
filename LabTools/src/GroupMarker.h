/*
 * MarkerGroup.h
 *
 *  Created on: 6 févr. 2016
 *      Author: alex
 */

#ifndef SRC_GROUPMARKER_H_
#define SRC_GROUPMARKER_H_

#include <SFML/Graphics/Color.hpp>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "utils/opengl/ColorPicker.h"
#include "utils/UUID.h"

class GroupMarker {
public:
	GroupMarker(double globalMargin);
	GroupMarker(const GroupMarker&);
	virtual ~GroupMarker();

	void addMarker(const std::string& name, double margin);
	double getGlobalMargin() const;
	double getMargin(const std::string& label) const;
	const std::unordered_map<std::string, double>& getMarkers() const;
	void eraseMarker(const std::string& label);
	void setMarkerMargin(const std::string& label, double margin);
	sf::Color getColor() const;
	unsigned long long int getUUID() const;

private:
	static utils::UUID uuidSeeder;
	static ColorPicker colorPicker;

	std::unordered_map<std::string, double> markers = std::unordered_map<std::string, double>();
	double globalMargin;
	sf::Color color = colorPicker.pickColor();
	unsigned long long int uuid = uuidSeeder.getUUID();
};

#endif /* SRC_GROUPMARKER_H_ */
