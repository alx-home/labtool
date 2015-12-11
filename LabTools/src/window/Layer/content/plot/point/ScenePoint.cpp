/*
 * ScenePoint.cpp
 *
 *  Created on: 26 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "ScenePoint.h"

#include <SFML/Graphics/Color.hpp>
#include <iterator>

#include "../../../../../labellise.hpp"
#include "../../../../Window.cxx"
#include "../../../../Window.h"
#include "../ColorMask.h"
#include "../line/Line.h"
#include "ModelPoint.h"

namespace utils {

ScenePoint::ScenePoint(const Vector3d& position, const sf::Color& color, float size, std::string label,
		const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack) :
		Point(position, color, size, label, callBack), oldName(label), groups() {
}

ScenePoint::ScenePoint(double x, double y, double z, const sf::Color& color, float size, std::string label,
		const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack) :
		Point(x, y, z, color, size, label, callBack), oldName(label), groups() {
}

void ScenePoint::addGroup(bool addLinkedPointsToGroup, const GroupMarker& group, bool assumUnchanged) {
	if (addLinkedPointsToGroup)
		for (const auto& line : lines)
			if (std::dynamic_pointer_cast<ModelPoint>(line->getPointA()) != nullptr)
				std::static_pointer_cast<ModelPoint>(line->getPointA())->addGroup(false, group, assumUnchanged);
			else
				std::static_pointer_cast<ModelPoint>(line->getPointB())->addGroup(false, group, assumUnchanged);

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

void ScenePoint::linkPointTo(const std::shared_ptr<Point>& point, const sf::Color& linkColor, float linkSize,
		const std::shared_ptr<Line>& link) {
	Point::linkPointTo(point, linkColor, linkSize, link);

	for (const auto& group : std::static_pointer_cast<ModelPoint>(point)->getGroups())
		addGroup(false, group.second);
}

void ScenePoint::removeGroup(bool removeLinkedPointsFromGroup, const GroupMarker& group, bool assumUnchanged) {
	if (removeLinkedPointsFromGroup)
		for (const auto& line : lines)
			if (std::dynamic_pointer_cast<ModelPoint>(line->getPointA()) != nullptr)
				std::static_pointer_cast<ModelPoint>(line->getPointA())->removeGroup(false, group, assumUnchanged);
			else
				std::static_pointer_cast<ModelPoint>(line->getPointB())->removeGroup(false, group, assumUnchanged);

	if (!assumUnchanged)
		editGroups = true;
	try {
		groups.erase(group.getUUID());

		removeColorMask(ColorMask(group.getColor(), 0, group.getUUID()));
	} catch (...) {
	}
}

void ScenePoint::clearGroups(bool removeLinkedPointsFromGroups, bool assumUnchanged) {
	if (removeLinkedPointsFromGroups)
		for (const auto& line : lines)
			if (std::dynamic_pointer_cast<ModelPoint>(line->getPointA()) != nullptr)
				std::static_pointer_cast<ModelPoint>(line->getPointA())->clearGroups(false, assumUnchanged);
			else
				std::static_pointer_cast<ModelPoint>(line->getPointB())->clearGroups(false, assumUnchanged);

	if (!assumUnchanged)
		editGroups = true;

	for (auto& group : groups)
		removeColorMask(ColorMask(group.second.getColor(), 0, group.first));

	groups.clear();
}

const std::unordered_map<unsigned long long int, GroupMarker>& ScenePoint::getGroups() const {
	return groups;
}

const std::string& ScenePoint::getOldName() {
	return oldName;
}

void ScenePoint::setLabel(const std::string& newLabel) {
	this->label = newLabel;

	if (label == "outlier") {
		setColor(window::Window::newlySuppressedColorPoint);
		setSize(window::Window::suppressedSize);
		unlinkPoint();
	} else if (label.c_str()[0] == '{') {
		setColor(window::Window::splitedColorPoint);
		setSize(window::Window::labellisedSize);
	} else {
		setColor(window::Window::sceneColor);
		setSize(window::Window::pointSize);
	}

	clearGroups(false);
}

void ScenePoint::applyChanges(window::Window& window, bool preStep) {
	if (this->oldName != this->label) {
		if (preStep) {
			window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::RenameLabel>::access(window, &Labeliser::renameLabel,
					oldName, "@!#320^" + oldName); //todo \0
			oldName = "@!#320^" + oldName;
		} else {
			if (this->label == "outlier") {
				window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::ErasePoint>::access(window, &Labeliser::erasePoint,
						oldName);
				clear();
			} else
				window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::RenameLabel>::access(window,
						&Labeliser::renameLabel, oldName, label);

			oldName = label;
		}
	}
}

void ScenePoint::applyGroupesChanges(window::Window& window) {
	if (editGroups)
		window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::UpdateMarkerGroupsFrom>::access(window,
				&Labeliser::updateMarkerGroupsFrom, oldName, groups);

	this->editGroups = false;
}

void ScenePoint::setGroupMargin(double margin) {
	for (auto& group : groups)
		group.second.setMarkerMargin(label, margin);

	this->editGroups = true;
}

ScenePoint::~ScenePoint() {
}

} /* namespace utils */
