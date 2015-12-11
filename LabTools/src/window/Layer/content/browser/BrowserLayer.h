/*
 * FileBrowser.h
 *
 *  Created on: 26 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_FILEBROWSER_H_
#define SRC_WINDOW_LAYER_CONTENT_FILEBROWSER_H_

#include <windows.h>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>

#include "../../Layer.h"

namespace std {
class thread;
} /* namespace std */

namespace window {
class Button;
class TextField;
} /* namespace window */

namespace window {

class BrowserLayer: public Layer {
public:
	BrowserLayer(const std::shared_ptr<TextField>& textField, const std::shared_ptr<Button>& browserButton, const std::string& title);
	virtual ~BrowserLayer();

	virtual void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height);
	virtual void pollEvent(const sf::Event& event, float x, float y, float width, float height);
	virtual void update();
	void disable();
	void lock();
	void enable();
	void unlock();
	void setCallBack(const std::function<void(float)>& callback = [](float timestamp) {});
	void close();
	void setValidator(const std::function<bool(std::string&)>& validator);
	const std::string& getText() const;
	void setText(const std::string& text);
	void setTitle(const std::string&);

	BrowserLayer& operator=(const BrowserLayer&) = delete;

protected:
	std::shared_ptr<TextField> textField;
	std::shared_ptr<Button> browserButton;
	std::shared_ptr<std::thread> browserThread = nullptr;
	std::shared_ptr<bool> closeFlag = std::make_shared<bool>(false);
	std::shared_ptr<std::mutex> browserWaiterMutex = std::make_shared<std::mutex>();
	std::shared_ptr<std::condition_variable> browserWaiter = std::make_shared<std::condition_variable>();
	std::string title;
	unsigned int lockIndex = 0;

	void init();
	virtual std::string browse() const = 0;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_FILEBROWSER_H_ */
