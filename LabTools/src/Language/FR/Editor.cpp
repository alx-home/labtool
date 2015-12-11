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

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getSplitAllFrames() const {
	static const std::string& text = "Délabelliser toutes les frames";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getSplitNextFrames() const {
	static const std::string& text = "Délabelliser les Frames suivantes";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getSplitPreviousFrames() const {
	static const std::string& text = "Délabelliser les Frames précédantes";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getSplitFrames() const {
	static const std::string& text = "Délabelliser les Frames sélectionnées";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getLinkSupression() const {
	static const std::string& text = "Supprimer le(s) lien(s)";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getMarkerRename() const {
	static const std::string& text = "Renommer le marqueur";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getLinkMarkers() const {
	static const std::string& text = "Lier les deux marqueurs";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getAddMarkersToGroups() const {
	static const std::string& text = "Ajouter au(x) groupe(s)";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getRemoveMarkersFromGroups() const {
	static const std::string& text = "Supprimer du/des groupe(s)";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getRemoveMarkerGroups() const {
	static const std::string& text = "Supprimer le(s) groupe(s)";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getCreateGroupFromMarkers() const {
	static const std::string& text = "Créer un nouveaux groupe";
	return text;
}

template<>
const std::string& LanguageProxy<LanguageLoader::FR>::getSetGroupMargin() const {
	static const std::string& text = "Définir la marge de group du/des marqueur(s)";
	return text;
}

} /* namespace language */
} /* namespace utils */
