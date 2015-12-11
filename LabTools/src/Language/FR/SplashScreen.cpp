/*
 * SplashScreen.cpp
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

HEADER_LANGUAGE(SceneOuputFileSelectText, "Veuillez sélectionner le chemin vers le fichier c3d de la scène")
HEADER_LANGUAGE(ModelOuputFileSelectText, "Veuillez sélectionner le chemin vers le fichier c3d du modèle")
HEADER_LANGUAGE(DefaultModelText, "Model par défault")
HEADER_LANGUAGE(SetModelAsDefaultCore,
		"Le modèle selectionné n'est pas le modèle par défaut.\nVoulez vous définir ce modèle comme étant le modèle par défaut ?")
HEADER_LANGUAGE(SetModelAsDefaultTitle, "Changer le model par défaut")
HEADER_LANGUAGE(LoadingText, "Chargement des données,")

} /* namespace language */
} /* namespace utils */
