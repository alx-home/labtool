/*
 * SplashScreen.cpp
 *
 *  Created on: 27 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "SplashScreen.h"

#include <combaseapi.h>
#include <minwindef.h>
#include <process.h>
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
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "../Language/LanguageLoader.h"
#include "../resources/classes/SplashScreenBackground.h"
#include "../utils/opengl/FontLoader.h"
#include "../utils/window/files/Registry.h"
#include "Layer/content/Buttons/Button.h"
#include "Layer/content/CheckBox.h"
#include "Layer/content/browser/FileBrowserLayer.h"
#include "Layer/disposition/CenteredLayer.h"
#include "Layer/disposition/ConstrainedLayer.h"
#include "Layer/disposition/StakeLayer.h"
#include "Layer/Layer.h"

extern char softwareName[];

SplashScreen::SplashScreen(const std::shared_ptr<std::string>& modelFilePath, const std::shared_ptr<std::string>& sceneFilePath) :
		modelFilePath(modelFilePath), sceneFilePath(sceneFilePath), loadingPercentage(std::make_shared<unsigned short>(0)) {
	thread = std::move(std::unique_ptr<std::thread>(new std::thread(&SplashScreen::threadInst, this)));
}

SplashScreen::SplashScreen() :
		modelFilePath(nullptr), sceneFilePath(nullptr), loadingPercentage(nullptr) {
	thread = std::move(std::unique_ptr<std::thread>(new std::thread(&SplashScreen::threadInst, this)));
}

const std::shared_ptr<bool>& SplashScreen::getProgramCloser() const {
	return exitProgram;
}

HWND SplashScreen::getSystemHandle() const {
	if (splashScreen == nullptr)
		return nullptr;
	return splashScreen->getSystemHandle();
}

void SplashScreen::threadInst() {
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
	constexpr float modelCheckBoxPos = 350.f;
	bool loading = modelFilePath == nullptr;

	splashScreen->setPosition(
			sf::Vector2i((sf::VideoMode::getDesktopMode().width - width) / 2.f, (sf::VideoMode::getDesktopMode().height - height) / 2.f));
	splashScreen->setVerticalSyncEnabled(true);
	splashScreen->setActive(false);

	SetForegroundWindow(splashScreen->getSystemHandle());

	SetWindowLong(splashScreen->getSystemHandle(), GWL_EXSTYLE, WS_EX_LAYERED);
	ITaskbarList3* m_pTaskBarlist;
	CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**) &m_pTaskBarlist);
	if (loadingPercentage == nullptr)
		m_pTaskBarlist->SetProgressState(splashScreen->getSystemHandle(), TBPF_INDETERMINATE);
	else
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

	auto sceneBrowser = window::FileBrowserLayer(SERIALIZER->getSceneOuputFileSelectText(), 20);
	auto modelBrowser = window::FileBrowserLayer(modelFilePath == nullptr ? "" : *modelFilePath, 20);
	auto modelCheckBox = window::CheckBox();
	std::string lastModelText = modelFilePath == nullptr ? "" : *modelFilePath;

	modelCheckBox.setCallback([&modelBrowser, &lastModelText, this](bool checked) {
		if (checked) {
			modelBrowser.lock();
			lastModelText = modelBrowser.getText();
			modelBrowser.setText(modelFilePath == nullptr ? "" : *modelFilePath);
		} else {
			modelBrowser.unlock();
			modelBrowser.setText(lastModelText);
		}
	});

	sf::Text displayModelText(SERIALIZER->getDefaultModelText(), *utils::opengl::FontLoader::getArialFont(), 14);
	displayModelText.setPosition(modelCheckBoxPos + 20.f, browser2Y + stackY + 3.f);
	displayModelText.setColor(sf::Color(0, 0, 0));

	auto validateBtn = std::make_shared<window::Button>(false, SERIALIZER->getValidateButtonText(), 20,
	[this, &modelBrowser, &sceneBrowser, &loading](float timestamp) {
		std::string modelFilePathN = modelBrowser.getText();

		if (*modelFilePath != modelFilePathN) {
			auto result = MessageBox(splashScreen->getSystemHandle(), SERIALIZER->getSetModelAsDefaultCore().c_str(), SERIALIZER->getSetModelAsDefaultTitle().c_str(), MB_YESNOCANCEL);

			if (result == IDCANCEL)
			return;

			if (result == IDYES)
			utils::windows::Registry::setStringKeyValue("Default model", modelFilePathN);
		}

		*modelFilePath = modelFilePathN;
		*sceneFilePath = sceneBrowser.getText();
		modelBrowser.close();
		sceneBrowser.close();
		loading = true;

		std::unique_lock<std::mutex> lock(*mutex);
		condition_variable->notify_all();
	});
	auto exitBtn = std::make_shared<window::Button>(false, SERIALIZER->getExitButtonText(), 20, [this](float timestamp) {
		*close = true;
	});

	validateBtn->disable();
	validateBtn->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::Return });
	exitBtn->addKeyListener(std::vector<sf::Keyboard::Key> { sf::Keyboard::Escape });

	auto stack = std::make_shared<std::vector<std::shared_ptr<window::ConstrainedLayer>>>();
	stack->push_back(std::make_shared<window::ConstrainedLayer>(80.f, buttonsHeight, validateBtn));
	stack->push_back(std::make_shared<window::ConstrainedLayer>(80.f, buttonsHeight, exitBtn));

	auto stackLayer = std::make_shared<window::StakeLayer>(window::Layer::NoBorders, stack);
	auto centerLayer = window::CenteredLayer(std::make_shared<window::ConstrainedLayer>(160.f, buttonsHeight, stackLayer));
	bool modelValid = false;
	bool sceneValid = false;

	{
		std::function<bool(const std::string&)> validator = [&modelValid, &sceneValid, validateBtn] (const std::string& text) -> bool {
			std::ifstream file(text);
			unsigned int extInd = text.find_last_of(".");
			modelValid = file && extInd != text.size() && text.substr(extInd, text.size() - extInd) == ".c3d";

			if (modelValid && sceneValid)
			validateBtn->enable();
			else
			validateBtn->disable();

			if (file)
			file.close();

			return true;
		};

		modelBrowser.setValidator(validator);
		if (modelFilePath != nullptr)
			validator(*modelFilePath);

		if (modelValid)
			modelCheckBox.check();
	}

	{
		std::function<bool(const std::string&)> validator = [&modelValid, &sceneValid, validateBtn] (const std::string& text) -> bool {
			std::ifstream file(text);
			unsigned int extInd = text.find_last_of(".");
			sceneValid = file && extInd != text.size() && text.substr(extInd, text.size() - extInd) == ".c3d";

			if (modelValid && sceneValid)
			validateBtn->enable();
			else
			validateBtn->disable();

			if (file)
			file.close();

			return true;
		};

		sceneBrowser.setValidator(validator);
	}

	sf::Text name1("Lab", *utils::opengl::FontLoader::getArialFont(), 40);
	sf::Text name2("Tools", *utils::opengl::FontLoader::getArialFont(), 40);
	sf::Text text(SERIALIZER->getLoadingText(), *utils::opengl::FontLoader::getArialFont(), 25);
	sf::Text text2(SERIALIZER->getPleaseWaitText(), *utils::opengl::FontLoader::getArialFont(), 25);
	sf::Text percentage(loadingPercentage == nullptr ? " ?%" : " 0%", *utils::opengl::FontLoader::getArialFont(), 25);
	sf::Color textColor = sf::Color(45, 145, 239);
	sf::Color textShadowColor = sf::Color(45, 145, 239, 80);
	sf::Color nameColor = textColor;
	sf::RectangleShape progressBarBgd = sf::RectangleShape();
	sf::RectangleShape ext = sf::RectangleShape();
	progressBarBgd.setPosition(20.f, splashScreen->getSize().y - 30);
	ext.setSize(sf::Vector2f(5.f, 5.f));
	ext.setFillColor(textShadowColor);
	background.setSize(sf::Vector2f(splashScreen->getSize().x, splashScreen->getSize().y));
	background.setTexture(&backgroundTexture);

	name1.setPosition(std::floor((splashScreen->getSize().x - (name1.getGlobalBounds().width + 2.f + name2.getGlobalBounds().width)) / 2.f),
			25.f);
	name1.setColor(nameColor);
	name2.setPosition(std::floor(name1.getPosition().x + 2.f + name1.getGlobalBounds().width), 35.f);
	name2.setColor(nameColor);
	text.setPosition(std::floor((splashScreen->getSize().x - text.getGlobalBounds().width) / 2.f), 100.f);
	text2.setColor(textColor);
	text2.setPosition(std::floor((splashScreen->getSize().x - text.getGlobalBounds().width) / 2.f + 10.f),
			std::floor(text.getPosition().y + text.getGlobalBounds().height + 4.f));
	percentage.setColor(textColor);
	percentage.setPosition(std::floor(text2.getPosition().x + text2.getGlobalBounds().width), std::floor(text2.getPosition().y));

	bool sens = true;
	sf::Event event;
	unsigned int timeStamp = 0;

	auto layer = window::TextLayer("");//todo dirtfix

	while (splashScreen->isOpen()) {
		while (splashScreen->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				*close = true;

			if (!loading) {
				modelBrowser.pollEvent(event, margin, browser1Y, splashScreen->getSize().x - margin * 2.f, browserHeight);
				sceneBrowser.pollEvent(event, margin, browser2Y, splashScreen->getSize().x - margin * 2.f, browserHeight);
				centerLayer.pollEvent(event, margin, browser2Y + stackY, splashScreen->getSize().x - margin * 2.f, buttonsHeight);
				modelCheckBox.pollEvent(event, modelCheckBoxPos, displayModelText.getPosition().y, 16.f, 16.f);
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

		if (loadingPercentage != nullptr)
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

		nameColor.r = textColor.r * (20 + timeStamp * 3) / 100;
		nameColor.g = textColor.g * (20 + timeStamp * 3) / 100;
		nameColor.b = textColor.b * (20 + timeStamp * 3) / 100;

		splashScreen->clear(sf::Color(0, 0, 0, 0));

		splashScreen->draw(background);

		{
			progressBarBgd.setFillColor(sf::Color(45, 145, 239, 100));
			splashScreen->draw(progressBarBgd);
			ext.setPosition(progressBarBgd.getPosition() + sf::Vector2f(progressBarBgd.getSize().x, 0.f));
			splashScreen->draw(ext);
		}

		name1.move(sf::Vector2f(-1, -1));
		name1.setColor(textShadowColor);
		splashScreen->draw(name1);
		name1.setColor(nameColor);
		name1.move(sf::Vector2f(1, 1));
		splashScreen->draw(name1);

		name2.move(sf::Vector2f(-1, -1));
		name2.setColor(textShadowColor);
		splashScreen->draw(name2);
		name2.setColor(nameColor);
		name2.move(sf::Vector2f(1, 1));
		splashScreen->draw(name2);

		if (loading) {
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

			if (loadingPercentage != nullptr) {
				percentage.setString(" " + std::to_string(*loadingPercentage) + "%");
				m_pTaskBarlist->SetProgressValue(splashScreen->getSystemHandle(), *loadingPercentage, 100);
			}

			percentage.move(sf::Vector2f(-1, -1));
			percentage.setColor(textShadowColor);
			splashScreen->draw(percentage);
			percentage.setColor(textColor);
			percentage.move(sf::Vector2f(1, 1));
			splashScreen->draw(percentage);
		} else {
			layer.setWidthMax(0);//todo dirtfix
			layer.draw(splashScreen, -200., -200., 0, 0);//todo dirtfix
			modelBrowser.draw(splashScreen, margin, browser1Y, splashScreen->getSize().x - margin * 2.f, browserHeight);
			sceneBrowser.draw(splashScreen, margin, browser2Y, splashScreen->getSize().x - margin * 2.f, browserHeight);

			centerLayer.draw(splashScreen, margin, browser2Y + stackY, splashScreen->getSize().x - margin * 2.f, buttonsHeight);
			modelCheckBox.draw(splashScreen, modelCheckBoxPos, displayModelText.getPosition().y, 16.f, 16.f);

			displayModelText.move(sf::Vector2f(-1, -1));
			displayModelText.setColor(textColor);
			splashScreen->draw(displayModelText);
			displayModelText.setColor(textShadowColor);
			displayModelText.move(sf::Vector2f(1, 1));
			splashScreen->draw(displayModelText);
		}

		splashScreen->display();
	}
}

SplashScreen::~SplashScreen() {
	*close = true;

	if (thread != nullptr && thread->joinable()) {
		thread->join();
	}
}

const std::shared_ptr<bool>& SplashScreen::getCloser() const {
	return close;
}

const std::shared_ptr<unsigned short>& SplashScreen::getLoadingPercentage() const {
	return loadingPercentage;
}
