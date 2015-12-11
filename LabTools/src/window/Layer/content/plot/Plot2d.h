/*
 * Plot2d.h
 *
 *  Created on: 2 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_PLOT2D_H_
#define SRC_WINDOW_LAYER_PLOT2D_H_

#include <SFML/Graphics/Color.hpp>
#include <cstdint>
#include <memory>
#include <vector>

#include "../../Layer.h"
#include "point/DefaultPoint.h"

namespace window {
class Window;
} /* namespace window */

namespace utils {
class Curve;
} /* namespace utils */

namespace sf {
class Event;
} /* namespace sf */
namespace utils {
class Line;
class Box;
} /* namespace utils */

namespace window {

class Plot2d: public Layer {
public:

	Plot2d(window::Window& window, const sf::Color& backgroud = sf::Color::White, const uint8_t& border = 0x0);
	virtual ~Plot2d();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void addLineToPlot(const std::shared_ptr<utils::Line>& line);
	void addPointToPlot(const std::shared_ptr<utils::Point>& point);
	void addCurveToPlot(const std::shared_ptr<utils::Curve>& point);
	void setSelector(const std::shared_ptr<point::Selector>& selector);
	const std::shared_ptr<point::Selector>& getSelector();
	void clear();
	void update() override;
	const std::vector<std::shared_ptr<utils::Point>>& getPoints() const;
	void hideAxis();
	void displayAxis();
	void disable();
	void enable();

	static constexpr float scale = 10.f;

private:
	bool inTranslation = false;
	bool inFrameTranslation = false;
	int lastTranslation = 0;
	unsigned int beggin = 0;
	unsigned int end = 0;
	int translation = 0;
	double xInit = 0.;
	int zoom = 1;
	unsigned int frameTrans = 0;
	sf::Color backgroud;
	std::vector<std::shared_ptr<utils::Point>> points = std::vector<std::shared_ptr<utils::Point>>();
	std::vector<std::shared_ptr<utils::Line>> lines = std::vector<std::shared_ptr<utils::Line>>();
	std::vector<std::shared_ptr<utils::Curve>> curves = std::vector<std::shared_ptr<utils::Curve>>();
	std::shared_ptr<point::Selector> selector = nullptr;
	std::shared_ptr<utils::Point> axisCenter = std::make_shared<utils::DefaultPoint>(0.f, 0.f, 0.f, sf::Color::Transparent, 0.f);
	std::shared_ptr<utils::Point> xAxisPoint = std::make_shared<utils::DefaultPoint>(0.2f, 0.f, 0.f, sf::Color::Transparent, 0.f);
	std::shared_ptr<utils::Point> yAxisPoint = std::make_shared<utils::DefaultPoint>(0.f, 0.2f, 0.f, sf::Color::Transparent, 0.f);
	std::shared_ptr<utils::Line> xAxisLine = nullptr;
	std::shared_ptr<utils::Line> yAxisLine = nullptr;
	window::Window& window;
	bool showAxis = true;
	bool disableFlag = false;
	bool insidePlot = false;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_PLOT_H_ */
