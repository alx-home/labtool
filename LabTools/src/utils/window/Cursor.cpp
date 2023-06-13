/*
 * Cursor.cpp
 *
 *  Created on: 2 f�vr. 2016
 *      Author: alex
 */

#include "Cursor.h"

#include <windows.h>

namespace utils {
namespace windows {

Cursor::Type Cursor::type = DEFAULT;

void Cursor::setCursor(Type type) {
	if (type == DEFAULT)
		SetCursor(LoadCursor(nullptr, IDC_ARROW));
	else if (type == MOUSE)
		SetCursor(LoadCursor(nullptr, IDC_HAND));
}

} /* namespace windows */
} /* namespace utils */
