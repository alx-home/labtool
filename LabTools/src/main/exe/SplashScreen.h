/*
 * SplashScreen.h
 *
 *  Created on: 27 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_SPLASHSCREEN_H_
#define SRC_SPLASHSCREEN_H_

#ifdef WITH_INSTALLER
#include <algorithm>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

namespace sf {
class RenderWindow;
} /* namespace sf */

namespace std {
class thread;
} /* namespace std */

namespace installer {

class SplashScreen {
public:
	std::unique_ptr<std::mutex> mutex = std::move(std::unique_ptr<std::mutex>(new std::mutex()));
	std::unique_ptr<std::condition_variable> condition_variable = std::move(
			std::unique_ptr<std::condition_variable>(new std::condition_variable()));

	SplashScreen(const std::shared_ptr<std::string>& matlabFilePath, bool needInstallation);
	virtual ~SplashScreen();
	const std::shared_ptr<bool>& getCloser() const;
	const std::shared_ptr<bool>& shouldLoad() const;
	const std::shared_ptr<unsigned short>& getLoadingPercentage() const;
	const std::shared_ptr<bool>& getProgramCloser() const;
	const std::shared_ptr<sf::RenderWindow>& getWindow() const;

private:
	std::unique_ptr<std::thread> thread = nullptr;
	std::shared_ptr<std::string> matlabFilePath;
	std::shared_ptr<bool> shouldLoadFlag = std::make_shared<bool>(true);
	std::shared_ptr<bool> close = std::make_shared<bool>(false);
	std::shared_ptr<bool> exitProgram = std::make_shared<bool>(false);
	std::shared_ptr<unsigned short> loadingPercentage;
	std::shared_ptr<sf::RenderWindow> window = nullptr;
	bool needInstallation = false;

	void threadInst();
};

}  // namespace installer

#endif /* SRC_SPLASHSCREEN_H_ */
#endif
