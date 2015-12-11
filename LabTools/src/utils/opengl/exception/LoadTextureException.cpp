/*
 * LoadFileException.cpp
 *
 *  Created on: 16 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "LoadTextureException.h"

namespace utils {
namespace opengl {
namespace exceptions {

LoadTextureException::LoadTextureException(const std::string& textureName, const std::string& file, int line) :
		textureName(textureName), file(file), line(line) {
}

LoadTextureException::~LoadTextureException() {
}

const char* LoadTextureException::what() const _GLIBCXX_USE_NOEXCEPT {
	return std::string("Error: lecture de la texture : \"" + textureName + "\" impossible !\n\tIn file : " + file + ", at line : "
			+ std::to_string(line)).c_str();
}

} /* namespace exceptions */
} /* namespace opengl */
} /* namespace utils */
