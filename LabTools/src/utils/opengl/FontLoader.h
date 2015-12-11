/*
 * FontLoader.h
 *
 *  Created on: 21 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_OPENGL_FONTLOADER_H_
#define SRC_UTILS_OPENGL_FONTLOADER_H_

#include <memory>
#include <string>

namespace sf {
class Font;
} /* namespace sf */

namespace utils {
namespace opengl {

class FontLoader {
public:
	virtual ~FontLoader();
	static const std::shared_ptr<sf::Font>& getArialFont();

private:
	FontLoader();

	class FontProxy {
	public:
		FontProxy(const std::string& fontPath);
		virtual ~FontProxy();

		std::shared_ptr<sf::Font> font;
	};

	static FontProxy arialFontProxy;
};

} /* namespace opengl */
} /* namespace utils */

#endif /* SRC_UTILS_OPENGL_FONTLOADER_H_ */
