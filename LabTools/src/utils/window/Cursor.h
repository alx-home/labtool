/*
 * Cursor.h
 *
 *  Created on: 2 févr. 2016
 *      Author: alex
 */

#ifndef SRC_UTILS_WINDOW_CURSOR_H_
#define SRC_UTILS_WINDOW_CURSOR_H_

namespace utils {
namespace windows {

class Cursor {
public:
	Cursor() = delete;
	virtual ~Cursor() = delete;

	enum Type {
		DEFAULT, MOUSE
	};

	static void setCursor(Type type);

private:
	static Type type;
};

} /* namespace windows */
} /* namespace utils */

#endif /* SRC_UTILS_WINDOW_CURSOR_H_ */
