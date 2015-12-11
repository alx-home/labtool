/*
 * Plot3d.h
 *
 *  Created on: 2 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_PLOT3D_H_
#define SRC_WINDOW_LAYER_PLOT3D_H_

#include <GL/glew.h>
#include <SFML/Graphics/Color.hpp>
#include <array>
#include <cstdint>
#include <memory>
#include <vector>

#include "../../../../utils/math/Vector.h"
#include "../../Layer.h"
#include "point/DefaultPoint.h"

namespace sf {
class Event;
} /* namespace sf */
namespace utils {
class Line;
class Box;
} /* namespace utils */

namespace window {

class Plot3d: public Layer {
public:

	typedef enum {
		Default = 00, Animated = 01, InRotation = Animated << 1, InTranslation = InRotation << 1
	} State;

	Plot3d(const Vector3d& camera, const Vector3d& cameraCenter, float xTrans = 0.f, float yTrans = 0.f, float zTrans = 0.f,
			const sf::Color& backgroud = sf::Color::White, const uint8_t& border = 0x0);
	virtual ~Plot3d();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void addLineToPlot(const std::shared_ptr<utils::Line>& line);
	void addPointToPlot(const std::shared_ptr<utils::Point>& point);
	void addBoxToPlot(const std::shared_ptr<utils::Box>& box);
	void setSelector(const std::shared_ptr<point::Selector>& selector);
	const std::shared_ptr<point::Selector>& getSelector();
	void clear();
	void update() override;
	const std::vector<std::shared_ptr<utils::Point>>& getPoints() const;
	void hideAxis();
	void displayAxis();
	std::array<Vector3d, 2> getViewFinder(double x, double y, double width, double height, double xCoord, double yCoord) const;
	void disable();
	void enable();
	void rotateCamera(const Vector3d& axis, double angle);

	static constexpr float scale = 10.f;

private:
	uint32_t state = Default;
	unsigned short transTimeStamp = 0;
	static constexpr unsigned short transTimeStampMax = 10;
	unsigned short animTimeStamp = 0;
	static constexpr unsigned short animTimeStampMax = 10;
	float xInit = 0.f;
	float yInit = 0.f;
	Vector3d camera;
	Vector3d cameraUp = Vector3d::zAxis;
	Vector3d cameraInit = Vector3d();
	Vector3d cameraUpInit = Vector3d();
	std::vector<std::tuple<double, Vector3d> > rotations;
	Vector3d translation;
	Vector3d translationEnd = Vector3d();
	Vector3d translationInit = Vector3d();
	sf::Color backgroud;
	std::vector<std::shared_ptr<utils::Point>> points = std::vector<std::shared_ptr<utils::Point>>();
	std::vector<std::shared_ptr<utils::Box>> boxes = std::vector<std::shared_ptr<utils::Box>>();
	std::vector<std::shared_ptr<utils::Line>> lines = std::vector<std::shared_ptr<utils::Line>>();
	std::array<GLint, 4> viewport = std::array<GLint, 4>();
	std::array<GLdouble, 16> modelview = std::array<GLdouble, 16>();
	std::array<GLdouble, 16> projection = std::array<GLdouble, 16>();
	std::shared_ptr<point::Selector> selector = nullptr;
	std::shared_ptr<utils::Point> axisCenter = std::make_shared<utils::DefaultPoint>(0.f, 0.f, 0.f, sf::Color::Transparent, 0.f);
	std::shared_ptr<utils::Point> xAxisPoint = std::make_shared<utils::DefaultPoint>(0.2f, 0.f, 0.f, sf::Color::Transparent, 0.f);
	std::shared_ptr<utils::Point> yAxisPoint = std::make_shared<utils::DefaultPoint>(0.f, 0.2f, 0.f, sf::Color::Transparent, 0.f);
	std::shared_ptr<utils::Point> zAxisPoint = std::make_shared<utils::DefaultPoint>(0.f, 0.f, 0.2f, sf::Color::Transparent, 0.f);
	std::shared_ptr<utils::Line> xAxisLine = nullptr;
	std::shared_ptr<utils::Line> yAxisLine = nullptr;
	std::shared_ptr<utils::Line> zAxisLine = nullptr;
	bool showAxis = true;
	bool disableFlag = false;
	double zoom = 40.;
	bool insidePlot = false;
	std::tuple<std::shared_ptr<utils::Box>, double> boxSelected = std::tuple<std::shared_ptr<utils::Box>, double> { nullptr, 0 };

	std::tuple<std::shared_ptr<utils::Point>, double> getNearestPoint(const Vector3d& beggin, const Vector3d& end);
	std::tuple<std::shared_ptr<utils::Box>, double> getNearestBox(const Vector3d& beggin, const Vector3d& end);
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_PLOT_H_ */
