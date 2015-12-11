/*
 * Controller.cpp
 *
 *  Created on: 7 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include <string>

#include "../LanguageLoader.h"
#include "../LanguageProxy.h"

namespace utils {
namespace language {

#define HEADER_LANGUAGE(NAME, TEXT) template<>\
	const std::string& LanguageProxy<LanguageLoader::FR>::get ## NAME() const {\
	static const std::string& text = TEXT;\
	return text;\
}

HEADER_LANGUAGE(FrameNbr, " frame n° ")
HEADER_LANGUAGE(NbPoints, " nb points")

} /* namespace language */
} /* namespace utils */
