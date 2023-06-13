/*
 * SplashScreen.cpp
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

HEADER_LANGUAGE(SceneOuputFileSelectText, "Veuillez s�lectionner le chemin vers le fichier c3d de la sc�ne")
HEADER_LANGUAGE(ModelOuputFileSelectText, "Veuillez s�lectionner le chemin vers le fichier c3d du mod�le")
HEADER_LANGUAGE(DefaultModelText, "Model par d�fault")
HEADER_LANGUAGE(SetModelAsDefaultCore,
		"Le mod�le selectionn� n'est pas le mod�le par d�faut.\nVoulez vous d�finir ce mod�le comme �tant le mod�le par d�faut ?")
HEADER_LANGUAGE(SetModelAsDefaultTitle, "Changer le model par d�faut")
HEADER_LANGUAGE(LoadingText, "Chargement des donn�es,")

} /* namespace language */
} /* namespace utils */
