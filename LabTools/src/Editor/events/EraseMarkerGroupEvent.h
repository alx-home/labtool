/*
 * EraseMarkerGroupEvent.h
 *
 *  Created on: 9 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EDITOR_EVENTS_ERASEMARKERGROUPEVENT_H_
#define SRC_EDITOR_EVENTS_ERASEMARKERGROUPEVENT_H_

#include "../../GroupMarker.h"
#include "Event.h"

namespace utils {
namespace Editor {

class EraseMarkerGroupEvent: public Event {
public:
	EraseMarkerGroupEvent(unsigned long long int id);
	virtual ~EraseMarkerGroupEvent();

	void apply(window::Window& window) override;

private:
	unsigned long long int id;
};

} /* namespace Editor */
} /* namespace utils */

#endif /* SRC_EDITOR_EVENTS_ERASEMARKERGROUPEVENT_H_ */
