/*
 * Event.h
 *
 *  Created on: 9 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EDITOR_EVENTS_EVENT_H_
#define SRC_EDITOR_EVENTS_EVENT_H_

namespace window {
class Window;
}  // namespace window

namespace utils {
namespace Editor {

class Event {
public:
	Event();
	virtual ~Event();

	virtual void apply(window::Window& window) = 0;
};

} /* namespace Editor */
} /* namespace utils */

#endif /* SRC_EDITOR_EVENTS_EVENT_H_ */
