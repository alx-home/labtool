/*
 * Language.cpp
 *
 *  Created on: 5 janv. 2016
 *      Author: Alexandre GARCIN
 */
#include <iostream>
#include "LanguageLoader.h"
#include "LanguageProxy.h"

namespace utils {
namespace language {

void LanguageLoader::setLanguage(LanguageLoader::Language language) {
	switch (language) {
	case LanguageLoader::FR:

		const_cast<std::unique_ptr<language::Language>&>(LanguageLoader::getLanguage()) = std::unique_ptr<language::Language>(
				new LanguageProxy<LanguageLoader::FR>());
		break;

	default:
		const_cast<std::unique_ptr<language::Language>&>(LanguageLoader::getLanguage()) = std::unique_ptr<language::Language>(
				new LanguageProxy<LanguageLoader::FR>());
		break;
	}
}

const std::unique_ptr<language::Language>& LanguageLoader::getLanguage() {
	static std::unique_ptr<language::Language> language = std::unique_ptr<language::Language>(
			new language::LanguageProxy<LanguageLoader::DEFAULT>());

	return language;
}

} /* namespace language */
} /* namespace utils */
