/*
 * ModelPoint.cpp
 *
 *  Created on: 19 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "ModelPoint.h"

#include <SFML/Graphics/Color.hpp>
#include <utility>

#include "../../../../../labellise.hpp"
#include "../../../../Window.cxx"
#include "../../../../Window.h"
#include "../ColorMask.h"
#include "../line/Line.h"
#include "ScenePoint.h"

namespace utils {

ModelPoint::ModelPoint(const Vector3d& position, const sf::Color& color, float size, std::string label,
		const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack) :
		Point(position, color, size, label, callBack), groups() {

}

ModelPoint::ModelPoint(double x, double y, double z, const sf::Color& color, float size, std::string label,
		const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack) :
		Point(x, y, z, color, size, label, callBack), groups() {

}

ModelPoint::~ModelPoint() {
}

void ModelPoint::setGroupMargin(double margin) {
	for (auto& group : groups)
		group.second.setMarkerMargin(label, margin);

	editGroups = true;
}

void ModelPoint::addGroup(bool addLinkedPointsToGroup, const GroupMarker& group, bool assumUnchanged) {
	if (addLinkedPointsToGroup)
		for (const auto& line : lines)
			if (std::dynamic_pointer_cast<ScenePoint>(line->getPointA()) != nullptr)
				std::static_pointer_cast<ScenePoint>(line->getPointA())->addGroup(false, group, assumUnchanged);
			else
				std::static_pointer_cast<ScenePoint>(line->getPointB())->addGroup(false, group, assumUnchanged);

	if (!assumUnchanged)
		editGroups = true;
	try {
		groups.at(group.getUUID());
		return;
	} catch (...) {
	}

	groups.insert(std::unordered_map<unsigned long long int, GroupMarker>::value_type(group.getUUID(), group));

	addColorMask(ColorMask(group.getColor(), 0, group.getUUID()));
}

void ModelPoint::removeGroup(bool removeLinkedPointsFromGroup, const GroupMarker& group, bool assumUnchanged) {
	if (removeLinkedPointsFromGroup)
		for (const auto& line : lines)
			if (std::dynamic_pointer_cast<ScenePoint>(line->getPointA()) != nullptr)
				std::static_pointer_cast<ScenePoint>(line->getPointA())->removeGroup(false, group, assumUnchanged);
			else
				std::static_pointer_cast<ScenePoint>(line->getPointB())->removeGroup(false, group, assumUnchanged);

	if (!assumUnchanged)
		editGroups = true;
	try {
		groups.at(group.getUUID());
		groups.erase(group.getUUID());

		removeColorMask(ColorMask(group.getColor(), 0, group.getUUID()));
	} catch (...) {
		return;
	}
}

void ModelPoint::clearGroups(bool removeLinkedPointsFromGroups, bool assumUnchanged) {
	if (removeLinkedPointsFromGroups)
		for (const auto& line : lines)
			if (std::dynamic_pointer_cast<ScenePoint>(line->getPointA()) != nullptr)
				std::static_pointer_cast<ScenePoint>(line->getPointA())->clearGroups(false, assumUnchanged);
			else
				std::static_pointer_cast<ScenePoint>(line->getPointB())->clearGroups(false,  assumUnchanged);

	if (!assumUnchanged)
		editGroups = true;

	for (auto groupIt = groups.begin(); groupIt != groups.end(); ++groupIt)
		removeColorMask(ColorMask(groupIt->second.getColor(), 0, groupIt->first));

	groups.clear();
}

void ModelPoint::applyGroupesChanges(window::Window& window) {
	if (editGroups)
		window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::UpdateMarkerGroupsFrom>::access(window,
				&Labeliser::updateMarkerGroupsFrom, label, groups);

	this->editGroups = false;
}

const std::unordered_map<unsigned long long int, GroupMarker>& ModelPoint::getGroups() const {
	return groups;
}

} /* namespace utils */
