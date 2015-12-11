/*
 * Language.cpp
 *
 *  Created on: 5 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "LanguageProxy.h"

#include <map>

#include "LanguageLoader.h"

namespace utils {
namespace language {

template<LanguageLoader::Language language>
LanguageProxy<language>::LanguageProxy() {
}

template<LanguageLoader::Language language>
LanguageProxy<language>::~LanguageProxy() {
}

} /* namespace language */
} /* namespace utils */

