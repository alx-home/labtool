/*
 * Editor.cpp
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

HEADER_LANGUAGE(AutoButtonText, "Automatique")
HEADER_LANGUAGE(ValidateButtonText, "Valider")
HEADER_LANGUAGE(CancelButtonText, "Anuler")
HEADER_LANGUAGE(StopButtonText, "stop")
HEADER_LANGUAGE(LabeliseButtonText, "Labellise")
HEADER_LANGUAGE(FirstLabelisationButtonText, "Prèmiere labellisation")
HEADER_LANGUAGE(EmptyCurvesButtonText, "Nettoyer les courbes")
HEADER_LANGUAGE(XCurveText, "Courbes X")
HEADER_LANGUAGE(YCurveText, "Courbes Y")
HEADER_LANGUAGE(ZCurveText, "Courbes Z")
HEADER_LANGUAGE(HelpText, "Aide")

} /* namespace language */
} /* namespace utils */
