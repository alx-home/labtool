/*
 * main.cpp
 *
 *  Created on: 27 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifdef MATLAB

#include <CoutMatlab.h>
#include <libloaderapi.h>
#include <matrix.h>
#include <MatlabMex.h>
#include <windef.h>
#include <winuser.h>
#include <array>
#include <condition_variable>
#include <exception>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../../datas/DataStruct.h"
#include "../../labellise.hpp"
#include "../../Language/LanguageLoader.h"
#include "../../resources/resource.h"
#include "../../utils/window/files/Registry.h"
#include "../../window/SplashScreen.h"
#include "../C3dReader.h"
#include "../XMLReader.h"

unsigned int sceneLabelPrefixSize = 7;
unsigned int modelLabelPrefixSize = 10;

using Mex = MatlabMex<Output<>,
Input<std::unordered_map<std::string, generic::DataStruct>, std::unordered_map<std::string, generic::DataStruct>>>;

template<>
std::string Mex::name("Labellise");

namespace {
std::unique_ptr<SplashScreen> splashScreen;
std::shared_ptr<bool> close = std::make_shared<bool>(false);
}

const char *mexFunctionName(void) {
	return Mex::getName().c_str();
}

template<>
void Mex::usage() {
	std::cout << SERIALIZER->getUsage1() + Mex::getName() + SERIALIZER->getUsage2() << std::endl;
}

template<>
void Mex::run(std::unordered_map<std::string, generic::DataStruct>& inputModel,
		std::unordered_map<std::string, generic::DataStruct>& inputScene) {
	std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>>estimationSets;
	std::vector<std::tuple<std::string, labeliser::Box>> labelisationBoxes;
	std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>> groupMarkers;
	double probaMin;
	double accelerationMax;
	double frameRate;
	unsigned int gapFramesSize;
	splashScreen.reset();

	for (auto it : inputModel) {
		if (it.second.datas.cols() != 3 || it.second.datas.rows() < 1) {
			std::cerr << "La dimension du modèle est incorrecte" << std::endl;
			std::cerr << "\texpected [1*3], received [" << it.second.datas.rows() << "*" << it.second.datas.cols() << "]" << std::endl;

			throw std::exception();
		}
	}

	for (auto it : inputScene) {
		if (it.second.datas.cols() != 3) {
			std::cerr << "La dimension de la scene est incorrecte" << std::endl;
			std::cerr << "\texpected [n*3], received [" << it.second.datas.rows() << "*" << it.second.datas.cols() << "]" << std::endl;

			throw std::exception();
		}
	}
	try {
		Labeliser::run(inputModel, inputScene, estimationSets, groupMarkers, labelisationBoxes, gapFramesSize, "", probaMin, accelerationMax, frameRate);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	generic::cerrRedirect cerr(Mex::getName());
	generic::coutRedirect cout(Mex::getName());
	generic::clogRedirect clog(Mex::getName());

	HICON hIcon = (HICON) LoadImage(GetModuleHandle(NULL),
	MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 32, 32, LR_SHARED);

	if (nrhs == 0)
		try {
			double probaMin;
			double accelerationMax;
			double frameRate;
			unsigned int gapFramesSize;
			std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>> groupMarkers;
			std::shared_ptr<std::string> modelFilePath, sceneFilePath;
			modelFilePath = std::make_shared<std::string>(
					utils::windows::Registry::getStringKeyValue("Default model",
							"Veuillez sélectionner le chemin vers le fichier c3d du modèle"));
			sceneFilePath = std::make_shared<std::string>();

			std::unordered_map<std::string, generic::DataStruct> inputModel;
			std::unordered_map<std::string, generic::DataStruct> inputScene;
			std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>>estimationSets;
			std::vector<std::tuple<std::string, labeliser::Box>> labelisationBoxes;

			{

				splashScreen = std::move(std::unique_ptr<SplashScreen>(new SplashScreen(modelFilePath, sceneFilePath)));

				std::shared_ptr<unsigned short> loadingPercentage = splashScreen->getLoadingPercentage();
				std::shared_ptr<bool> programCloser = splashScreen->getProgramCloser();

				{
					std::unique_lock<std::mutex> lock(*splashScreen->mutex);
					splashScreen->condition_variable->wait(lock);

					if (*splashScreen->getCloser())
						return;
				}

				try {
					XMLReader::read(modelFilePath, estimationSets, groupMarkers, labelisationBoxes, gapFramesSize, *splashScreen, probaMin,
							accelerationMax);
					C3dReader::read(frameRate, inputModel, inputScene, modelFilePath, sceneFilePath, loadingPercentage, programCloser,
							splashScreen->getSystemHandle());
				} catch (...) {
					return;
				}
			}

			try {
				Mex::run(inputModel, inputScene);
			} catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}

		} catch (const std::exception& e) {
			e.what();
		} catch (...) {
		}
	else
		try {
			splashScreen = std::move(std::unique_ptr<SplashScreen>(new SplashScreen()));
			Mex::mexFunction(nlhs, plhs, nrhs, prhs);
		} catch (...) {
			Mex::usage();
		}
}

#endif
