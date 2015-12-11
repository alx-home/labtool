/*
 * Installer.cpp
 *
 *  Created on: 28 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "Installer.h"
#ifdef WITH_INSTALLER
#include <process.h>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../utils/window/files/File.h"
#include "../../utils/window/files/Registry.h"
#include "../../resources/classes/MexFile.h"
#include "SplashScreen.h"

extern char version[];

Installer::AdminPrivilegeRequiredException::AdminPrivilegeRequiredException(std::stack<std::function<void()>>& uninstaller) {
	while (!uninstaller.empty()) {
		uninstaller.top()();
		uninstaller.pop();
	}
}
Installer::AdminPrivilegeRequiredException::~AdminPrivilegeRequiredException() {
}

void Installer::perform() {
	std::stack<std::function<void()>> uninstaller;
	bool needInstallation;

	if (!(needInstallation = utils::windows::Registry::getStringKeyValue("Installed", "false") != "true"
			|| utils::windows::Registry::getStringKeyValue("Version", "1.0") != version)) {
		exit(EXIT_FAILURE);
	}

	if (needInstallation)
		uninstaller.push([]() {
			utils::windows::Registry::deleteKey();
		});

	std::shared_ptr<std::string> matlabFilePath = std::make_shared<std::string>("");

	installer::SplashScreen splashScreen(matlabFilePath, needInstallation);

	std::shared_ptr<unsigned short> loadingPercentage = splashScreen.getLoadingPercentage();
	std::shared_ptr<bool> programCloser = splashScreen.getProgramCloser();

	{
		std::unique_lock<std::mutex> lock(*splashScreen.mutex);
		splashScreen.condition_variable->wait(lock);

		if (*programCloser)
			throw AdminPrivilegeRequiredException(uninstaller);

		if (*splashScreen.getCloser())
			exit(EXIT_SUCCESS);
	}

	std::string path = *matlabFilePath + "\\labtools";

	std::cout << "Installation de la librairie labtools dans le dossier : \"" << path << "\"." << std::endl;

	DWORD pathError = 0;

	while (!CreateDirectory(path.c_str(), nullptr) && ERROR_ALREADY_EXISTS != (pathError = GetLastError())) {
		auto result = MessageBox(splashScreen.getWindow()->getSystemHandle(),
				(LPSTR) ("Impossible de créer le dossier : \"" + path + "\"\n\nVoullez vous réessayer ?").c_str(),
				"Erreur lors de la création du répertoire d'installation", MB_RETRYCANCEL);

		if (result != IDRETRY)
			exit(EXIT_FAILURE);
	}

	if (pathError != ERROR_ALREADY_EXISTS)
		uninstaller.push([path]() {
			utils::window::File::removeDirectory(path.c_str());
		});

	std::ofstream file(path + "/labtools.mexw64", std::ios::binary);

	while (!file) {
		auto result = MessageBox(splashScreen.getWindow()->getSystemHandle(),
				(LPSTR) ("Impossible d'ouvrir le fichier : \"" + path + "/labtools.mexw64" + "\"\n\nVoullez vous réessayer ?").c_str(),
				"Erreur lors de l'installation", MB_RETRYCANCEL);

		if (result != IDRETRY)
			exit(EXIT_FAILURE);
	}

	unsigned short sizePackets = 10;
	size_t nbPackets = std::floor(resources::MexFile::datas.size() / sizePackets);

	for (size_t i = 0; i < nbPackets; ++i) {
		file.write(&reinterpret_cast<char&>(resources::MexFile::datas[i * sizePackets]), 10);
		*loadingPercentage = ((float) i) / ((float) nbPackets) * 100.f;
		if (*programCloser)
			exit(EXIT_SUCCESS);
	}

	unsigned short dataLeft = resources::MexFile::datas.size() - sizePackets * std::floor(resources::MexFile::datas.size() / sizePackets);

	if (dataLeft != 0)
		file.write(&reinterpret_cast<char&>(resources::MexFile::datas[nbPackets * sizePackets]), dataLeft);
	file.close();

	uninstaller.push([path]() {
		std::remove((path + "/labtools.mexw64").c_str());
	});

	if (needInstallation) {

		bool setMatlabPath = true;

		{
			std::ifstream test(path.substr(0, path.size() - 8) + "local\\pathdef.m");

			if (!test) {
				auto result =
				MessageBox(splashScreen.getWindow()->getSystemHandle(),
						(LPSTR) ("Des privilèges administrateurs sont requis afin de modifier les définitions de path de matlab ! \n\n"
								"Voullez vous relancer l'application en mode administrateur ?\n\n"
								"(Dans le cas contraire veuillez ajouter le dossier :\n\"" + path
								+ "\"\naux variables d'environement de matlab : File -> setPath.)").c_str(),
						"Privilèges administrateurs requis",
						MB_YESNO);

				if (result == IDYES)
					throw AdminPrivilegeRequiredException(uninstaller);
				else
					setMatlabPath = false;
			} else
				test.close();
		}

		if (setMatlabPath) {

			SHELLEXECUTEINFO ShExecInfo = { 0 };
			ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
			ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
			ShExecInfo.hwnd = NULL;
			ShExecInfo.lpVerb = "runas";
			ShExecInfo.lpFile = "matlab.exe";
			ShExecInfo.lpParameters = ("-wait -automation -nodesktop -nosplash -r \"addpath('" + path + "');savepath;exit\"").c_str();
			ShExecInfo.lpDirectory = NULL;
			ShExecInfo.nShow = SW_HIDE;
			ShExecInfo.hInstApp = NULL;

			ShellExecuteEx(&ShExecInfo);

			WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
			CloseHandle(ShExecInfo.hProcess);
		}
	}

	*loadingPercentage = 100;

	{
		std::unique_lock<std::mutex> lock(*splashScreen.mutex);
		splashScreen.condition_variable->wait(lock);

		utils::windows::Registry::setStringKeyValue("Installed", "true");
		utils::windows::Registry::setStringKeyValue("Version", version);

		if (!*splashScreen.shouldLoad())
			exit(EXIT_SUCCESS);
	}
}
#endif
