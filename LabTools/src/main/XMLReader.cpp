/*
 * XMLReader.cpp
 *
 *  Created on: 27 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "XMLReader.h"

#include <windows.h>
#include <array>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <utility>

#include "../GroupMarker.h"
#include "../resources/classes/XMLModelSettings.h"
#include "../utils/math/math.h"
#include "../utils/xml/exceptions/OpenFileException.h"
#include "../utils/xml/Reader.h"
#include "../utils/xml/tag/RootTag.h"
#include "../window/SplashScreen.h"

void XMLReader::read(const std::shared_ptr<std::string>& modelFilePath,
		std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker> > >& estimationSets,
		std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker> >& groupMarkers,
		std::vector<std::tuple<std::string, labeliser::Box> >& labelisationBoxes, unsigned int& gapFramesSize, SplashScreen& splashScreen,
		double& probaMin, double& accelerationMax) {
	std::string xmlFile;

	while (true)
		try {
			xmlFile = modelFilePath->substr(0, modelFilePath->size() - 4) + ".settings";
			const std::shared_ptr<utils::xml::Tag>& tag = utils::xml::Reader::read(xmlFile);

			std::cout << "\nLecture du fichier \"" << std::string(modelFilePath->substr(0, modelFilePath->size() - 4) + ".settings")
					<< "\"\n\n";

			try {
				const auto& groups = tag->getFirstChild("groups");

				std::cout << "<groups>\n";

				for (auto group : groups->getChilds())
					try {
						if (group->getName() == "group") {
							std::cout << "\t<group";
							double margin = std::numeric_limits<double>::max();
							{
								std::stringstream ss;
								ss << group->getParam("margin");
								ss >> margin;
								std::cout << " margin=" << margin;
							}

							auto temp = std::make_shared<GroupMarker>(margin);
							groupMarkers[temp->getUUID()] = temp;

							std::cout << "/>\n";

							for (auto child : group->getChilds())
								try {
									std::cout << "\t\t<marker";
									double margin2 = margin;

									try {
										std::stringstream ss;
										ss << child->getParam("margin");
										ss >> margin2;
										std::cout << " margin=" << std::to_string(margin2);
									} catch (...) {
									}

									std::string label = child->getParam("label");

									std::cout << " label=" << label;

									temp->addMarker(label, margin2);

									std::cout << "/>\n";
								} catch (...) {
									std::cerr << "Error: Le tag xml marker ne contient pas de parametre label -> marker ignoré"
											<< std::endl;
								}

							std::cout << "\t</group>\n";

							for (auto marker : temp->getMarkers())
								estimationSets[std::get<0>(marker)][temp->getUUID()] = temp;
						}
					} catch (...) {
						std::cerr << "Error: Le tag xml group ne contient pas de parametre margin -> group ignoré" << std::endl;
					}

				std::cout << "</groups>\n";

			} catch (...) {

			}

			gapFramesSize = 50;
			probaMin = 0.98;
			accelerationMax = 0.002;

			try {
				const auto& settings = tag->getFirstChild("settings");

				std::cout << "<settings>\n";

				for (const auto& boxTag : settings->getChilds())
					if (boxTag->getName() == "gapFrames") {
						std::cout << "\t<gapFrames";
						std::stringstream ss;
						ss << boxTag->getParam("size");
						ss >> gapFramesSize;

						std::cout << " size=" << gapFramesSize;
						std::cout << "/>\n";
					} else if (boxTag->getName() == "probaMin") {
						std::cout << "\t<probaMin";
						std::stringstream ss;
						ss << boxTag->getParam("value");
						ss >> probaMin;

						std::cout << " value=" << probaMin;
						std::cout << "/>\n";
					} else if (boxTag->getName() == "accMax") {
						std::cout << "\t<accMax";
						std::stringstream ss;
						ss << boxTag->getParam("value");
						ss >> accelerationMax;

						std::cout << " value=" << accelerationMax;
						std::cout << "/>\n";
					}

				std::cout << "</settings>\n";
			} catch (...) {
			}

			try {
				const auto& boxes = tag->getFirstChild("boxes");

				std::cout << "<boxes>\n";

				for (const auto& boxTag : boxes->getChilds())
					if (boxTag->getName() == "labelisationBoxes") {

						std::cout << "\t<labelisationBoxes>\n";

						for (const auto& child : boxTag->getChilds())
							if (child->getName() == "box")
								try {
									std::cout << "\t\t<box";
									double x1 = math::StringManipulator<double>::convert(child->getParam("x1"));
									double y1 = math::StringManipulator<double>::convert(child->getParam("y1"));
									double z1 = math::StringManipulator<double>::convert(child->getParam("z1"));
									double x2 = math::StringManipulator<double>::convert(child->getParam("x2"));
									double y2 = math::StringManipulator<double>::convert(child->getParam("y2"));
									double z2 = math::StringManipulator<double>::convert(child->getParam("z2"));
									double tmp;

									std::cout << " x1=" << x1;
									std::cout << " y1=" << y1;
									std::cout << " z1=" << z1;
									std::cout << " x2=" << x2;
									std::cout << " y2=" << y2;
									std::cout << " z2=" << z2;

									std::string label = child->getParam("label");

									labelisationBoxes.push_back(std::tuple<std::string, labeliser::Box>(label, labeliser::Box(Vector3d( {
											x1, y1, z1 }), Vector3d( { x2, y2, z2 }))));

									std::cout << " label=" << label << "/>\n";
								} catch (...) {
									std::cerr << "Error: Ill-formed Box tag in xml file : " << xmlFile << "." << std::endl;
								}

						std::cout << "\t</labelisationBoxes>\n";
					} else if (boxTag->getName() == "supressionBoxes") {

						std::cout << "\t</supressionBoxes>\n";

						for (const auto& child : boxTag->getChilds())
							if (child->getName() == "box")
								try {
									std::cout << "\t\t<box";
									double x1 = math::StringManipulator<double>::convert(child->getParam("x1"));
									double y1 = math::StringManipulator<double>::convert(child->getParam("y1"));
									double z1 = math::StringManipulator<double>::convert(child->getParam("z1"));
									double x2 = math::StringManipulator<double>::convert(child->getParam("x2"));
									double y2 = math::StringManipulator<double>::convert(child->getParam("y2"));
									double z2 = math::StringManipulator<double>::convert(child->getParam("z2"));
									double tmp;

									std::cout << " x1=" << x1;
									std::cout << " y1=" << y1;
									std::cout << " z1=" << z1;
									std::cout << " x2=" << x2;
									std::cout << " y2=" << y2;
									std::cout << " z2=" << z2 << "/>\n";

									labelisationBoxes.push_back(
											std::tuple<std::string, labeliser::Box>("outlier",
													labeliser::Box(Vector3d( { x1, y1, z1 }), Vector3d( { x2, y2, z2 }))));
								} catch (...) {
									std::cerr << "Error: Ill-formed Box tag in xml file : " << xmlFile << "." << std::endl;
								}

						std::cout << "\t</supressionBoxes>\n";
					}

				std::cout << "</boxes>\n";
			} catch (...) {

			}

			break;
		} catch (const utils::xml::exceptions::OpenFileException& e) {
			std::clog << "[xml][error] xml file *.settings (file=\""
					<< std::string(modelFilePath->substr(0, modelFilePath->size() - 4) + ".settings") << "\" not found." << std::endl;

			DWORD result =
			MessageBox(splashScreen.getSystemHandle(), "Fichier *.settings introuvable !\nVoullez vous en générer un ?\n\n"
					"(Dans le cas contraire, veuillez placer le fichier *.settings adéquate "
					"dans le même dossier que le modèle et lui donner le même nom)", "Fichier *.settings introuvable",
			MB_YESNOCANCEL);

			if (result == IDNO)
				continue;

			if (result == IDCANCEL)
				throw e;

			std::ofstream file;

			try {
				class FileAllocator {
				public:
					FileAllocator(std::ofstream& file, const std::string& filePath) :
							file(file) {
						file.open(filePath, std::ios::binary);

						if (!file)
							throw utils::xml::exceptions::OpenFileException();
					}

					virtual ~FileAllocator() {
						if (file)
							file.close();
					}

				private:
					std::ofstream& file;
				} fileAllocator(file, xmlFile);

				file.write(reinterpret_cast<char*>(&resources::XMLModelSettings::datas), resources::XMLModelSettings::datas.size());
			} catch (...) {
				MessageBox(splashScreen.getSystemHandle(), "Impossible de générer le fichier .settings !",
						"Impossible de générer le fichier .settings",
						MB_OK);

				throw e;
			}
		} catch (const std::exception& e) {
			e.what();

			std::clog << "[xml][error] xml exception while reading *.settings (file=\""
					<< std::string(modelFilePath->substr(0, modelFilePath->size() - 4) + ".settings") << "\"" << std::endl;

			MessageBox(splashScreen.getSystemHandle(), ("Le fichier *.settings est corrompu !\n\n" + std::string(e.what())).c_str(),
					"Fichier *.settings corrompu",
					MB_OK);

			throw e;
		} catch (...) {
			MessageBox(splashScreen.getSystemHandle(), "Une erreure est survenue lors de la lecture *.settings", "Erreur", MB_OK);
			throw std::exception();
		}
}

