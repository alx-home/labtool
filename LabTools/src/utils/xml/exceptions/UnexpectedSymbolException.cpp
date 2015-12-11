/*
 * UnexpectedSymbolException.cpp
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "UnexpectedSymbolException.h"

#include <sstream>

namespace utils {
namespace xml {
namespace exceptions {
//todo xml exceptions
UnexpectedSymbolException::UnexpectedSymbolException(char symbol, const std::string& line) :
		symbol(symbol), line(line) {
}

UnexpectedSymbolException::~UnexpectedSymbolException() {
}

const char* UnexpectedSymbolException::what() const _GLIBCXX_USE_NOEXCEPT {
	std::string character = "";
	std::stringstream ss;

	ss << symbol;
	ss >> character;

	return ("Symbole \"" + (character == "\"" ? "\\\"" : character) + "\" inattendu a la ligne : " + line).c_str();
}

} /* namespace exceptions */
} /* namespace xml */
} /* namespace utils */
