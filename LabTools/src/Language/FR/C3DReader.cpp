/*
 * C3DReader.cpp
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

HEADER_LANGUAGE(NumberOfMarker, "Nombre de marqueurs : ")
HEADER_LANGUAGE(NumberOfFrame, "Nombre de frames : ")
HEADER_LANGUAGE(FirstFrameNbr, "Numéro de la première frame : ")
HEADER_LANGUAGE(LastFrameNbr, "Numéro de la dernière frame : ")
HEADER_LANGUAGE(ScaleFactor, "Facteur d'échelle : ")
HEADER_LANGUAGE(InvalidDataFormat, "Erreur: le format des données du fichier c3d n'est pas le bon.")
// HEADER_LANGUAGE(AnalogueDatasNotImplemented, "Error : Analogue datas not yet implemented.")
HEADER_LANGUAGE(AnalogueDatasNotImplemented,
		"Erreur : La lecture des fichiers c3d comportants des données analogiques n'est pas encore supporté.")
HEADER_LANGUAGE(AquisitionFrequency, "Fréquence d'acquisition : ")
HEADER_LANGUAGE(ProcessorUsed, "Processeur utilisé lors de l'écriture du fichier : ")
HEADER_LANGUAGE(InvalidProcessorType, "Erreur : invalid Processor type in c3d file")
HEADER_LANGUAGE(ParameterLabelsNotFound, "Erreur : Parameter labels not found in c3d file.")
/* HEADER_LANGUAGE(EntityGroupNotFound1, "Error : entity with group id : ")
 HEADER_LANGUAGE(EntityGroupNotFound2, ", does not match any group.")*/
HEADER_LANGUAGE(EntityGroupNotFound1, "Erreur : l'identifiant d'un paramètre (id, ")
HEADER_LANGUAGE(EntityGroupNotFound2, "), ne correspond à aucun groupe.")
//HEADER_LANGUAGE(InvalidTypeOrNumberOf3DPoints, "Error: file corupted\n\tThe size of the datas does not match the number and/or the type of 3d-points.")
HEADER_LANGUAGE(InvalidTypeOrNumberOf3DPoints,
		"Erreur: fichier corrompu\n\tLa taille des données ne correspond pas au nombre et/ou au type du nuage de points.")
HEADER_LANGUAGE(FrameReading1, "Lecture de la frame n°")
HEADER_LANGUAGE(FrameReading2, "bloc n°")
// HEADER_LANGUAGE(C3dIntegerDatasNotImplemented, "Error: c3d integer data format not yet implemented.")
HEADER_LANGUAGE(C3dIntegerDatasNotImplemented,
		"Erreur : la lecture des fichiers c3d comportant des données au format numérique n'est pas encore supporté.")
/*HEADER_LANGUAGE(InvalidParameterType1, "Error: invalide parameter type : ")
 HEADER_LANGUAGE(InvalidParameterType2, ", should be \"-1 for characters data\", \"1 for byte data\", \"2 for integer data\" or "
 "\"4 for floating-point data\".")*/
HEADER_LANGUAGE(InvalidParameterType1, "Erreur: Le type du paramètre est incorrect : ")
HEADER_LANGUAGE(InvalidParameterType2,
		", devrait être \"-1 pour des données de type littéral\", \"1 pour des données binaires\", \"2 pour des entiers\" ou "
				"\"4 pour des nombres à virgule flottante\".")
HEADER_LANGUAGE(CharacterType, "Littéral")
HEADER_LANGUAGE(IntegerType, "Entier")
HEADER_LANGUAGE(FloatType, "Flottant")
HEADER_LANGUAGE(ByteType, "Octet")
HEADER_LANGUAGE(ModelPrefixSizeError1, "Erreur: la taille d'un des labels du modèle (")
HEADER_LANGUAGE(ModelPrefixSizeError2, ") est inférieure à celle du préfixe (")
HEADER_LANGUAGE(ScenePrefixSizeError1, "Erreur: la taille d'un des labels de la scène (")
HEADER_LANGUAGE(ScenePrefixSizeError2, ") est inférieure à celle du préfixe (")
HEADER_LANGUAGE(ParameterChildOverflowException1, "Error: fatal error, parameterChild overflow in file : ")
HEADER_LANGUAGE(ParameterChildOverflowException2, ", at line : ")
HEADER_LANGUAGE(ParameterChildOverflowException3, ".\n\t expected value smaller than : (")
HEADER_LANGUAGE(ParameterChildOverflowException4, "), received : (")

} /* namespace language */
} /* namespace utils */
