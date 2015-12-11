/*
 * ScenePoint.h
 *
 *  Created on: 26 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_SCENEPOINT_H_
#define SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_SCENEPOINT_H_

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
}  // namespace window

namespace utils {

class ScenePoint: public Point {
public:
	ScenePoint(const Vector3d& position, const sf::Color& color, float size, std::string label = "",
			const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack = nullptr);
	ScenePoint(double x, double y, double z, const sf::Color& color, float size, std::string label = "",
			const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack = nullptr);
	void addGroup(bool addLinkedPointsToGroup, const GroupMarker& group, bool assumUnchanged = true);
	void removeGroup(bool removeLinkedPointsFromGroup, const GroupMarker& group, bool assumUnchanged = true);
	void clearGroups(bool removeLinkedPointsFromGroups, bool assumUnchanged = true);
	const std::unordered_map<unsigned long long int, GroupMarker>& getGroups() const;
	const std::string& getOldName();
	void setLabel(const std::string&) override;
	void applyChanges(window::Window& window, bool preStep = false);
	void applyGroupesChanges(window::Window& window);
	void setGroupMargin(double margin);

	virtual ~ScenePoint();

protected:
	std::string oldName;
	std::unordered_map<unsigned long long int, GroupMarker> groups;
	bool editGroups = false;

	void linkPointTo(const std::shared_ptr<Point>& point, const sf::Color& linkColor, float linkSize, const std::shared_ptr<Line>& link) override;
};

} /* namespace utils */

#endif /* SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_SCENEPOINT_H_ */
