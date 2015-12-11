/*
 * Mex.cpp
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

HEADER_LANGUAGE(Usage1, "\nUtilisation : \n\t[struct outputScene] = ")
HEADER_LANGUAGE(Usage2, "(struct inputScene, struct inputModel) \n"
		"\navec :\n"
		"\tstruct inputScene: une structure contenant les données des points non labellisés "
		"(obtenue à l'aide de la fonction readc3d)\n"
		"\tstruct inputModel: une structure contenant les données des points déjà labellisés "
		"(obtenue à l'aide de la fonction readc3d)\n\n"
		"\tstruct outputScene: le résultat de la labellisation (structure identique à celles "
		"d'entrées)\n\n"
		"info :\n\tIl est possible de ne pas spécifier inputScene et inputModel afin "
		"d'ouvrir les fichiers c3d à l'aide du logiciel.\n")

} /* namespace language */
} /* namespace utils */
