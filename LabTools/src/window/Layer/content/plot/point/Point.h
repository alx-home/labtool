/*
 * Point.h
 *
 *  Created on: 5 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TYPES_POINT_H_
#define SRC_TYPES_POINT_H_

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../../../../utils/math/Vector.h"
#include "../ColorMask.h"
#include "exception/EmptyLabelDrawerFunctionException.h"

namespace sf {
class RenderTarget;
class RenderTexture;
} /* namespace sf */

namespace point {
class Selector;
} /* namespace point */

namespace utils {
class Line;
} /* namespace plot */

namespace utils {

class Point {
public:
	virtual ~Point();

	void setColor(sf::Color color);
	sf::Color getColor() const;
	const std::vector<std::shared_ptr<Line> >& getLines() const;
	void setLines(const std::vector<std::shared_ptr<Line> >& lines);
	const Vector3d& getPosition() const;
	void setPosition(const Vector3d& position);
	float getSize() const;
	void setSize(float size);
	virtual void draw3d() const;
	virtual void draw2d(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) const;
	virtual void drawLabel(const std::shared_ptr<sf::RenderTarget>& window, ::Vector3d cameraRight, ::Vector3d cameraUp, float width,
			float height) const;
	const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& getCallBack() const;
	void setCallBack(const std::shared_ptr<std::function<void(const sf::Event&, bool)> >& callBack);
	const std::string& getLabel() const;
	void unlinkPoint();
	void setError(bool flag = true);
	void clear();
	bool isSuppressed();
	bool isSelected();
	virtual void setLabel(const std::string& label);
	void display();
	void hide();
	bool isDisplayed() const;
	void setLabelDrawer(const std::function<void(const std::shared_ptr<sf::RenderTexture>&, float& width, float& height)>& labelDrawer);
	bool isLabelEnable() const;
	void displayLabel();
	void hideLabel();
	void addColorMask(ColorMask mask);
	void removeColorMask(ColorMask mask);
	void clearColorMasks();
	virtual bool isSelectable();
	void set2DColor(const sf::Color&);

	friend class Line;

protected:
	sf::Color color;
	sf::Color color2d = sf::Color(0, 0, 0);
	Vector3d position;
	float size;
	std::vector<std::shared_ptr<Line>> lines = std::vector<std::shared_ptr<Line>>();
	std::shared_ptr<std::function<void(const sf::Event&, bool)>> callBack;
	bool selected = false;
	std::shared_ptr<point::Selector> selector = nullptr;
	std::string label;
	bool suppressed = false;
	bool selectable = true;
	bool error = false;
	bool displayFlag = true;
	bool showLabel = false;
	std::map<unsigned short, std::vector<ColorMask>> colorMasks = std::map<unsigned short, std::vector<ColorMask>>();
	std::function<void(const std::shared_ptr<sf::RenderTexture>&, float& width, float& height)> labelDrawer =
			[](const std::shared_ptr<sf::RenderTexture>& renderTexture, float& width, float& height) {
				throw exception::EmptyLabelDrawerFunctionException();
			};

	Point(const Vector3d& position, const sf::Color& color, float size, std::string label = "",
			const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack = nullptr);
	Point(double x, double y, double z, const sf::Color& color, float size, std::string label = "",
			const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack = nullptr);

	virtual void linkPointTo(const std::shared_ptr<Point>& point, const sf::Color& linkColor, float linkSize,
			const std::shared_ptr<Line>& link);
	void unlinkPointTo(const Line& link);

	friend class point::Selector;
};

} /* namespace plot */

#endif /* SRC_TYPES_POINT_H_ */
