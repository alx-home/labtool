/*
 * SplashScreenSaver.h
 *
 *  Created on: 17 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_SPLASHSCREENSAVER_H_
#define SRC_WINDOW_SPLASHSCREENSAVER_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <windows.h>
#include <algorithm>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

class SplashScreenSaver {
public:
	std::unique_ptr<std::mutex> mutex = std::move(std::unique_ptr<std::mutex>(new std::mutex()));
	std::unique_ptr<std::condition_variable> condition_variable = std::move(
			std::unique_ptr<std::condition_variable>(new std::condition_variable()));

	SplashScreenSaver(const std::shared_ptr<std::string>& modelSettingsFilePath,
			const std::shared_ptr<std::string>& sceneFilePath, bool modelSettingsChanged);
	virtual ~SplashScreenSaver();
	const std::shared_ptr<bool>& getCloser() const;
	const std::shared_ptr<unsigned short>& getLoadingPercentage() const;
	const std::shared_ptr<bool>& getProgramCloser() const;
	HWND getSystemHandle() const;

private:
	std::unique_ptr<std::thread> thread = nullptr;
	std::shared_ptr<std::string> modelSettingsFilePath, sceneFilePath;
	std::shared_ptr<bool> close = std::make_shared<bool>(false);
	std::shared_ptr<bool> exitProgram = std::make_shared<bool>(false);
	std::shared_ptr<unsigned short> loadingPercentage;
	std::shared_ptr<sf::RenderWindow> splashScreen = nullptr;
	bool modelSettingsChanged;

	void threadInst();
};

#endif /* SRC_WINDOW_SPLASHSCREENSAVER_H_ */
