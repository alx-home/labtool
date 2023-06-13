/*
 *  BottomMenu.cpp
 *
 *  Created on: 5 janv. 2016
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

HEADER_LANGUAGE(FirstLabelisationText, "Veuillez s�lectionner la frame dont le nuage de points rouges "
		"(scene) correspond le mieux au nuage de points bleus (mod�le) � l'aide des boutons \"<<<\" et \">>>\""
		"\nUne fois cela fait, cliquez sur le bouton \"Premi�re Labellisation\" afin de lancer la "
		"labellisation.")

HEADER_LANGUAGE(LabelisationText, "Deux possibilit�s s'offrent � vous :\n\n"
		"\t- Appuyer sur \"Automatique\" et faire confiance au logiciel.\n"
		"\t- Selectionner manuellement toutes les frames � labelliser � l'aide des boutons \"<<<\" et \">>>\" et "
		"appuyez sur le bouton \"Labelliser\" pour chacune de ces frames.")

HEADER_LANGUAGE(ValidationFirstLabelisationText,
		"Veuillez v�rifier que la correspondance entre les marqueurs du nuage de points rouges et celle du nuage de points"
				" bleus est correcte.\nSi tel est le cas, appuyez sur \"valider\" pour continuer. "
				"Sinon appliquez les corrections n�cessaires en cliquant sur les points aberrants.\n"
				"Vous pouvez aussi cliquer sur \"annuler\" afin de choisir une frame de r�f�rence diff�rente")

HEADER_LANGUAGE(ValidationLabelisationText,
		"Veuillez v�rifier que la correspondance entre les marqueurs du nuage de points rouges et celle du nuage de points"
				" bleus est correcte.\nSi tel est le cas, appuyez sur \"valider\" pour continuer. "
				"Sinon appliquez les corrections n�scessaires en cliquant sur les points aberrants.\n"
				"Vous pouvez aussi cliquer sur \"annuler\" afin d'annuler les changements apport�s par le logiciel.")

HEADER_LANGUAGE(AutoModeText, "Veuillez patienter pendant la labellisation automatique des points critiques.\n"
		"Appuyez sur stop si vous voulez mettre en pause le processus. Vous pourrez alors appliquer des modifications manuellement.")

HEADER_LANGUAGE(EditText, "Une fois vos modifications manuelles termin�es, veuillez cliquer sur valider pour les appliquer ou sur "
		"annuler pour revenir � l'�tat initial.")

HEADER_LANGUAGE(AutoModeEndedText, "Labellisation automatique des marqueurs termin�e ...\n\n"
		"Veuillez regarder les courbes de chacun des marqueurs violets (marqueurs du mod�le) afin de :"
		"\n\t- completer les parties manquantes (rectangles rouges) "
		"\n\t- corriger les coordonn�es �ron�es (rectangles oranges).\n"
		"\nUne fois ceci fait, vous pouvez fermer la fenetre afin d'enregistrer la labelisation.")

HEADER_LANGUAGE(AutoModeWaitText, "Une incoh�rence � �t� d�tect�e lors de la labellisation automatique. "
		"Veuillez effectuer une v�rification visuelle et apporter les changements n�sc�ssaires.\n"
		"Une fois ceci fait appuyez sur valider pour continuer.")

} /* namespace language */
} /* namespace utils */
