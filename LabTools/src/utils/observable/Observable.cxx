/*
 * Observable.cxx
 *
 *  Created on: 17 janv. 2016
 *      Author: alex
 */

#ifndef SRC_UTILS_OBSERVABLE_OBSERVABLE_CXX_
#define SRC_UTILS_OBSERVABLE_OBSERVABLE_CXX_

#include "Observable.h"

#include <memory>

namespace window {
namespace observable {
class Event;
} /* namespace observable */
} /* namespace window */

template class Observable<const std::shared_ptr<window::observable::Event>&>;

#endif /* SRC_UTILS_OBSERVABLE_OBSERVABLE_CXX_ */
