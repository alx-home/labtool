/*
 * ResizableBox.h
 *
 *  Created on: 3 févr. 2016
 *      Author: alex
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_PLOT_BOX_RESIZABLEBOX_H_
#define SRC_WINDOW_LAYER_CONTENT_PLOT_BOX_RESIZABLEBOX_H_

#include <GL/glew.h>
#include <SFML/Window/Event.hpp>
#include <array>
#include <functional>
#include <limits>
#include <memory>
#include <tuple>

#include "../../../../../utils/math/Vector.h"
#include "Box.h"

namespace labeliser {
class Box;
} /* namespace labeliser */

namespace utils {
class Point;
} /* namespace utils */

namespace utils {

class ResizableBox: public Box {
public:
	ResizableBox(const labeliser::Box& box, sf::Color color, bool assumUnchanged, const std::string& name);
	ResizableBox(double x1, double y1, double z1, double x2, double y2, double z2, sf::Color color, bool assumUnchanged,
			const std::string& name);
	ResizableBox(const std::array<double, 3>&, const std::array<double, 3>&, sf::Color color, bool assumUnchanged, const std::string& name);
	ResizableBox(const Vector3d&, const Vector3d&, sf::Color color, bool assumUnchanged, const std::string& name);
	ResizableBox(const std::array<double, 6>&, sf::Color color, bool assumUnchanged, const std::string& name);
	virtual ~ResizableBox();

	virtual std::tuple<Vector3d, double> getIntersection(const Vector3d& beggin, const Vector3d& vec) override;
	virtual void draw(const std::array<GLdouble, 16>& modelview, double zoom) const override;
	void setExremities(Vector3d& extr1, Vector3d& extr2, bool assumUnchanged = false);
	virtual void setCallBack(const std::function<void(const sf::Event&, bool, const Vector3d&, const Vector3d&)>& callBack) override;
	void setChangeCallback(const std::function<void()>& callback) override;
	bool isResized() const;
	bool isRenamed() const;
	void setRenameCallBack(const std::function<void(ResizableBox&)>&);
	void setDeleteCallBack(const std::function<void(ResizableBox&)>&);
	bool isDeleted() const;
	void setName(const std::string& name) override;

private:
	unsigned int timeStamp = 0;
	std::tuple<Vector3d, double> lastResult { Vector3d( { 0.0, 0.0, 0.0 }), std::numeric_limits<double>::max() };
	bool outside = false;
	Vector3d dirResize = Vector3d( { 0.0, 0.0, 0.0 });
	Vector3d baryCenter = Vector3d( { 0.0, 0.0, 0.0 });
	bool resized = false;
	std::function<void(ResizableBox&)> onRename = [](ResizableBox&) {};
	std::function<void(ResizableBox&)> onDelete = [](ResizableBox&) {};
	bool deleted = false;
	bool renamed = false;

	void pollEvent(const sf::Event& event, bool ctrlEnable, const Vector3d& beggin, const Vector3d& vec);
	void drawArrow(double norm, double anim, const std::array<GLdouble, 16>& modelview, double zoom, Box& box) const;
};

} /* namespace utils */

#endif /* SRC_WINDOW_LAYER_CONTENT_PLOT_BOX_RESIZABLEBOX_H_ */
