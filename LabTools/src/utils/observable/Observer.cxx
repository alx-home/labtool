/*
 * Observer.cxx
 *
 *  Created on: 17 janv. 2016
 *      Author: alex
 */

#ifndef SRC_UTILS_OBSERVABLE_OBSERVER_CXX_
#define SRC_UTILS_OBSERVABLE_OBSERVER_CXX_

#include "Observer.h"

#include <memory>

namespace window {
namespace observable {
class Event;
} /* namespace observable */
} /* namespace window */

template class Observer<const std::shared_ptr<window::observable::Event>&>;

#endif /* SRC_UTILS_OBSERVABLE_OBSERVER_CXX_ */
