/*
 * PlotMouseMenu.cpp
 *
 *  Created on: 24 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include <string>

#include "../LanguageLoader.h"
#include "../LanguageProxy.h"

namespace utils {
namespace language {

#define HEADER_LANGUAGE(NAME,  TEXT) template<>\
	const std::string& LanguageProxy<LanguageLoader::FR>::get ## NAME() const {\
	static const std::string& text = TEXT;\
	return text;\
}

HEADER_LANGUAGE(ShowModelPointText, "Afficher le nuage de points modèle");
HEADER_LANGUAGE(ShowPredictionSpheresText, "Afficher les sphères de prédiction");
HEADER_LANGUAGE(HidePredictionSpheresText, "Cacher les sphères de prédiction");
HEADER_LANGUAGE(HideModelPointsText, "Cacher le nuage de points modèle");
HEADER_LANGUAGE(ShowLegendText, "Afficher la légende");
HEADER_LANGUAGE(ShowLabelsText, "Afficher les labels");
HEADER_LANGUAGE(HideLabelsText, "Cacher les labels");
HEADER_LANGUAGE(HideLegendText, "Cacher la légende");
HEADER_LANGUAGE(ShowLabelisationBoxesText, "Afficher les boites de labellisation");
HEADER_LANGUAGE(HideLabelisationBoxesText, "Cacher les boites de labellisation");
HEADER_LANGUAGE(AddSuppressionBoxesText, "Ajouter une boite de suppression");
HEADER_LANGUAGE(AddLabelisationBoxesText, "Ajouter une boite de labellisation");
HEADER_LANGUAGE(ShowGroupsText, "Afficher les groupes de marqueurs");
HEADER_LANGUAGE(HideGroupsText, "Cacher les groupes de marqueurs");
HEADER_LANGUAGE(RotateDatasText, "Pivoter les données de la scène")
} /* namespace language */
} /* namespace utils */
