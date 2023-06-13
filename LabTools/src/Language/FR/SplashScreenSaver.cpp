/*
 * SplashScreenSaver.cpp
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

HEADER_LANGUAGE(OuputFileSelectText, "Veuillez s�lectionner le chemin vers le fichier de sortie")
HEADER_LANGUAGE(SaveSettingsFile, "Appliquer les changements au fichier *.settings")
HEADER_LANGUAGE(OverrideFileCore1, "Le fichier : \"")
HEADER_LANGUAGE(OverrideFileCore2, "\", �xiste d�j�, voullez-vous l'�craser ?")
HEADER_LANGUAGE(OverrideFileTitle, "Ecraser le fichier ?")
HEADER_LANGUAGE(SavingText, "Enregistrement en cours,")
HEADER_LANGUAGE(PleaseWaitText, "Veuillez patienter")
HEADER_LANGUAGE(ExitButtonText, "Quitter")

} /* namespace language */
} /* namespace utils */
