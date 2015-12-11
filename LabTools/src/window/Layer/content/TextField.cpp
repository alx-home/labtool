/*
 * TextField.cpp
 *
 *  Created on: 27 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "TextField.h"

#include <GL/glew.h>
#include <string.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <exception>
#include <iostream>
#include <memory>
#include <windows.h>

#include "../../../utils/opengl/FontLoader.h"

namespace window {

TextField* TextField::activeField = nullptr;

TextField::TextField(const std::string& initText, unsigned int size, uint8_t alignment, const std::function<void()>& onValidation,
		const std::function<void()>& onEscape) :
		TextLayer(initText, size, false, alignment), lText(initText), onValidation(onValidation), onEscape(onEscape), textBox(), pipeBox(), selectionBox() {
	activeField = this;
	initialise = true;

	textBox.setFillColor(sf::Color(240, 240, 240));
	textBox.setOutlineThickness(-1.f);
	textBox.setOutlineColor(sf::Color(0, 0, 0));

	pipeBox.setFillColor(sf::Color(0, 0, 0));
	selectionBox.setFillColor(sf::Color(110, 200, 240, 100));
}

TextField::~TextField() {
}

void TextField::setValidationFunc(const std::function<void()>& onValidation) {
	this->onValidation = onValidation;
}

void TextField::setEscapeFunc(const std::function<void()>& onEscape) {
	this->onEscape = onEscape;
}

void TextField::setValidator(const std::function<bool(std::string&)>& validator) {
	this->validator = validator;
}

void TextField::update() {
}

void TextField::disable() {
	isDisable = true;
}

void TextField::enable() {
	isDisable = false;
}

void TextField::setText(const std::string& text2) {
	std::string text = text2;

	activeField = this;
	if (validator(text))
		TextLayer::setText(text);
}

void TextField::setText(const std::string& text2, bool initialise) {
	std::string text = text2;

	if (initialise)
		this->initialise = true;

	setText(text);
}

unsigned int TextField::getTextSize() const {
	return textSize;
}

void TextField::updatePipePos(float x, float y, float width, float height) {
	sf::Text text(lText, *utils::opengl::FontLoader::getArialFont(), textSize);
	pipePos = text.getGlobalBounds().width;
	textDec = 0;

	while (pipePos > width) {
		text.setString(text.getString().substring(0, ((std::string) text.getString()).size() - 1));
		textDec += pipePos - text.getGlobalBounds().width;
		pipePos = text.getGlobalBounds().width;
	}

	if (begginSelection > this->text.size())
		begginSelection = endSelection = 0;
	else if (endSelection > this->text.size())
		endSelection = this->text.size();

	if (begginSelection == 0 && endSelection == 0)
		begginSelectionPos = endSelectionPos = 0;
	else {
		text.setString(this->text.substr(0, begginSelection));
		begginSelectionPos = text.getGlobalBounds().width;
		text.setString(this->text.substr(0, endSelection));
		endSelectionPos = text.getGlobalBounds().width;
	}
}

unsigned int TextField::getClickPos(float xClick, float yClick, float x, float y, float width, float height) const {
	if (text.size() == 0)
		return 0;

	sf::Text text("", *utils::opengl::FontLoader::getArialFont(), textSize);
	sf::Text text1("", *utils::opengl::FontLoader::getArialFont(), textSize);
	unsigned int result = 0;
	float delta = xClick - x;

	while (text.getGlobalBounds().width + text1.getGlobalBounds().width / 2.f < delta + textDec) {
		if (this->text.size() == result - 1)
			return result - 1;

		++result;
		text.setString(this->text.substr(0, result));
		if (result > 1)
			text1.setString(this->text.substr(result - 2, 1));
	}

	return result;
}

void TextField::setPipePos(unsigned int pos, float x, float y, float width, float height) {
	unsigned int lastPos = lText.size();
	if (pos > 0)
		lText = text.substr(0, pos);
	else
		lText = "";

	if (pos < text.size())
		rText = text.substr(pos, text.size() - pos);
	else
		rText = "";

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || mouseClicked) {
		if (begginSelection == 0 && endSelection == 0) {
			begginSelection = lastPos;
			endSelection = lText.size();
		} else
			endSelection = lText.size();
	} else {
		begginSelection = endSelection = 0;
		begginSelectionPos = endSelectionPos = 0.f;
	}

	updatePipePos(x, y, width, height);

	pipeActive = true;
	pipeTimestamp = 0;
}

void TextField::pipeForward(float x, float y, float width, float height) {
	if (rText.size() != 0) {
		lText += rText.substr(0, 1);
		rText = rText.substr(1, rText.size() - 1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
		if (begginSelection == 0 && endSelection == 0) {
			begginSelection = lText.size() - 1;
			endSelection = lText.size();
		} else if (endSelection < text.size())
			++endSelection;
	} else {
		begginSelection = endSelection = 0;
		begginSelectionPos = endSelectionPos = 0.f;
	}

	updatePipePos(x, y, width, height);

	pipeActive = true;
	pipeTimestamp = 0;
}

void TextField::pipeBackward(float x, float y, float width, float height) {
	if (lText.size() != 0) {
		rText = lText.substr(lText.size() - 1, 1) + rText;
		lText = lText.substr(0, lText.size() - 1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
		if (begginSelection == 0 && endSelection == 0) {
			begginSelection = lText.size() + 1;
			endSelection = lText.size();
		} else if (endSelection > 0)
			--endSelection;
	} else {
		begginSelection = endSelection = 0;
		begginSelectionPos = endSelectionPos = 0.f;
	}

	updatePipePos(x, y, width, height);

	pipeActive = true;
	pipeTimestamp = 0;
}

void TextField::addChar(char character, float x, float y, float width, float height) {
	if (!(begginSelection == 0 && endSelection == 0))
		removeLeft(x, y, width, height);

	lText += character;
	setText(lText + rText);
	pipeActive = true;
	pipeTimestamp = 0;

	updatePipePos(x, y, width, height);
}

void TextField::removeLeft(float x, float y, float width, float height) {
	if (!(begginSelection == 0 && endSelection == 0)) {
		if (begginSelection > endSelection) {
			float tmp = begginSelection;
			begginSelection = endSelection;
			endSelection = tmp;
		}

		lText = text.substr(0, begginSelection);
		rText = text.substr(endSelection, text.size() - endSelection);
		setText(lText + rText);
		begginSelection = endSelection = 0;
		begginSelectionPos = endSelectionPos = 0.f;

		updatePipePos(x, y, width, height);
		return;
	}

	if (!lText.size())
		return;

	lText = lText.substr(0, lText.size() - 1);
	setText(lText + rText);
	pipeActive = true;
	pipeTimestamp = 0;

	updatePipePos(x, y, width, height);
}

void TextField::removeRight(float x, float y, float width, float height) {
	if (!(begginSelection == 0 && endSelection == 0)) {
		if (begginSelection > endSelection) {
			float tmp = begginSelection;
			begginSelection = endSelection;
			endSelection = tmp;
		}

		lText = text.substr(0, begginSelection);
		rText = text.substr(endSelection, text.size() - endSelection);
		setText(lText + rText);
		begginSelection = endSelection = 0;
		begginSelectionPos = endSelectionPos = 0.f;

		updatePipePos(x, y, width, height);
		return;
	}

	if (!rText.size())
		return;

	rText = rText.substr(1, rText.size() - 1);
	setText(lText + rText);
	pipeActive = true;
	pipeTimestamp = 0;
}

void TextField::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	float x2 = x + 2.f;
	float width2 = width - 4.f;

	if (first) {
		updatePipePos(x2, y, width2, height);
		first = false;
	}

	pipeBox.setSize(sf::Vector2f(2.f, height));

	if (keyPressed == sf::Keyboard::Left)
		if (keyTimestamp == keyMaxTimestamp)
			pipeBackward(x2, y, width2, height);
		else
			++keyTimestamp;
	else if (keyPressed == sf::Keyboard::Right)
		if (keyTimestamp == keyMaxTimestamp)
			pipeForward(x2, y, width2, height);
		else
			++keyTimestamp;
	else if ((keyPressed >= sf::Keyboard::A && keyPressed <= sf::Keyboard::Num9)
			|| (keyPressed >= sf::Keyboard::Numpad0 && keyPressed <= sf::Keyboard::Numpad9))
		if (keyTimestamp == keyMaxTimestamp)
			addChar(keyPressed, x2, y, width2, height);
		else
			++keyTimestamp;
	else if (keyPressed == sf::Keyboard::Delete)
		if (keyTimestamp == keyMaxTimestamp)
			removeRight(x2, y, width2, height);
		else
			++keyTimestamp;
	else if (keyPressed == sf::Keyboard::BackSpace)
		if (keyTimestamp == keyMaxTimestamp)
			removeLeft(x2, y, width2, height);
		else
			++keyTimestamp;

	if (activeField == this && !isDisable) {
		reinitialise = true;

		if (pipeTimestamp == pipeTimestampMax) {
			pipeTimestamp = 0;
			pipeActive = !pipeActive;
		}
	} else {
		if (reinitialise)
			setPipePos(text.size(), x2, y, width2, height);
		reinitialise = false;

		pipeActive = false;
		pipeTimestamp = 0;
	}
//todo defilement
	if (initialise) {
		setPipePos(text.size(), x2, y, width2, height);
		initialise = false;
	}

	textBox.setPosition(x, y);
	textBox.setSize(sf::Vector2f(width, height));

	glEnable(GL_STENCIL_TEST);

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);

	glClear(GL_STENCIL_BUFFER_BIT);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	window->draw(textBox);

	glStencilMask(0x00);

	glStencilFunc(GL_EQUAL, 1, 0xFF);

	TextLayer::draw(window, x2 - textDec, y, width2 + textDec, height);

	if (pipeActive) {
		pipeBox.setPosition(x2 + pipePos, y);
		window->draw(pipeBox);
	}

	if (!(begginSelection == 0 && endSelection == 0)) {
		if (begginSelection > endSelection) {
			selectionBox.setPosition(x2 - textDec + endSelectionPos, y);
			selectionBox.setSize(sf::Vector2f(begginSelectionPos - endSelectionPos, height));
		} else {
			selectionBox.setPosition(x2 - textDec + begginSelectionPos, y);
			selectionBox.setSize(sf::Vector2f(endSelectionPos - begginSelectionPos, height));
		}

		window->draw(selectionBox);
	}

	glDisable(GL_STENCIL_TEST);

	if (isDisable) {
		sf::RectangleShape greyBox = textBox;
		greyBox.setFillColor(sf::Color(greyBox.getFillColor().r, greyBox.getFillColor().g, greyBox.getFillColor().b, 120));

		window->draw(greyBox);
	}

	++pipeTimestamp;
}

void TextField::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	if (isDisable)
		return;

	float x2 = x + 2.f;
	float width2 = width - 4.f;

	if (activeField != this)
		if (event.type != sf::Event::MouseButtonPressed)
			return;

	TextField::KeyType keyType;
	bool isCtrlEnable = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

	switch (event.type) {

	case sf::Event::KeyPressed:
		if ((event.key.code == sf::Keyboard::Left && keyPressed != sf::Keyboard::Left)
				|| (event.key.code == sf::Keyboard::Right && keyPressed != sf::Keyboard::Right) || isAlphaNumeric(event.key.code)
				|| (event.key.code == sf::Keyboard::Delete) || (event.key.code == sf::Keyboard::BackSpace)
				|| (event.key.code == sf::Keyboard::Home) || (event.key.code == sf::Keyboard::End)) {
			keyPressed = event.key.code;

			bool flag = true;

			if (event.key.code == sf::Keyboard::A
					&& (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
				begginSelection = 0;
				endSelection = text.size();
				lText = text;
				rText = "";
				updatePipePos(x2, y, width2, height);
			} else if (event.key.code == sf::Keyboard::Home)
				setPipePos(0, x2, y, width2, height);
			else if (event.key.code == sf::Keyboard::End) {
				setPipePos(text.size(), x2, y, width2, height);
			} else if ((event.key.code == sf::Keyboard::X || event.key.code == sf::Keyboard::C) && isCtrlEnable) {
				if (!(begginSelection == 0 && endSelection == 0)) {
					if (OpenClipboard(0)) {
						EmptyClipboard();
						std::string text;

						if (begginSelection < endSelection)
							text = this->text.substr(begginSelection, endSelection - begginSelection);
						else
							text = this->text.substr(endSelection, begginSelection - endSelection);

						HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);

						if (hg) {
							memcpy(GlobalLock(hg), text.c_str(), text.size() + 1);
							GlobalUnlock(hg);
							SetClipboardData(CF_TEXT, hg);
							GlobalFree(hg);

							if (event.key.code == sf::Keyboard::X)
								removeRight(x2, y, width2, height);
						}

						CloseClipboard();
					}
				}
			} else if (event.key.code == sf::Keyboard::V && isCtrlEnable) {
				if (!(begginSelection == 0 && endSelection == 0))
					removeRight(x2, y, width2, height);

				if (OpenClipboard(0)) {
					std::string text;

					if (IsClipboardFormatAvailable(CF_TEXT)) {
						HGLOBAL hg = GetClipboardData(CF_TEXT);

						if (hg != nullptr) {
							LPTSTR result = (LPTSTR) GlobalLock(hg);

							if (result != nullptr) {
								this->lText += result;
								setText(lText + rText);
								updatePipePos(x2, y, width2, height);
								GlobalUnlock(hg);
							}
						}
					}

					CloseClipboard();
				}
			} else if ((keyType = getKeyType(keyPressed)) != TextField::Unknown) {
				if (keyType == TextField::AlphaNumeric)
					addChar(getDigit(keyPressed), x2, y, width2, height);
				else if (keyType == TextField::Charactere)
					addChar(getAlpha(keyPressed), x2, y, width2, height);
				else
					addChar(getSpecialCharactere(keyPressed), x2, y, width2, height);
			} else if (event.key.code == sf::Keyboard::Delete)
				removeRight(x2, y, width2, height);
			else if (event.key.code == sf::Keyboard::BackSpace)
				removeLeft(x2, y, width2, height);
			else
				flag = false;

			if (flag) {
				pipeActive = true;
				pipeTimestamp = 0;
				keyPressed = sf::Keyboard::Unknown;
			}

			keyTimestamp = 0;
		}

		pipeActive = true;
		pipeTimestamp = 0;
		break;

	case sf::Event::KeyReleased:

		if (event.key.code == sf::Keyboard::Left && keyPressed == sf::Keyboard::Left) {
			if (keyMaxTimestamp > keyTimestamp)
				pipeBackward(x2, y, width2, height);

			keyPressed = sf::Keyboard::Unknown;
			pipeActive = true;
			pipeTimestamp = 0;
		} else if (event.key.code == sf::Keyboard::Right && keyPressed == sf::Keyboard::Right) {
			if (keyMaxTimestamp > keyTimestamp)
				pipeForward(x2, y, width2, height);

			pipeActive = true;
			pipeTimestamp = 0;
			keyPressed = sf::Keyboard::Unknown;
		} else if ((keyType = getKeyType(keyPressed)) != TextField::Unknown) {
			if (keyMaxTimestamp > keyTimestamp) {
				if (keyType == TextField::AlphaNumeric)
					addChar(getDigit(keyPressed), x2, y, width2, height);
				else if (keyType == TextField::Charactere)
					addChar(getAlpha(keyPressed), x2, y, width2, height);
				else
					addChar(getSpecialCharactere(keyPressed), x2, y, width2, height);
			}

			pipeActive = true;
			pipeTimestamp = 0;
			keyPressed = sf::Keyboard::Unknown;
		} else if (event.key.code == sf::Keyboard::Delete && keyPressed == sf::Keyboard::Delete) {
			if (keyMaxTimestamp > keyTimestamp) {
				removeRight(x2, y, width2, height);
			}

			pipeActive = true;
			pipeTimestamp = 0;
			keyPressed = sf::Keyboard::Unknown;
		} else if (event.key.code == sf::Keyboard::BackSpace && keyPressed == sf::Keyboard::BackSpace) {
			if (keyMaxTimestamp > keyTimestamp) {
				removeLeft(x2, y, width2, height);
			}

			pipeActive = true;
			pipeTimestamp = 0;
			keyPressed = sf::Keyboard::Unknown;
		} else if (event.key.code == sf::Keyboard::Return)
			onValidation();
		else if (event.key.code == sf::Keyboard::Escape)
			onEscape();

		break;

	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button != sf::Mouse::Left)
			break;

		{
			const float& xMousePos = event.mouseButton.x;
			const float& yMousePos = event.mouseButton.y;

			if (xMousePos < x2 + width2 && xMousePos > x2 && yMousePos < y + height && yMousePos > y) {
				setPipePos(getClickPos(xMousePos, yMousePos, x2, y, width2, height), x2, y, width2, height);
				mouseClicked = true;
				activeField = this;
			} else
				mouseClicked = false;
		}
		break;

	case sf::Event::MouseButtonReleased:
		mouseClicked = false;
		break;

	case sf::Event::MouseMoved:
		if (mouseClicked) {
			const float& xMousePos = event.mouseMove.x;
			const float& yMousePos = event.mouseMove.y;

			setPipePos(getClickPos(xMousePos, yMousePos, x2, y, width2, height), x2, y, width2, height);
		}
		break;

	default:
		break;
	}
}

TextField::KeyType TextField::getKeyType(const sf::Keyboard::Key& key) const {
	if (isDigit(key))
		return TextField::AlphaNumeric;
	else if (isAlpha(key))
		return TextField::Charactere;
	else if (isSpecialCharactere(key))
		return TextField::SpecialCharactere;

	return TextField::Unknown;
}

bool TextField::isAlphaNumeric(const sf::Keyboard::Key& key) const {
	return isDigit(key) || isAlpha(key) || isSpecialCharactere(key);
}

bool TextField::isDigit(const sf::Keyboard::Key& key) const {
	bool shiftEnable = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
	return (key > sf::Keyboard::Z && key < sf::Keyboard::Escape && shiftEnable)
			|| (key > sf::Keyboard::Down && key < sf::Keyboard::F1 && !shiftEnable);
}

bool TextField::isAlpha(const sf::Keyboard::Key& key) const {
	return key < sf::Keyboard::Num0 && key > sf::Keyboard::Unknown;
}

bool TextField::isSpecialCharactere(const sf::Keyboard::Key& key) const {
	return (key > sf::Keyboard::Z && key < sf::Keyboard::Escape
			&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
			|| (key > sf::Keyboard::Menu && key < sf::Keyboard::Return) || (key > sf::Keyboard::Delete && key < sf::Keyboard::Left)
			|| key == sf::Keyboard::Space;
}

char TextField::getDigit(const sf::Keyboard::Key& key) const {
	if (key < sf::Keyboard::Escape)
		return (char) (key - sf::Keyboard::Num0 + 48);
	else
		return (char) (key - sf::Keyboard::Numpad0 + 48);
}

char TextField::getAlpha(const sf::Keyboard::Key& key) const {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		return (char) (key + 65);
	else
		return (char) (key + 97);
}

char TextField::getSpecialCharactere(const sf::Keyboard::Key& key) const {
	bool isShiftEnable = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift));
	bool isAltEnable = sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);

	switch (key) {
	case sf::Keyboard::Space:
		return ' ';

	case sf::Keyboard::Add:
		return '+';

	case sf::Keyboard::Subtract:
		return '-';

	case sf::Keyboard::Multiply:
		return '*';

	case sf::Keyboard::Divide:
		return '/';

	case sf::Keyboard::LBracket:
		return isShiftEnable ? '°' : (isAltEnable ? ']' : ')');

	case sf::Keyboard::RBracket:
		return isShiftEnable ? '¨' : '^'; //todo accents ...

	case sf::Keyboard::SemiColon:
		return isShiftEnable ? '£' : (isAltEnable ? '¤' : '$');

	case sf::Keyboard::Comma:
		return isShiftEnable ? '?' : ',';

	case sf::Keyboard::Period:
		return isShiftEnable ? '.' : ';';

	case sf::Keyboard::Quote:
		return '\'';

	case sf::Keyboard::Slash:
		return isShiftEnable ? '/' : ':';

	case sf::Keyboard::BackSlash:
		return isShiftEnable ? 'µ' : '*';

	case sf::Keyboard::Tilde:
		return isShiftEnable ? 'ù' : '%';

	case sf::Keyboard::Equal:
		return isShiftEnable ? '+' : (isAltEnable ? '}' : '=');

	case sf::Keyboard::Dash:
		return '-';

	default:
		if (key > sf::Keyboard::Z && key < sf::Keyboard::Escape && !isShiftEnable)
			if (isAltEnable)
				switch (key) {
				case sf::Keyboard::Num0:
					return '@';

				case sf::Keyboard::Num1:
					return '&';

				case sf::Keyboard::Num2:
					return '~';

				case sf::Keyboard::Num3:
					return '#';

				case sf::Keyboard::Num4:
					return '{';

				case sf::Keyboard::Num5:
					return '[';

				case sf::Keyboard::Num6:
					return '|';

				case sf::Keyboard::Num7:
					return '`';

				case sf::Keyboard::Num8:
					return '\\';

				case sf::Keyboard::Num9:
					return '^';

				default:
					return 0;
				}
			else
				switch (key) {
				case sf::Keyboard::Num0:
					return 'à';

				case sf::Keyboard::Num1:
					return '&';

				case sf::Keyboard::Num2:
					return 'é';

				case sf::Keyboard::Num3:
					return '"';

				case sf::Keyboard::Num4:
					return '\'';

				case sf::Keyboard::Num5:
					return '(';

				case sf::Keyboard::Num6:
					return '-';

				case sf::Keyboard::Num7:
					return 'è';

				case sf::Keyboard::Num8:
					return '_';

				case sf::Keyboard::Num9:
					return 'ç';

				default:
					return 0;
				}
		return 0;
	}
}

} /* namespace window */
