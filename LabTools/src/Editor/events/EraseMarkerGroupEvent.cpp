/*
 * EraseMarkerGroupEvent.cpp
 *
 *  Created on: 9 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "EraseMarkerGroupEvent.h"

#include <iostream>

#include "../../labellise.hpp"
#include "../../window/Window.cxx"
#include "../../window/Window.h"

namespace utils {
namespace Editor {

EraseMarkerGroupEvent::EraseMarkerGroupEvent(unsigned long long int id) :
		id(id) {
}

EraseMarkerGroupEvent::~EraseMarkerGroupEvent() {
}

void EraseMarkerGroupEvent::apply(window::Window& window) {
	window::Window::LabeliseAccessor<window::Window::LabeliseAccessorTypes::RemoveMarkerGroup>::access(window,
			&Labeliser::removeMarkerGroup, id);
}

} /* namespace Editor */
} /* namespace utils */
