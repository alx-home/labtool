/*
 * TextField.h
 *
 *  Created on: 27 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_TEXTFIELD_H_
#define SRC_WINDOW_LAYER_CONTENT_TEXTFIELD_H_

#include <SFML/Window/Keyboard.hpp>
#include <cstdint>
#include <functional>
#include <string>

#include "TextLayer.h"

namespace window {

class TextField: public TextLayer {
public:
	TextField(const std::string& initText = "", unsigned int size = 25, uint8_t alignment = LEFTALIGN,
			const std::function<void()>& onValidation = []() {}, const std::function<void()>& onEscape = []() {});
	virtual ~TextField();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	void pipeForward(float x, float y, float width, float height);
	void pipeBackward(float x, float y, float width, float height);
	void setPipePos(unsigned int pos, float x, float y, float width, float height);
	unsigned int getClickPos(float xClick, float yClick, float x, float y, float width, float height) const;
	void addChar(char character, float x, float y, float width, float height);
	void removeLeft(float x, float y, float width, float height);
	void removeRight(float x, float y, float width, float height);
	void updatePipePos(float x, float y, float width, float height);
	void setValidationFunc(const std::function<void()>& onValidation);
	void setEscapeFunc(const std::function<void()>& onEscape);
	void setValidator(const std::function<bool(std::string&)>& validator);
	void update() override;
	void disable();
	void enable();
	void setText(const std::string&, bool initialise);
	void setText(const std::string&) override;
	unsigned int getTextSize() const;

	typedef enum {
		Unknown = -1, AlphaNumeric, Charactere, SpecialCharactere
	} KeyType;

	KeyType getKeyType(const sf::Keyboard::Key& key) const;

protected:
	static TextField* activeField;
	bool pipeActive = false;
	unsigned int pipeTimestamp = 0;
	float pipePos = 0;
	float textDec = 0;
	static constexpr unsigned int pipeTimestampMax = 20;
	std::string lText;
	std::string rText = "";
	unsigned int keyTimestamp = 0;
	sf::Keyboard::Key keyPressed = sf::Keyboard::Unknown;
	unsigned int keyMaxTimestamp = 20;
	float lastWidth = 0;
	float lastHeight = 0;
	bool first = true;
	std::function<void()> onValidation;
	std::function<void()> onEscape;
	std::function<bool(std::string&)> validator = [](std::string&)->bool {return true;};
	unsigned int begginSelection = 0;
	unsigned int endSelection = 0;
	float begginSelectionPos = 0.f;
	float endSelectionPos = 0.f;
	bool mouseClicked = false;
	sf::RectangleShape textBox;
	sf::RectangleShape pipeBox;
	sf::RectangleShape selectionBox;
	bool isDisable = false;
	bool reinitialise = true;
	bool initialise = true;

	bool isAlphaNumeric(const sf::Keyboard::Key& key) const;
	bool isDigit(const sf::Keyboard::Key& key) const;
	bool isAlpha(const sf::Keyboard::Key& key) const;
	bool isSpecialCharactere(const sf::Keyboard::Key& key) const;
	char getDigit(const sf::Keyboard::Key& key) const;
	char getAlpha(const sf::Keyboard::Key& key) const;
	char getSpecialCharactere(const sf::Keyboard::Key& key) const;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_TEXTFIELD_H_ */
