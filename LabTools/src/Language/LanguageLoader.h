/*
 * Language.h
 *
 *  Created on: 5 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_LANGUAGE_LANGUAGELOADER_H_
#define SRC_LANGUAGE_LANGUAGELOADER_H_

#include <map>
#include <memory>

#include "Language.h"

#define SERIALIZER utils::language::LanguageLoader::getLanguage()

namespace utils {
namespace language {

class LanguageLoader {
public:
	typedef enum {
		FR, DEFAULT = FR
	} Language;

	virtual ~LanguageLoader() = delete;

	static void setLanguage(Language language);
	static const std::unique_ptr<language::Language>& getLanguage();

private:
	LanguageLoader() = delete;
};

}
/* namespace language */
} /* namespace utils */

#endif /* SRC_LANGUAGE_LANGUAGELOADER_H_ */
