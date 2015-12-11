/*
 * ModelPoint.h
 *
 *  Created on: 19 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_MODELPOINT_H_
#define SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_MODELPOINT_H_

#include <SFML/Window/Event.hpp>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../../../../GroupMarker.h"
#include "../../../../../utils/math/Vector.h"
#include "Point.h"

namespace window {
class Window;
} /* namespace window */

namespace utils {

class ModelPoint: public Point {
public:
	ModelPoint(const Vector3d& position, const sf::Color& color, float size, std::string label = "",
			const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack = nullptr);
	ModelPoint(double x, double y, double z, const sf::Color& color, float size, std::string label = "",
			const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack = nullptr);
	virtual ~ModelPoint();

	void addGroup(bool addLinkedPointsToGroup, const GroupMarker&, bool assumUnchanged = true);
	void removeGroup(bool removeLinkedPointsFromGroup, const GroupMarker&, bool assumUnchanged = true);
	void clearGroups(bool removeLinkedPointsFromGroups, bool assumUnchanged = true);
	const std::unordered_map<unsigned long long int, GroupMarker>& getGroups() const;
	void applyGroupesChanges(window::Window& window);
	void setGroupMargin(double margin);

private:
	std::unordered_map<unsigned long long int, GroupMarker> groups;
	bool editGroups = false;
};

} /* namespace utils */

#endif /* SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_MODELPOINT_H_ */
