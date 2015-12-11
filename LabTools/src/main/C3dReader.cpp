/*
 * C3dReader.cpp
 *
 *  Created on: 27 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "C3dReader.h"

#include <vxl/core/vnl/vnl_matrix.h>
#include <cmath>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <regex>
#include <utility>

#include "../Language/LanguageLoader.h"
#include "../utils/c3d/reader/Parameter.h"
#include "../utils/c3d/reader/Reader.h"

extern std::string sceneLabelPrefix;
extern std::string sceneLabelUnlabelisedPrefix;

void C3dReader::read(double& frameRate, std::unordered_map<std::string, generic::DataStruct>& inputModel,
		std::unordered_map<std::string, generic::DataStruct>& inputScene, const std::shared_ptr<std::string>& modelFilePath,
		const std::shared_ptr<std::string>& sceneFilePath, const std::shared_ptr<unsigned short>& loadingPercentage,
		const std::shared_ptr<bool>& programCloser, HWND hwnd) {
	bool first = true;

	std::function<void(const std::shared_ptr<utils::c3d::reader::Group>&)> parameterReader =
			[&first, programCloser](const std::shared_ptr<utils::c3d::reader::Group>& group) {
				if (first) {
					first = false;
					std::cout << "\n\t Lecture des parametres du fichier\n\n";
				}

				const auto& parameters = group->getParameters();
				std::cout << "<" << group->getName() << " id=\"" << std::to_string(group->getEntityId()) << "\"" <<
				(group->getDescription().size() == 0 ? "" : " description=\"" + group->getDescription() + "\"") << ">\n";

				for (const auto& parameterIt : parameters) {
					auto& parameter = *parameterIt.second;

					std::cout << "\t" << "<" << parameter.getName() << ">\n";

					if (parameter.getDescription().size() != 0) {
						std::cout << "\t\t" << "<description>\n";
						std::cout << "\t\t\t" << std::regex_replace(parameter.getDescription(), std::regex("\n"), "\n\t\t\t") << "\n";
						std::cout << "\t\t" << "</description>\n";
					}

					std::cout << "\t\t" << "<content type=\"" << parameter.getTypeName() << "\">\n";
					std::cout << "\t\t\t" << std::regex_replace(
							std::regex_replace(
									std::regex_replace(parameter.toString(), std::regex(";"), ";\n"),
									std::regex(","), ", "),
							std::regex("\n"), "\n\t\t\t") << "\n";
					std::cout << "\t\t" << "</content>\n";

					std::cout << "\t</" << parameter.getName() << ">\n";

					if (*programCloser)
					throw std::exception(); //todo exceptions
				}

				std::cout << "</" << group->getName() << ">\n";
			};

	std::cout << "\n\nLecture du fichier : \"" + *sceneFilePath + "\"\n\n";
	std::cout << "\t Lecture de l'entete du fichier\n\n";

	try {
		utils::c3d::Reader::read(*sceneFilePath,
				[&inputScene, &loadingPercentage, programCloser](float x, float y, float z, unsigned int nbFrames, unsigned int frame,
						const std::string& markerLabel) {
					*loadingPercentage = frame * 100.f / (float)nbFrames;

					std::string label = "";
					if (markerLabel.size() > sceneLabelPrefix.size() && markerLabel.substr(0, sceneLabelPrefix.size()) == sceneLabelPrefix)
					label = sceneLabelUnlabelisedPrefix + markerLabel.substr(sceneLabelPrefix.size(), markerLabel.size() - sceneLabelPrefix.size());
					else
					label = markerLabel;

					auto& it = inputScene[label];

					if (frame == 0)
					it.datas.set_size(nbFrames, 3);

					if (x == 0 && y == 0 && z == 0)
					it.datas(frame, 0) = it.datas(frame, 1) = it.datas(frame, 2) = nan("");
					else {
						it.datas(frame, 0) = x;
						it.datas(frame, 1) = y;
						it.datas(frame, 2) = z;}

					if (*programCloser)
					throw std::exception(); //todo exceptions
				}, parameterReader,
				[&frameRate](const std::string& headerText) {
					if (headerText.substr(0, SERIALIZER->getAquisitionFrequency().size()) == SERIALIZER->getAquisitionFrequency()) {
						std::stringstream ss;
						ss << headerText.substr(SERIALIZER->getAquisitionFrequency().size(), headerText.size() - SERIALIZER->getAquisitionFrequency().size() - 1);
						ss >> frameRate;
					}

					std::cout << headerText;
				});
	} catch (const std::exception& e) {
		MessageBox(hwnd, ("Une erreure est survenue lors de la lecture du fichier de la scene : \"" + *sceneFilePath + "\"").c_str(),
				"Erreur", MB_OK);
		throw e;
	}

	std::cout << "\n\nLecture du fichier : \"" + *modelFilePath + "\"\n\n";
	std::cout << "\t Lecture de l'entete du fichier\n\n";

	first = true;

	try {
		utils::c3d::Reader::read(*modelFilePath,
				[&inputModel, &loadingPercentage, programCloser](float x, float y, float z, unsigned int nbFrames, unsigned int frame, const std::string& markerLabel) {
					*loadingPercentage = frame * 100.f / (float)nbFrames;

					std::string label = "";
					if (markerLabel.size() > sceneLabelPrefix.size() && markerLabel.substr(0, sceneLabelPrefix.size()) == sceneLabelPrefix)
					label = markerLabel.substr(sceneLabelPrefix.size(), markerLabel.size() - sceneLabelPrefix.size());
					else
					label = markerLabel;

					auto& it = inputModel[label];

					if (frame == 0)
					it.datas.set_size(nbFrames, 3);

					it.datas(frame, 0) = x;
					it.datas(frame, 1) = y;
					it.datas(frame, 2) = z;

					if (*programCloser)
					throw std::exception(); //todo exceptions
				}, parameterReader, [](const std::string& headerText) {
					std::cout << headerText;
				});
	} catch (const std::exception& e) {
		MessageBox(hwnd, ("Une erreure est survenue lors de la lecture du fichier du modèle : \"" + *modelFilePath + "\"").c_str(),
				"Erreur", MB_OK);
		throw e;
	}

	std::cout << "\n" << std::endl;
}
