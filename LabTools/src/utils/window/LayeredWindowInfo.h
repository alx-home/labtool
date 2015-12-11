/*
 * LayeredWindowInfo.h
 *
 *  Created on: 20 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_WINDOW_LAYEREDWINDOWINFO_H_
#define SRC_UTILS_WINDOW_LAYEREDWINDOWINFO_H_

#include <Windows.h>

namespace utils {
namespace window {

class LayeredWindowInfo {
	const POINT m_sourcePosition;
	POINT m_windowPosition;
	SIZE m_size;
	BLENDFUNCTION m_blend;
	UPDATELAYEREDWINDOWINFO m_info;

public:
	LayeredWindowInfo(LONG width, LONG height);
	virtual ~LayeredWindowInfo();

	void update(HWND window, HDC source);
	LONG getWidth() const;
	LONG getHeight() const;
};

} /* namespace window */
} /* namespace utils */

#endif /* SRC_UTILS_WINDOW_LAYEREDWINDOWINFO_H_ */
