/*
 template<typename BrowserType>
 * BrowserLayer<BrowserType>.cpp
 *
 *  Created on: 26 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "../browser/BrowserLayer.h"

#include <cstdlib>
#include <iostream>
#include <thread>

#include "../../../../utils/window/files/File.h"
#include "../Buttons/Button.h"
#include "../TextField.h"

namespace window {

BrowserLayer::BrowserLayer(const std::shared_ptr<TextField>& textField, const std::shared_ptr<Button>& browserButton,
		const std::string& title) :
		Layer(Layer::NoBorders), textField(textField), browserButton(browserButton), title(title) {
}

BrowserLayer::~BrowserLayer() {
	close();
}

void BrowserLayer::init() {

	browserButton->setCallBack([this](float timestamp) {
		std::unique_lock<std::mutex> lock (*browserWaiterMutex);
		browserWaiter->notify_all();
	});

	browserThread = std::make_shared<std::thread>([this]() {
		while(!*closeFlag)
		try {
			std::unique_lock<std::mutex> locker (*browserWaiterMutex);
			browserWaiter->wait(locker);
			if (*closeFlag)
			break;
			lock();
			textField->setText(browse(), true);
			unlock();
		} catch (const utils::window::File::BrowserException& e) {
			if (e.getErrorCode() == 0)
			std::clog << "[event][browser] closed." << std::endl;
			else
			std::cerr << "Error: dialog failure occurred when opening a file browser\n\terror code : "
			<< std::hex << e.getErrorCode() << std::endl;
			unlock();
		} catch (...) {
			std::cerr << "Error: unexpected error in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
			unlock();
		}
	});
}

const std::string& BrowserLayer::getText() const {
	return textField->getText();
}

void BrowserLayer::setTitle(const std::string& text) {
	this->title = title;
}

void BrowserLayer::setValidator(const std::function<bool(std::string&)>& validator) {
	textField->setValidator(validator);
}

void BrowserLayer::close() {
	*closeFlag = true;
	{
		std::unique_lock<std::mutex> lock(*browserWaiterMutex);
		browserWaiter->notify_all();
	}

	if (browserThread->joinable())
		browserThread->join();
}

void BrowserLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	textField->draw(window, x, y, width - 40, height);
	browserButton->draw(window, x + width - 40, y, 40, height);
}

void BrowserLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	textField->pollEvent(event, x, y, width - 40, height);
	browserButton->pollEvent(event, x + width - 40, y, 40, height);
}

void BrowserLayer::setCallBack(const std::function<void(float)>& callback) {
	browserButton->setCallBack(callback);
}

void BrowserLayer::enable() {
	if (lockIndex != 0)
		return;

	textField->enable();
	browserButton->enable();
}

void BrowserLayer::disable() {
	textField->disable();
	browserButton->disable();
}

void BrowserLayer::lock() {
	disable();
	++lockIndex;
}

void BrowserLayer::unlock() {
	if (lockIndex < 2) {
		lockIndex = 0;
		enable();
	} else
		--lockIndex;
}

void BrowserLayer::update() {
}

void BrowserLayer::setText(const std::string& text) {
	this->textField->setText(text, true);
}

} /* namespace window */
