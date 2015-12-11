/*
 * Selector.cpp
 *
 *  Created on: 9 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "Selector.h"

#include <algorithm>
#include <iterator>
#include <stack>

#include "../../../../Window.h"
#include "ModelPoint.h"
#include "ScenePoint.h"

namespace point {

std::shared_ptr<Selector> Selector::create(window::Window& window, const std::function<void()>& onSelectionStarted,
		const std::function<void()>& onSelectionEnded,
		const std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)>& onSelection,
		const std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)>& onUnSelection,
		const std::function<void(Selector&)>& onUpdate) {
	struct make_shared_enabler: public Selector {
		make_shared_enabler(window::Window& window, const std::function<void()>& onSelectionStarted,
				const std::function<void()>& onSelectionEnded,
				const std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)>& onSelection,
				const std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)>& onUnSelection,
				const std::function<void(Selector&)>& onUpdate) :
				Selector(window, onSelectionStarted, onSelectionEnded, onSelection, onUnSelection, onUpdate) {
		}
	};

	std::shared_ptr<Selector> selector = std::make_shared<make_shared_enabler>(window, onSelectionStarted, onSelectionEnded, onSelection,
			onUnSelection, onUpdate);

	return selector;
}

Selector::Selector(window::Window& window, const std::function<void()>& onSelectionStarted, const std::function<void()>& onSelectionEnded,
		const std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)>& onSelection,
		const std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)>& onUnSelection,
		const std::function<void(Selector&)>& onUpdate) :
		onSelectionStarted(onSelectionStarted), onSelectionEnded(onSelectionEnded), window(window), onSelection(onSelection), onUnSelection(
				onUnSelection), onUpdate(onUpdate) {
}

Selector::~Selector() {
}

void Selector::selectPoint(const std::shared_ptr<utils::Point>& point, bool withUpdate) {
	if (!isEnable)
		return;

	if (selectedPoints.size() == 0)
		onSelectionStarted();

	if (std::find(selectedPoints.begin(), selectedPoints.end(), point) == selectedPoints.end())
		selectedPoints.push_back(point);
	else
		return;

	point->selected = true;
	onSelection(point, *this, withUpdate);

	if (withUpdate)
		onUpdate(*this);
}

void Selector::unselectPoint(const std::shared_ptr<utils::Point>& point, bool withUpdate) {

	for (auto it = selectedPoints.begin(); it != selectedPoints.end(); ++it)
		if (*it == point) {
			selectedPoints.erase(it);
			break;
		}

	point->selected = false;
	onUnSelection(point, *this, withUpdate);

	if (withUpdate)
		onUpdate(*this);
}

const std::vector<std::shared_ptr<utils::Point>>& Selector::getSelectedPoints() const {
	return selectedPoints;
}

const std::unordered_map<std::string, std::shared_ptr<utils::Point>>& Selector::getSelectedNaNPoints() const {
	return selectedNaNPoints;
}

void Selector::triggerPoint(const std::shared_ptr<utils::Point>& point) {
	if (point->selected)
		unselectPoint(point);
	else
		selectPoint(point);
}

void Selector::unselectAll() {
	for (auto point : selectedPoints) {
		point->selected = false;
		onUnSelection(point, *this, false);
	}

	this->selectedNaNPoints.clear();

	selectedPoints.clear();
	onUpdate(*this);
}

void Selector::endSelection() {
	unselectAll();
	onSelectionEnded();
}

void Selector::updateSelection() {
	std::stack<std::shared_ptr<utils::Point>> unselectedPoints;
	std::unordered_map<std::string, std::shared_ptr<utils::Point>> windowScenePoints;
	std::unordered_map<std::string, std::shared_ptr<utils::Point>> windowModelPoints;

	for (const auto& point : window.getScenePoints()) {
		windowScenePoints[point->getLabel()] = point;

		try {
			selectedNaNPoints.at(std::static_pointer_cast<utils::ScenePoint>(point)->getLabel());
			selectedNaNPoints.erase(std::static_pointer_cast<utils::ScenePoint>(point)->getLabel());

			selectPoint(point, false);
		} catch (...) {
		}
	}

	for (const auto& point : window.getModelPoints())
		windowModelPoints[point->getLabel()] = point;

	auto selectedPoints = this->selectedPoints;
	this->selectedPoints.clear();

	for (const auto& point : selectedPoints) {
		if (std::dynamic_pointer_cast<utils::ScenePoint>(point))
			try {
				auto point2 = windowScenePoints.at(std::static_pointer_cast<utils::ScenePoint>(point)->getLabel());

				selectPoint(point2, false);
			} catch (...) {
				this->selectedNaNPoints[point->getLabel()] = point;
			}
		else if (std::dynamic_pointer_cast<utils::ModelPoint>(point))
			try {
				auto point2 = windowModelPoints.at(std::static_pointer_cast<utils::ModelPoint>(point)->getLabel());
				selectPoint(point2, false);
			} catch (...) {
			}
	}

	onUpdate(*this);
}

void Selector::enable() {
	isEnable = true;
}

void Selector::disable() {
	isEnable = false;
	endSelection();
}

} /* namespace point */
