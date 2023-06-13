/*
 * MessagesBox.cpp
 *
 *  Created on: 24 f�vr. 2016
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

HEADER_LANGUAGE(LabelisationNotEndedCore, "Le nuage de point n'est pas enti�rement labellis�.\nEtes vous sur de vouloir quitter ?")
HEADER_LANGUAGE(LabelisationNotEndedTitle, "Labellisation non termin�e")
HEADER_LANGUAGE(SaveBeforeExitCore, "Voulez-vous sauvegarder avant de quitter le programme ?")
HEADER_LANGUAGE(SaveBeforeExitTitle, "Enregistrement des r�sultas")
HEADER_LANGUAGE(SaverErrorCore1, "Impossible d'ouvrir le fichier : \"")
HEADER_LANGUAGE(SaverErrorCore2, "\", Voullez-vous r�essayer ?")
HEADER_LANGUAGE(SaverErrorTitle, "Erreur")

} /* namespace language */
} /* namespace utils */
