/*
 * CreateMarkerGroupEvent.cpp
 *
 *  Created on: 9 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "CreateMarkerGroupEvent.h"

#include "../../labellise.hpp"
#include "../../window/Window.cxx"
#include "../../window/Window.h"

namespace utils {
namespace Editor {

CreateMarkerGroupEvent::CreateMarkerGroupEvent(const GroupMarker& group) :
		group(group) {
}

CreateMarkerGroupEvent::~CreateMarkerGroupEvent() {
}

void CreateMarkerGroupEvent::apply(window::Window& window) {
	window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::AddMarkerGroup>::access(window, &Labeliser::addMarkerGroup,
			group);
}

} /* namespace Editor */
} /* namespace utils */
