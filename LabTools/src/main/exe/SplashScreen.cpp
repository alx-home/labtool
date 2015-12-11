/*
 * SplashScreen.cpp
 *
 *  Created on: 27 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifdef WITH_INSTALLER

#include "SplashScreen.h"

#include <combaseapi.h>
#include <minwindef.h>
#include <shobjidl.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <windef.h>
#include <winuser.h>
#include <array>
#include <cmath>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "../../resources/classes/SplashScreenBackground.h"
#include "../../utils/opengl/FontLoader.h"
#include "../../utils/window/files/File.h"
#include "../../window/Layer/content/Buttons/Button.h"
#include "../../window/Layer/content/CheckBox.h"
#include "../../window/Layer/content/browser/FolderBrowserLayer.h"
#include "../../window/Layer/disposition/CenteredLayer.h"
#include "../../window/Layer/disposition/ConstrainedLayer.h"
#include "../../window/Layer/disposition/StakeLayer.h"
#include "../../window/Layer/Layer.h"
#include "Installer.h"

extern char softwareName[];

namespace installer {

SplashScreen::SplashScreen(const std::shared_ptr<std::string>& matlabFilePath, bool needInstallation) :
		matlabFilePath(matlabFilePath), loadingPercentage(std::make_shared<unsigned short>(0)), needInstallation(needInstallation) {
	thread = std::move(std::unique_ptr<std::thread>(new std::thread(&SplashScreen::threadInst, this)));
}

const std::shared_ptr<bool>& SplashScreen::getProgramCloser() const {
	return exitProgram;
}

const std::shared_ptr<sf::RenderWindow>& SplashScreen::getWindow() const {
	return window;
}

void SplashScreen::threadInst() {
	static constexpr float width = 512.f;
	static constexpr float height = 256.f;

	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height),
			std::string(softwareName) + (needInstallation ? " Installer" : " Updater"), sf::Style::None,
			sf::ContextSettings(24, 8, 8, 3, 3));

	constexpr float browserHeight = 25.f;
	constexpr int browser1Y = 120.f;
	constexpr int browser2Y = browser1Y + browserHeight * 3.f / 2.f;
	constexpr float margin = 30.f;
	constexpr float stackY = 50.f;
	constexpr float buttonsHeight = 22.f;
	constexpr float loadAfterInstallCheckBoxPos = 185.f;
	bool loading = false;

	window->setPosition(
			sf::Vector2i((sf::VideoMode::getDesktopMode().width - width) / 2.f, (sf::VideoMode::getDesktopMode().height - height) / 2.f));
	window->setVerticalSyncEnabled(true);
	window->setActive(false);

	SetWindowLong(window->getSystemHandle(), GWL_EXSTYLE, WS_EX_LAYERED);
	ITaskbarList3* m_pTaskBarlist;
	CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**) &m_pTaskBarlist);
	if (loadingPercentage == nullptr)
		m_pTaskBarlist->SetProgressState(window->getSystemHandle(), TBPF_INDETERMINATE);
	else {
		m_pTaskBarlist->SetProgressState(window->getSystemHandle(), TBPF_NORMAL);
		m_pTaskBarlist->SetProgressValue(window->getSystemHandle(), 0, 100);
	}

	COLORREF crKey = 0;
	BYTE bAlpha = 0;
	DWORD dwFlags = LWA_ALPHA;

	SetLayeredWindowAttributes(window->getSystemHandle(), crKey, bAlpha, dwFlags);
	window->setActive(true);

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	if (!backgroundTexture.loadFromMemory(&resources::SplashScreenBackground::datas[0], sizeof(resources::SplashScreenBackground::datas))) {
		std::cerr << "Error: fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
		throw std::exception();
	}

	{
		DWORD pathSize;
		matlabFilePath->resize(MAX_PATH);

		if ((pathSize = SearchPath(nullptr, "matlab.exe", nullptr, MAX_PATH, const_cast<char*>(matlabFilePath->c_str()), nullptr))
				> MAX_PATH) {
			matlabFilePath->resize(pathSize);

			pathSize = SearchPath(nullptr, "matlab.exe", nullptr, pathSize, const_cast<char*>(matlabFilePath->c_str()), nullptr);
		}

		if (pathSize != 0) {
			matlabFilePath->resize(pathSize);
			std::cout << "Matlab found : " << *matlabFilePath << std::endl;
		} else {

		}
	}

	*matlabFilePath = matlabFilePath->substr(0, matlabFilePath->size() - 14) + "toolbox";

	window::FolderBrowserLayer matlabBrowser (window->getSystemHandle(), *matlabFilePath, "\n", 20);

	matlabBrowser.setTitle("LabTools installer");

	if (!needInstallation)
		matlabBrowser.lock();

	auto installBtn =
			std::make_shared<window::Button>(false, needInstallation ? "Installer" : "Mettre à jour", 20,
					[this, &matlabBrowser, &loading](float timestamp) {
						*matlabFilePath = matlabBrowser.getText();

						{
							std::ifstream test(*matlabFilePath + "\\test.txt");

							if (!test) {
								std::ofstream test2(*matlabFilePath + "\\test.txt");

								if (!test2) {
									auto result = MessageBox(window->getSystemHandle(), (std::string ("Le dossier d'installation choisit "
															"requière des privilèges administrateurs ! Voullez vous relancer l'application en mode "
															"administrateur ?") + (needInstallation ? "\n\n(Dans le cas contraire veuillez selectionner un dossier différent.)" : "")).c_str(),
											"Privilèges administrateurs requis", MB_YESNO);

									if (result == IDYES) {
										*exitProgram = true;

										std::unique_lock<std::mutex> lock(*mutex);
										condition_variable->notify_all();
									}

									return;
								} else {
									test2.close();
									std::remove(std::string(*matlabFilePath + "\\test.txt").c_str());
								}

							} else
							test.close();
						}

						matlabBrowser.close();
						loading = true;

						std::unique_lock<std::mutex> lock(*mutex);
						condition_variable->notify_all();
					});
	auto exitBtn = std::make_shared<window::Button>(false, "Quitter", 20, [this](float timestamp) {
		*close = true;
	});

	installBtn->disable();

	auto loadingAfterInstallCheckBox = window::CheckBox();
	loadingAfterInstallCheckBox.check();

	loadingAfterInstallCheckBox.setCallback([this](bool checked) {
		*shouldLoadFlag = checked;
	});

	auto stack = std::make_shared<std::vector<std::shared_ptr<window::ConstrainedLayer>>>();
	stack->push_back(std::make_shared<window::ConstrainedLayer>(needInstallation ? 85.f : 135.f, buttonsHeight, installBtn));
	stack->push_back(std::make_shared<window::ConstrainedLayer>(80.f, buttonsHeight, exitBtn));

	auto stackLayer = std::make_shared<window::StakeLayer>(window::Layer::NoBorders, stack);
	auto centerLayer = window::CenteredLayer(
			std::make_shared<window::ConstrainedLayer>([stack] (float x, float y, float width, float heihgt) -> float {
				float result;
				for (const auto& bttn : *stack)
				result += bttn->getWidth(x, y ,width, height);

				return result;
			}, buttonsHeight, stackLayer));
	bool matlabValid = false;

	{
		std::function<bool(std::string&)> validator = [&matlabValid, installBtn] (std::string& text) -> bool {
			std::replace(text.begin(), text.end(), '/', '\\');
			matlabValid = utils::window::File::isDirExist(text);

			if (matlabValid)
			installBtn->enable();
			else
			installBtn->disable();
			return true;
		};

		matlabBrowser.setValidator(validator);
		validator(*matlabFilePath);
	}

	sf::Text name1("Lab", *utils::opengl::FontLoader::getArialFont(), 40);
	sf::Text name2("Tools", *utils::opengl::FontLoader::getArialFont(), 40);
	sf::Text text(needInstallation ? "Installation en cours," : "Mise à jour en cours,", *utils::opengl::FontLoader::getArialFont(), 25);
	sf::Text text2("Veuillez patienter", *utils::opengl::FontLoader::getArialFont(), 25);
	sf::Text percentage(" 0%", *utils::opengl::FontLoader::getArialFont(), 25);
	sf::Text loadAfterInstall("Lancer LabTools", *utils::opengl::FontLoader::getArialFont(), 15);
	sf::Color textColor = sf::Color(45, 145, 239);
	sf::Color textShadowColor = sf::Color(45, 145, 239, 80);
	sf::Color nameColor = textColor;
	sf::RectangleShape progressBarBgd = sf::RectangleShape();
	sf::RectangleShape ext = sf::RectangleShape();
	progressBarBgd.setPosition(20.f, window->getSize().y - 30);
	loadAfterInstall.setPosition(loadAfterInstallCheckBoxPos + 20.f, 150.f);
	ext.setSize(sf::Vector2f(5.f, 5.f));
	ext.setFillColor(textShadowColor);
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setTexture(&backgroundTexture);

	name1.setPosition(std::floor((window->getSize().x - (name1.getGlobalBounds().width + 2.f + name2.getGlobalBounds().width)) / 2.f),
			25.f);
	name1.setColor(nameColor);
	name2.setPosition(std::floor(name1.getPosition().x + 2.f + name1.getGlobalBounds().width), 35.f);
	name2.setColor(nameColor);
	text.setPosition(std::floor((window->getSize().x - text.getGlobalBounds().width) / 2.f), 100.f);
	text2.setColor(textColor);
	text2.setPosition(std::floor((window->getSize().x - text.getGlobalBounds().width) / 2.f + 10.f),
			std::floor(text.getPosition().y + text.getGlobalBounds().height + 4.f));
	percentage.setColor(textColor);
	percentage.setPosition(std::floor(text2.getPosition().x + text2.getGlobalBounds().width), std::floor(text2.getPosition().y));

	bool sens = true;
	sf::Event event;
	unsigned int timeStamp = 0;
	bool isLoaded = false;

	while (window->isOpen()) {
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				*close = true;

			if (!loading) {
				matlabBrowser.pollEvent(event, margin, browser1Y, window->getSize().x - margin * 2.f, browserHeight);
				centerLayer.pollEvent(event, margin, browser2Y + stackY, window->getSize().x - margin * 2.f, buttonsHeight);
			} else if (isLoaded) {
				centerLayer.pollEvent(event, margin, browser2Y + stackY, window->getSize().x - margin * 2.f, buttonsHeight);
				loadingAfterInstallCheckBox.pollEvent(event, loadAfterInstallCheckBoxPos, loadAfterInstall.getPosition().y, 16.f, 16.f);
			}
		}

		if (*close) {
			if (loading)
				*exitProgram = true;
			window->close();
			std::unique_lock<std::mutex> lock(*mutex);
			condition_variable->notify_all();
			break;
		}

		if (loadingPercentage != nullptr && !isLoaded)
			progressBarBgd.setSize(sf::Vector2f((window->getSize().x - 40.f) * *loadingPercentage / 100.f, 5));

		if (bAlpha != 255)
			SetLayeredWindowAttributes(window->getSystemHandle(), crKey, bAlpha += 3, dwFlags);

		if (loading) {
			if (sens)
				if (timeStamp == 20)
					sens = false;
				else
					++timeStamp;
			else if (timeStamp == 0)
				sens = true;
			else
				--timeStamp;
		}

		nameColor.r = textColor.r * (20 + timeStamp * 3) / 100;
		nameColor.g = textColor.g * (20 + timeStamp * 3) / 100;
		nameColor.b = textColor.b * (20 + timeStamp * 3) / 100;

		window->clear(sf::Color(0, 0, 0, 0));

		window->draw(background);

		if (loadingPercentage != nullptr && !isLoaded) {
			progressBarBgd.setFillColor(sf::Color(45, 145, 239, 100));
			window->draw(progressBarBgd);
			ext.setPosition(progressBarBgd.getPosition() + sf::Vector2f(progressBarBgd.getSize().x, 0.f));
			window->draw(ext);
		}

		name1.move(sf::Vector2f(-1, -1));
		name1.setColor(textShadowColor);
		window->draw(name1);
		name1.setColor(nameColor);
		name1.move(sf::Vector2f(1, 1));
		window->draw(name1);

		name2.move(sf::Vector2f(-1, -1));
		name2.setColor(textShadowColor);
		window->draw(name2);
		name2.setColor(nameColor);
		name2.move(sf::Vector2f(1, 1));
		window->draw(name2);

		if (loading) {
			if (*loadingPercentage == 100)
				if (!isLoaded) {
					isLoaded = true;

					text.setString("Installation terminée !");
					stack->erase(stack->begin());
				}

			text.move(sf::Vector2f(-1, -1));
			text.setColor(textShadowColor);
			window->draw(text);
			text.setColor(textColor);
			text.move(sf::Vector2f(1, 1));
			window->draw(text);

			if (isLoaded) {
				centerLayer.draw(window, margin, browser2Y + stackY, window->getSize().x - margin * 2.f, buttonsHeight);

				loadingAfterInstallCheckBox.draw(window, loadAfterInstallCheckBoxPos, loadAfterInstall.getPosition().y, 16.f, 16.f);

				loadAfterInstall.move(sf::Vector2f(-1, -1));
				loadAfterInstall.setColor(textShadowColor);
				window->draw(loadAfterInstall);
				loadAfterInstall.setColor(textColor);
				loadAfterInstall.move(sf::Vector2f(1, 1));
				window->draw(loadAfterInstall);

			} else {
				text2.move(sf::Vector2f(-1, -1));
				text2.setColor(textShadowColor);
				window->draw(text2);
				text2.setColor(textColor);
				text2.move(sf::Vector2f(1, 1));
				window->draw(text2);

				percentage.setString(" " + std::to_string(*loadingPercentage) + "%");
				m_pTaskBarlist->SetProgressValue(window->getSystemHandle(), *loadingPercentage, 100);

				percentage.move(sf::Vector2f(-1, -1));
				percentage.setColor(textShadowColor);
				window->draw(percentage);
				percentage.setColor(textColor);
				percentage.move(sf::Vector2f(1, 1));
				window->draw(percentage);
			}
		} else {
			matlabBrowser.draw(window, margin, browser1Y, window->getSize().x - margin * 2.f, browserHeight);

			centerLayer.draw(window, margin, browser2Y + stackY, window->getSize().x - margin * 2.f, buttonsHeight);
		}

		window->display();
	}
}

SplashScreen::~SplashScreen() {
	*close = true;

	if (thread->joinable()) {
		thread->join();
	}
}

const std::shared_ptr<bool>& SplashScreen::getCloser() const {
	return close;
}

const std::shared_ptr<bool>& SplashScreen::shouldLoad() const {
	return shouldLoadFlag;
}

const std::shared_ptr<unsigned short>& SplashScreen::getLoadingPercentage() const {
	return loadingPercentage;
}

}  // namespace installer
#endif
