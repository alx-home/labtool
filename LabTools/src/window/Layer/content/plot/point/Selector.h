/*
 * Selector.h
 *
 *  Created on: 9 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TYPES_POINT_SELECTOR_H_
#define SRC_TYPES_POINT_SELECTOR_H_

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace window {
class Window;
} /* namespace window */

namespace utils {
class Point;
} /* namespace utils */

namespace point {

class Selector {
public:
	virtual ~Selector();

	static std::shared_ptr<Selector> create(window::Window& window, const std::function<void()>& onSelectionStarted = []() {},
			const std::function<void()>& onSelectionEnded = []() {},
			const std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)>& onSelection =
					[](const std::shared_ptr<utils::Point>& point, Selector& selector, bool withUpdate) {},
			const std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)>& onUnSelection =
					[](const std::shared_ptr<utils::Point>& point, Selector& selector, bool withUpdate) {},
			const std::function<void(Selector&)>& onUpdate = [](Selector& selector) {});

	void selectPoint(const std::shared_ptr<utils::Point>& point, bool withUpdate = true);
	void unselectPoint(const std::shared_ptr<utils::Point>& point, bool withUpdate = true);
	const std::vector<std::shared_ptr<utils::Point>>& getSelectedPoints() const;
	const std::unordered_map<std::string, std::shared_ptr<utils::Point>>& getSelectedNaNPoints() const;
	void triggerPoint(const std::shared_ptr<utils::Point>& point);
	void endSelection();
	void updateSelection();
	void unselectAll();
	void disable();
	void enable();

private:
	std::vector<std::shared_ptr<utils::Point>> selectedPoints = std::vector<std::shared_ptr<utils::Point>>();
	std::unordered_map<std::string, std::shared_ptr<utils::Point>> selectedNaNPoints = std::unordered_map<std::string,
			std::shared_ptr<utils::Point>>();
	std::function<void()> onSelectionStarted;
	std::function<void()> onSelectionEnded;
	std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)> onSelection;
	std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)> onUnSelection;
	std::function<void(Selector&)> onUpdate;
	bool isEnable = true;
	window::Window& window;

	Selector(window::Window& window, const std::function<void()>& onSelectionStarted, const std::function<void()>& onSelectionEnded,
			const std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)>& onSelection,
			const std::function<void(const std::shared_ptr<utils::Point>&, Selector&, bool withUpdate)>& onUnSelection,
			const std::function<void(Selector&)>& onUpdate);
};

} /* namespace point */

#endif /* SRC_TYPES_POINT_SELECTOR_H_ */
