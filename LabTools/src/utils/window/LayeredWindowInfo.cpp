/*
 * LayeredWindowInfo.cpp
 *
 *  Created on: 20 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "LayeredWindowInfo.h"

namespace utils {
namespace window {

LayeredWindowInfo::LayeredWindowInfo(LONG width, LONG height) :
		m_sourcePosition(), m_windowPosition(), m_size({width, height}), m_blend(), m_info() {

	m_info.cbSize = sizeof(UPDATELAYEREDWINDOWINFO);
	m_info.pptSrc = &m_sourcePosition;
	m_info.pptDst = &m_windowPosition;
	m_info.psize = &m_size;
	m_info.pblend = &m_blend;
	m_info.dwFlags = ULW_ALPHA;

	m_blend.SourceConstantAlpha = 255;
	m_blend.AlphaFormat = AC_SRC_ALPHA;
}

LayeredWindowInfo::~LayeredWindowInfo() {
}

void LayeredWindowInfo::update(HWND window, HDC source) {

	m_info.hdcSrc = source;

	UpdateLayeredWindowIndirect(window, &m_info);
}

LONG LayeredWindowInfo::getWidth() const {
	return m_size.cx;
}

LONG LayeredWindowInfo::getHeight() const {
	return m_size.cy;
}

} /* namespace window */
} /* namespace utils */
