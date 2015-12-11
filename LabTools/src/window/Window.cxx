/*
 * Window.cxx
 *
 *  Created on: 4 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "Window.h"

#ifdef SRC_WINDOW_WINDOW_H_
#ifndef SRC_WINDOW_WINDOW_CXX_
#define SRC_WINDOW_WINDOW_CXX_

namespace window {

template<typename ... Params>
class Window::LabeliseAccessor<void (Labeliser::*)(Params...)> {
public:
	static void access(Window& window, void (Labeliser::*memberPtr)(Params...), Params ...params);
};

template<typename ... Params>
class Window::LabeliseAccessor<void (Labeliser::*)(Params...) const> {
public:
	static void access(Window& window, void (Labeliser::*memberPtr)(Params...) const, Params ...params);
};

template<typename Return, typename ... Params>
Return Window::LabeliseAccessor<Return (Labeliser::*)(Params...)>::access(Window& window, Return (Labeliser::*memberPtr)(Params...),
		Params ...params) {
	std::shared_ptr<Labeliser> labeliser = window.getLabeliser();

	std::lock_guard<std::mutex> lock(window.labeliserLock);

	const Return& result = ((*labeliser).*memberPtr)(params...);

	return result;
}

template<typename ... Params>
void Window::LabeliseAccessor<void (Labeliser::*)(Params...)>::access(Window& window, void (Labeliser::*memberPtr)(Params...),
		Params ...params) {
	std::shared_ptr<Labeliser> labeliser = window.getLabeliser();

	std::lock_guard<std::mutex> lock(window.labeliserLock);
	((*labeliser).*memberPtr)(params...);
}

template<typename Return, typename ... Params>
Return Window::LabeliseAccessor<Return (Labeliser::*)(Params...) const>::access(Window& window,
		Return (Labeliser::*memberPtr)(Params...) const, Params ...params) {
	std::shared_ptr<Labeliser> labeliser = window.getLabeliser();

	std::lock_guard<std::mutex> lock(window.labeliserLock);
	const Return& result = ((*labeliser).*memberPtr)(params...);

	return result;
}

template<typename ... Params>
void Window::LabeliseAccessor<void (Labeliser::*)(Params...) const>::access(Window& window, void (Labeliser::*memberPtr)(Params...) const,
		Params ...params) {
	std::shared_ptr<Labeliser> labeliser = window.getLabeliser();

	std::lock_guard<std::mutex> lock(window.labeliserLock);
	((*labeliser).*memberPtr)(params...);
}

}
// namespace window

#endif /* SRC_WINDOW_WINDOW_CXX_ */
#endif /* SRC_WINDOW_WINDOW_H_ */
