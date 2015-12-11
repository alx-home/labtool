/*
 * FontLoader.cpp
 *
 *  Created on: 21 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "FontLoader.h"

#include <SFML/Graphics/Font.hpp>
#include <array>
#include <exception>
#include <iostream>

#include "../../resources/classes/ArialFont.h"

namespace utils {
namespace opengl {

FontLoader::FontProxy FontLoader::arialFontProxy = FontLoader::FontProxy("arial.ttf");

FontLoader::FontLoader() {
}

FontLoader::~FontLoader() {
}

FontLoader::FontProxy::FontProxy(const std::string& fontPath) :
		font(nullptr) {
	font = std::make_shared<sf::Font>();

	if (fontPath == "arial.ttf") {
		if (!font->loadFromMemory(&resources::ArialFont::datas, resources::ArialFont::datas.size())) {
			std::cerr << "ERROR : impossible de charger la police : \"" << fontPath << "\"" << std::endl;
			throw std::exception();
		}
	} else if (!font->loadFromFile(fontPath)) {
		std::cerr << "ERROR : impossible de trouver la police : \"" << fontPath << "\"" << std::endl;
		throw std::exception();
	}
}

FontLoader::FontProxy::~FontProxy() {
}

const std::shared_ptr<sf::Font>& FontLoader::getArialFont() {
	return arialFontProxy.font;
}

} /* namespace opengl */
} /* namespace utils */
