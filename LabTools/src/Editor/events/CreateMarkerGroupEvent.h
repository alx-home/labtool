/*
 * CreateMarkerGroupEvent.h
 *
 *  Created on: 9 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EDITOR_EVENTS_CREATEMARKERGROUPEVENT_H_
#define SRC_EDITOR_EVENTS_CREATEMARKERGROUPEVENT_H_

#include "../../GroupMarker.h"
#include "Event.h"

namespace utils {
namespace Editor {

class CreateMarkerGroupEvent: public Event {
public:
	CreateMarkerGroupEvent(const GroupMarker& group);
	virtual ~CreateMarkerGroupEvent();

	void apply(window::Window& window) override;

private:
	GroupMarker group;
};

} /* namespace Editor */
} /* namespace utils */

#endif /* SRC_EDITOR_EVENTS_CREATEMARKERGROUPEVENT_H_ */
