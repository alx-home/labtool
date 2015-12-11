/*
 * Validator.h
 *
 *  Created on: 8 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_LABELISERMENU_VALIDATOR_H_
#define SRC_LABELISERMENU_VALIDATOR_H_

#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>

namespace window {
class Button;
class LabeliserMenu;
class Window;
} /* namespace window */

namespace window {

class Validator {
public:
	virtual ~Validator();
	static std::shared_ptr<Validator> create(const std::shared_ptr<Button>& validate, const std::shared_ptr<Button>& cancel, Window& window,
			const std::shared_ptr<LabeliserMenu>& labeliserMenu);

	void applyChanges();
	void abord();
	void start(const std::string& textDuringValidation, const std::string& textAfterValidation, bool wait = true);
	bool isEnable() const;
	void unPause();

private:
	std::shared_ptr<Button> validate;
	std::shared_ptr<Button> cancel;
	Window& window;
	std::shared_ptr<LabeliserMenu> labeliserMenu;
	std::string lastText = "";
	std::string textAfterValidation = "";
	bool enable = false;
	std::condition_variable waiter;
	std::mutex waiterMutex;

	Validator(const std::shared_ptr<Button>& validate, const std::shared_ptr<Button>& cancel, Window& window,
			const std::shared_ptr<LabeliserMenu>& labeliserMenu);
};

} /* namespace window */

#endif /* SRC_LABELISERMENU_VALIDATOR_H_ */
