/*
 * main.cpp
 *
 *  Created on: 2 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef MATLAB

#include <CoutMatlab.h>
#include <windows.h>
#include <array>
#include <cmath>
#include <condition_variable>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <regex>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../../datas/DataStruct.h"
#include "../../labellise.hpp"
#include "../../Language/LanguageLoader.h"
#include "../../resources/resource.h"
#include "../../utils/c3d/reader/Reader.h"
#include "../../utils/window/files/Registry.h"
#include "../../utils/xml/exceptions/OpenFileException.h"
#include "../../window/SplashScreen.h"
#include "../C3dReader.h"
#include "../XMLReader.h"
#ifdef WITH_INSTALLER
#include "Installer.h"
#endif

extern char softwareName[];
char version[] = "1.1.1";

//fixme supp folder if cerr empty
int main(int argc, char* argv[]) {
#ifdef WITH_INSTALLER
	if (argc == 2) {
		Installer::perform();

		return 3;
	} else if (utils::windows::Registry::getStringKeyValue("Installed", "false") != "true"
			|| utils::windows::Registry::getStringKeyValue("Version", version) != version) {
		try {
			Installer::perform();
		} catch (const Installer::AdminPrivilegeRequiredException& e) {
			SHELLEXECUTEINFO ShExecInfo = {0};
			ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
			ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
			ShExecInfo.hwnd = NULL;
			ShExecInfo.lpVerb = "runas";
			ShExecInfo.lpFile = "labtools.exe";
			ShExecInfo.lpParameters = "admin";
			ShExecInfo.lpDirectory = NULL;
			ShExecInfo.nShow = SW_HIDE;
			ShExecInfo.hInstApp = NULL;

			ShellExecuteEx(&ShExecInfo);

			DWORD exitCode;

			WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
			GetExitCodeProcess(ShExecInfo.hProcess, &exitCode);
			CloseHandle(ShExecInfo.hProcess);

			if (exitCode != 3)
			return exitCode;
		}
	}
#endif

	std::shared_ptr<std::string> modelFilePath, sceneFilePath;
	modelFilePath = std::make_shared<std::string>(utils::windows::Registry::getStringKeyValue("Default model", SERIALIZER->getModelOuputFileSelectText()));
	sceneFilePath = std::make_shared<std::string>();
	HICON hIcon = (HICON) LoadImage(GetModuleHandle(NULL),
	MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 32, 32, LR_SHARED);

	try {
		generic::cerrRedirect cerr(softwareName);
		generic::coutRedirect cout(softwareName);
		generic::clogRedirect clog(softwareName);

		try {
			std::unordered_map<std::string, generic::DataStruct> inputModel = std::unordered_map<std::string, generic::DataStruct>();
			std::unordered_map<std::string, generic::DataStruct> inputScene = std::unordered_map<std::string, generic::DataStruct>();
			std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker> > > estimationSets =
					std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker> > >();
			std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker> > groupMarkers = std::unordered_map<
					unsigned long long int, std::shared_ptr<GroupMarker>>();
			std::vector<std::tuple<std::string, labeliser::Box> > labelisationBoxes =
					std::vector<std::tuple<std::string, labeliser::Box> >();
			unsigned int gapFramesSize;
			double probaMin;
			double accelerationMax;
			double frameRate;

			{
				SplashScreen splashScreen(modelFilePath, sceneFilePath);

				std::shared_ptr<unsigned short> loadingPercentage = splashScreen.getLoadingPercentage();
				std::shared_ptr<bool> programCloser = splashScreen.getProgramCloser();

				{
					std::unique_lock<std::mutex> lock(*splashScreen.mutex);
					splashScreen.condition_variable->wait(lock);

					if (*splashScreen.getCloser())
						return EXIT_SUCCESS;
				}

				try {
					XMLReader::read(modelFilePath, estimationSets, groupMarkers, labelisationBoxes, gapFramesSize, splashScreen, probaMin,
							accelerationMax);
					C3dReader::read(frameRate, inputModel, inputScene, modelFilePath, sceneFilePath, loadingPercentage, programCloser,
							splashScreen.getSystemHandle());
				} catch (...) {
					return EXIT_SUCCESS;
				}
			}

			try {
				Labeliser::run(inputModel, inputScene, estimationSets, groupMarkers, labelisationBoxes, gapFramesSize, *sceneFilePath,
						*modelFilePath, probaMin, accelerationMax, frameRate);
			} catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}

		} catch (const std::exception& e) {
			e.what();
		} catch (...) {
		}
	} catch (const std::exception& e) {
		e.what();

		std::clog << "[stream][redirection] an exception occurred during stream redirection." << std::endl;
		return EXIT_FAILURE;
	} catch (...) {
	}

	return EXIT_SUCCESS;
}

#endif
