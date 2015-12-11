/*
 * Line.h
 *
 *  Created on: 5 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TYPES_LINE_H_
#define SRC_TYPES_LINE_H_

#include <SFML/Graphics/Color.hpp>
#include <array>
#include <memory>

#include "../../../../../utils/math/Vector.h"

namespace utils {
class Point;
} /* namespace plot */

namespace utils {

class Line {
public:
	virtual ~Line();

	static std::shared_ptr<Line> createLine(const std::shared_ptr<Point>& pointA, const std::shared_ptr<Point>& pointB,
			const sf::Color& linkColor, float linkSize);
	sf::Color getLinkColor() const;
	void setLinkColor(sf::Color);
	float getLinkSize() const;
	void setLinkSize(float);
	const std::shared_ptr<Point>& getPointA() const;
	const std::shared_ptr<Point>& getPointB() const;
	void draw(double zoom) const;
	void clear();
	bool isSuppressed();
	bool isDisplayed();
	void hide();
	void display();

private:
	std::shared_ptr<Point> pointA;
	std::shared_ptr<Point> pointB;
	sf::Color linkColor;
	float linkSize;
	bool suppressed = false;
	bool displayFlag = true;

	Line(const std::shared_ptr<Point>& pointA, const std::shared_ptr<Point>& pointB, const sf::Color& linkColor, float linkSize);
};

} /* namespace plot */

#endif /* SRC_TYPES_LINE_H_ */
