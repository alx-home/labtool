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
		"\tstruct inputScene: une structure contenant les donn�es des points non labellis�s "
		"(obtenue � l'aide de la fonction readc3d)\n"
		"\tstruct inputModel: une structure contenant les donn�es des points d�j� labellis�s "
		"(obtenue � l'aide de la fonction readc3d)\n\n"
		"\tstruct outputScene: le r�sultat de la labellisation (structure identique � celles "
		"d'entr�es)\n\n"
		"info :\n\tIl est possible de ne pas sp�cifier inputScene et inputModel afin "
		"d'ouvrir les fichiers c3d � l'aide du logiciel.\n")

} /* namespace language */
} /* namespace utils */
