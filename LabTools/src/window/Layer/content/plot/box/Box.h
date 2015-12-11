/*
 * Box.h
 *
 *  Created on: 25 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_BOX_H_
#define SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_BOX_H_

#include <GL/glew.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include <functional>
#include <memory>
#include <tuple>

#include "../../../../../utils/math/Vector.h"

namespace window {
class Window;
} /* namespace window */

namespace utils {
class Point;
} /* namespace utils */

namespace utils {

class Box {
public:
	Box(double x1, double y1, double z1, double x2, double y2, double z2, sf::Color color, const std::string& name);
	Box(const std::array<double, 3>&, const std::array<double, 3>&, sf::Color color, const std::string& name);
	Box(const Vector3d&, const Vector3d&, sf::Color color, const std::string& name);
	Box(const std::array<double, 6>&, sf::Color color, const std::string& name);
	virtual ~Box();

	virtual void draw(const std::array<GLdouble, 16>& modelview, double zoom) const;
	void display();
	void hide();
	bool isSelectable() const;
	bool isDisplayed() const;
	std::array<double, 3> getExtr1() const;
	std::array<double, 3> getExtr2() const;
	const std::function<void(const sf::Event&, bool, const Vector3d&, const Vector3d&)>& getCallBack() const;
	virtual void setCallBack(const std::function<void(const sf::Event&, bool, const Vector3d&, const Vector3d&)>& callBack);
	virtual std::tuple<Vector3d, double> getIntersection(const Vector3d& beggin, const Vector3d& vec);
	void unselect();
	void setColor(sf::Color color);
	void applyChanges();
	virtual void setChangeCallback(const std::function<void()>& callback);
	const std::string& getName() const;
	virtual void setExtreminties(const ::Vector3d& extr1, const ::Vector3d& extr2);
	virtual void setName(const std::string&);

protected:
	double x1;
	double y1;
	double z1;
	double x2;
	double y2;
	double z2;
	std::array<Vector3d, 8> A = std::array<Vector3d, 8>();
	bool selectable = true;
	bool displayFlag = false;
	unsigned int boxIndex = 0;
	unsigned int cornerIndex = 0;
	bool cornerIntersect = false;
	bool boxIntersect = false;
	sf::Color color;
	std::function<void(const sf::Event&, bool, const Vector3d&, const Vector3d&)> callBack =
			[] (const sf::Event&, bool ,const Vector3d&, const Vector3d&) {};
	bool mouseOver = false;
	unsigned short face = 0;
	bool clicked = false;
	std::function<void()> changeCallback = []() {};
	std::string name;
};

} /* namespace utils */

#endif /* SRC_WINDOW_LAYER_CONTENT_PLOT_POINT_BOX_H_ */
