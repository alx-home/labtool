/*
 * SplashScreenSaver.cpp
 *
 *  Created on: 24 févr. 2016
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

HEADER_LANGUAGE(OuputFileSelectText, "Veuillez sélectionner le chemin vers le fichier de sortie")
HEADER_LANGUAGE(SaveSettingsFile, "Appliquer les changements au fichier *.settings")
HEADER_LANGUAGE(OverrideFileCore1, "Le fichier : \"")
HEADER_LANGUAGE(OverrideFileCore2, "\", éxiste déjà, voullez-vous l'écraser ?")
HEADER_LANGUAGE(OverrideFileTitle, "Ecraser le fichier ?")
HEADER_LANGUAGE(SavingText, "Enregistrement en cours,")
HEADER_LANGUAGE(PleaseWaitText, "Veuillez patienter")
HEADER_LANGUAGE(ExitButtonText, "Quitter")

} /* namespace language */
} /* namespace utils */
