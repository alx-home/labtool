/*
 * SplashScreenSaver.cpp
 *
 *  Created on: 17 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "SplashScreenSaver.h"

#include <combaseapi.h>
#include <minwindef.h>
#include <shobjidl.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
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
#include <vector>

#include "../Language/LanguageLoader.h"
#include "../resources/classes/SplashScreenBackground.h"
#include "../utils/opengl/FontLoader.h"
#include "../utils/window/files/Registry.h"
#include "Layer/content/Buttons/Button.h"
#include "Layer/content/CheckBox.h"
#include "Layer/content/browser/OutputFileBrowserLayer.h"
#include "Layer/disposition/CenteredLayer.h"
#include "Layer/disposition/ConstrainedLayer.h"
#include "Layer/disposition/StakeLayer.h"
#include "Layer/disposition/MarginLayer.h"
#include "Layer/EmptyLayer.h"
#include "Layer/Layer.h"

extern char softwareName[];

SplashScreenSaver::SplashScreenSaver(const std::shared_ptr<std::string>& modelSettingsFilePath,
		const std::shared_ptr<std::string>& sceneFilePath, bool modelSettingsChanged) :
		modelSettingsFilePath(modelSettingsFilePath), sceneFilePath(sceneFilePath), loadingPercentage(std::make_shared<unsigned short>(0)), modelSettingsChanged(
				modelSettingsChanged) {
	thread = std::move(std::unique_ptr<std::thread>(new std::thread(&SplashScreenSaver::threadInst, this)));
}

const std::shared_ptr<bool>& SplashScreenSaver::getProgramCloser() const {
	return exitProgram;
}

HWND SplashScreenSaver::getSystemHandle() const {
	if (splashScreen == nullptr)
		return nullptr;
	return splashScreen->getSystemHandle();
}

void SplashScreenSaver::threadInst() {
	static constexpr float width = 512.f;
	static constexpr float height = 256.f;

	splashScreen = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), softwareName, sf::Style::None,
			sf::ContextSettings(24, 8, 8, 3, 3));

	constexpr float browserHeight = 25.f;
	constexpr int browser1Y = 120.f;
	constexpr int browser2Y = browser1Y + browserHeight * 3.f / 2.f;
	constexpr float margin = 30.f;
	constexpr float stackY = 50.f;
	constexpr float buttonsHeight = 22.f;
	constexpr float modelSettingsCheckBoxPos = 40.f;
	bool loading = false;

	splashScreen->setPosition(
			sf::Vector2i((sf::VideoMode::getDesktopMode().width - width) / 2.f, (sf::VideoMode::getDesktopMode().height - height) / 2.f));
	splashScreen->setVerticalSyncEnabled(true);
	splashScreen->setActive(false);

	SetForegroundWindow(splashScreen->getSystemHandle());

	SetWindowLong(splashScreen->getSystemHandle(), GWL_EXSTYLE, WS_EX_LAYERED);
	ITaskbarList3* m_pTaskBarlist;
	CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**) &m_pTaskBarlist);
	m_pTaskBarlist->SetProgressState(splashScreen->getSystemHandle(), TBPF_NORMAL);

	m_pTaskBarlist->SetProgressValue(splashScreen->getSystemHandle(), 0, 100);

	COLORREF crKey = 0;
	BYTE bAlpha = 0;
	DWORD dwFlags = LWA_ALPHA;

	SetLayeredWindowAttributes(splashScreen->getSystemHandle(), crKey, bAlpha, dwFlags);
	splashScreen->setActive(true);

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	if (!backgroundTexture.loadFromMemory(&resources::SplashScreenBackground::datas[0], sizeof(resources::SplashScreenBackground::datas))) {
		std::cerr << "Error: fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
		throw std::exception();
	}

	std::string lastModelText = *modelSettingsFilePath;

	auto stackBrowser = std::make_shared<std::vector<std::shared_ptr<window::ConstrainedLayer>>>();
	auto stackLayerBrowsers = std::make_shared<window::StakeLayer>(window::Layer::NoBorders, stackBrowser);
	auto marginBrowsers = std::make_shared<window::MarginLayer>(stackLayerBrowsers, margin, margin, 0, 0);

	auto centerBrowser = std::make_shared<window::CenteredLayer>(
			std::make_shared<window::ConstrainedLayer>([](float x, float y, float width, float height) {
				return width;
			}, [stackLayerBrowsers](float x, float y, float width, float height) {
				return stackLayerBrowsers->getHeight(x, y, width, height);
			}, marginBrowsers));

	auto sceneBrowser = std::make_shared<window::OutputFileBrowserLayer>(SERIALIZER->getOuputFileSelectText(), 20);
	std::shared_ptr<window::OutputFileBrowserLayer> modelSettingsBrowser = nullptr;
	std::shared_ptr<window::CheckBox> modelSettingsCheckBox;
	bool modelValid = false;
	bool sceneValid = false;

	if (modelSettingsChanged) {
		modelSettingsCheckBox = std::make_shared<window::CheckBox>();
		modelSettingsBrowser = std::make_shared<window::OutputFileBrowserLayer>("", 20);
		modelSettingsBrowser->setPattern(std::string("Model settings Files\0*.settings\0\0", 33));
		modelSettingsBrowser->lock();

		stackBrowser->push_back(std::make_shared<window::ConstrainedLayer>([margin](float x, float y, float width, float height) {
			return width;
		}, browserHeight, modelSettingsBrowser));

		stackBrowser->push_back(std::make_shared<window::ConstrainedLayer>([margin](float x, float y, float width, float height) {
			return width;
		}, browserHeight + 3., std::make_shared<window::EmptyLayer>()));
	}

	stackBrowser->push_back(std::make_shared<window::ConstrainedLayer>([margin](float x, float y, float width, float height) {
		return width;
	}, browserHeight, sceneBrowser));

	sf::Text displayModelText(SERIALIZER->getSaveSettingsFile(), *utils::opengl::FontLoader::getArialFont(), 14);
	displayModelText.setPosition(modelSettingsCheckBoxPos + 20.f, 115.);
	displayModelText.setColor(sf::Color(0, 0, 0));

	auto validateBtn =
			std::make_shared<window::Button>(false, "Valider", 20,
					[this, modelSettingsBrowser, sceneBrowser, &loading](float timestamp) {
						if (modelSettingsBrowser != nullptr) {
							*modelSettingsFilePath = modelSettingsBrowser->getText();

							unsigned int extInd = modelSettingsFilePath->find_last_of(".");
							if (extInd >= modelSettingsFilePath->size() || modelSettingsFilePath->substr(extInd, modelSettingsFilePath->size() - extInd) != ".settings")
							*modelSettingsFilePath += ".settings";

							modelSettingsBrowser->close();
						}

						*sceneFilePath = sceneBrowser->getText();

						unsigned int extInd = sceneFilePath->find_last_of(".");
						if (extInd >= sceneFilePath->size() || sceneFilePath->substr(extInd, sceneFilePath->size() - extInd) != ".c3d")
						*sceneFilePath += ".c3d";

						sceneBrowser->close();
						loading = true;

						std::unique_lock<std::mutex> lock(*mutex);
						condition_variable->notify_all();
					});

	auto goBackBtn = std::make_shared<window::Button>(false, "Retour", 20, [this](float timestamp) {
		*close = true;
	});

	auto exitBtn = std::make_shared<window::Button>(false, "Quitter", 20, [this](float timestamp) {
		*close = true;
		*exitProgram = true;
	});

	validateBtn->disable();
	validateBtn->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::Return });
	goBackBtn->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::Escape });

	auto stack = std::make_shared<std::vector<std::shared_ptr<window::ConstrainedLayer>>>();
	stack->push_back(std::make_shared<window::ConstrainedLayer>(80.f, buttonsHeight, validateBtn));
	stack->push_back(std::make_shared<window::ConstrainedLayer>(80.f, buttonsHeight, goBackBtn));
	stack->push_back(std::make_shared<window::ConstrainedLayer>(80.f, buttonsHeight, exitBtn));

	auto stackLayer = std::make_shared<window::StakeLayer>(window::Layer::NoBorders, stack);
	auto centerLayer = window::CenteredLayer(std::make_shared<window::ConstrainedLayer>(240.f, buttonsHeight, stackLayer));

	if (modelSettingsBrowser != nullptr) {
		std::function<bool(std::string&)> validator = [&modelValid, &sceneValid, validateBtn, this] (std::string& text) -> bool {
			std::string text2 = text;

			if (text2 != "") {
				unsigned int extInd = text2.find_last_of(".");
				if (extInd >= text2.size() || text2.substr(extInd, text2.size() - extInd) != ".settings")
				text2 += ".settings";

				std::ifstream file(text2);
				modelValid = true;

				if (file) {
					file.close();

					int result = MessageBox(splashScreen->getSystemHandle(),
							(SERIALIZER->getOverrideFileCore1() + text2 + SERIALIZER->getOverrideFileCore2()).c_str(),
							SERIALIZER->getOverrideFileTitle().c_str(), MB_YESNO);

					if (result == IDNO)
					modelValid = false;
					else {
						std::ofstream file2(text2, std::ios::app);

						if (!file2)
						modelValid = false;
						else
						file2.close();
					}
				} else {
					std::ofstream file2(text2);

					if (!file2) {
						modelValid = false;
					} else {
						file2.close();
						std::remove(text2.c_str());
					}

				}
			} else
			modelValid = false;

			if (modelValid && sceneValid)
			validateBtn->enable();
			else
			validateBtn->disable();

			return true;
		};

		modelSettingsBrowser->setValidator(validator);

		modelSettingsCheckBox->setCallback([&modelSettingsBrowser, &lastModelText, &modelValid, this](bool checked) {
			if (checked) {
				modelSettingsBrowser->unlock();
				modelSettingsBrowser->setText(lastModelText);
			} else {
				modelSettingsBrowser->lock();
				*modelSettingsFilePath = "";
				modelSettingsBrowser->setText("");
				modelValid = true;
			}
		});

		if (modelValid)
			modelSettingsCheckBox->check();
	} else
		modelValid = true;

	{
		std::function<bool(std::string&)> validator = [&modelValid, &sceneValid, validateBtn, this] (std::string& text) -> bool {
			std::string text2 = text;

			if (text2 != "") {
				unsigned int extInd = text2.find_last_of(".");
				if (extInd >= text2.size() || text2.substr(extInd, text2.size() - extInd) != ".c3d")
				text2 += ".c3d";

				std::ifstream file(text2);
				sceneValid = true;

				if (file) {
					file.close();

					int result = MessageBox(splashScreen->getSystemHandle(),
							(SERIALIZER->getOverrideFileCore1() + text2 + SERIALIZER->getOverrideFileCore2()).c_str(),
							SERIALIZER->getOverrideFileTitle().c_str(), MB_YESNO);

					if (result == IDNO)
					sceneValid = false;
					else {
						std::ofstream file2(text2, std::ios::app);

						if (!file2)
						sceneValid = false;
						else
						file2.close();
					}
				} else {
					std::ofstream file2(text2);

					if (!file2) {
						sceneValid = false;
					} else {
						file2.close();
						std::remove(text2.c_str());
					}

				}
			} else
			sceneValid = false;

			if (modelValid && sceneValid)
			validateBtn->enable();
			else
			validateBtn->disable();

			return true;
		};

		sceneBrowser->setValidator(validator);
	}

	sf::Text text(SERIALIZER->getSavingText(), *utils::opengl::FontLoader::getArialFont(), 25);
	sf::Text text2(SERIALIZER->getPleaseWaitText(), *utils::opengl::FontLoader::getArialFont(), 25);
	sf::Text percentage(" 0%", *utils::opengl::FontLoader::getArialFont(), 25);
	sf::Color textColor = sf::Color(45, 145, 239);
	sf::Color textShadowColor = sf::Color(45, 145, 239, 80);
	sf::RectangleShape progressBarBgd = sf::RectangleShape();
	sf::RectangleShape ext = sf::RectangleShape();
	progressBarBgd.setPosition(20.f, splashScreen->getSize().y - 30);
	ext.setSize(sf::Vector2f(5.f, 5.f));
	ext.setFillColor(textShadowColor);
	background.setSize(sf::Vector2f(splashScreen->getSize().x, splashScreen->getSize().y));
	background.setTexture(&backgroundTexture);

	text.setPosition(std::floor((splashScreen->getSize().x - text.getGlobalBounds().width) / 2.f), 100.f);
	text2.setColor(textColor);
	text2.setPosition(std::floor((splashScreen->getSize().x - text.getGlobalBounds().width) / 2.f + 10.f),
			std::floor(text.getPosition().y + text.getGlobalBounds().height + 4.f));
	percentage.setColor(textColor);
	percentage.setPosition(std::floor(text2.getPosition().x + text2.getGlobalBounds().width), std::floor(text2.getPosition().y));

	bool sens = true;
	sf::Event event;
	unsigned int timeStamp = 0;

	while (splashScreen->isOpen()) {
		while (splashScreen->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				*close = true;

			if (!loading) {
				centerBrowser->pollEvent(event, 0, 0, splashScreen->getSize().x, splashScreen->getSize().y);
				centerLayer.pollEvent(event, margin, browser2Y + stackY, splashScreen->getSize().x - margin * 2.f, buttonsHeight);
				if (modelSettingsCheckBox != nullptr)
					modelSettingsCheckBox->pollEvent(event, modelSettingsCheckBoxPos, displayModelText.getPosition().y, 16.f, 16.f);
			}
		}

		if (*close) {
			if (loading)
				*exitProgram = true;
			splashScreen->close();
			std::unique_lock<std::mutex> lock(*mutex);
			condition_variable->notify_all();
			break;
		}

		progressBarBgd.setSize(sf::Vector2f((splashScreen->getSize().x - 40.f) * *loadingPercentage / 100.f, 5));

		if (bAlpha != 255)
			SetLayeredWindowAttributes(splashScreen->getSystemHandle(), crKey, bAlpha += 3, dwFlags);

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

		splashScreen->clear(sf::Color(0, 0, 0, 0));

		splashScreen->draw(background);

		{
			progressBarBgd.setFillColor(sf::Color(45, 145, 239, 100));
			splashScreen->draw(progressBarBgd);
			ext.setPosition(progressBarBgd.getPosition() + sf::Vector2f(progressBarBgd.getSize().x, 0.f));
			splashScreen->draw(ext);
		}

		if (loading) {
			//if (*loadingPercentage != 100) {
			text.move(sf::Vector2f(-1, -1));
			text.setColor(textShadowColor);
			splashScreen->draw(text);
			text.setColor(textColor);
			text.move(sf::Vector2f(1, 1));
			splashScreen->draw(text);

			text2.move(sf::Vector2f(-1, -1));
			text2.setColor(textShadowColor);
			splashScreen->draw(text2);
			text2.setColor(textColor);
			text2.move(sf::Vector2f(1, 1));
			splashScreen->draw(text2);

			percentage.setString(" " + std::to_string(*loadingPercentage) + "%");
			m_pTaskBarlist->SetProgressValue(splashScreen->getSystemHandle(), *loadingPercentage, 100);

			percentage.move(sf::Vector2f(-1, -1));
			percentage.setColor(textShadowColor);
			splashScreen->draw(percentage);
			percentage.setColor(textColor);
			percentage.move(sf::Vector2f(1, 1));
			splashScreen->draw(percentage);
			/*} else {
			 //todo quitter / retour
			 }*/
		} else {

			centerLayer.draw(splashScreen, margin, browser2Y + stackY, splashScreen->getSize().x - margin * 2.f, buttonsHeight);
			centerBrowser->draw(splashScreen, 0, 0, splashScreen->getSize().x, splashScreen->getSize().y);
			if (modelSettingsCheckBox != nullptr)
				modelSettingsCheckBox->draw(splashScreen, modelSettingsCheckBoxPos, displayModelText.getPosition().y, 16.f, 16.f);

			if (modelSettingsBrowser != nullptr) {
				displayModelText.move(sf::Vector2f(-1, -1));
				displayModelText.setColor(textColor);
				splashScreen->draw(displayModelText);
				displayModelText.setColor(textShadowColor);
				displayModelText.move(sf::Vector2f(1, 1));
				splashScreen->draw(displayModelText);
			}
		}

		splashScreen->display();
	}
}

SplashScreenSaver::~SplashScreenSaver() {
	*close = true;

	if (thread != nullptr && thread->joinable()) {
		thread->join();
	}
}

const std::shared_ptr<bool>& SplashScreenSaver::getCloser() const {
	return close;
}

const std::shared_ptr<unsigned short>& SplashScreenSaver::getLoadingPercentage() const {
	return loadingPercentage;
}

