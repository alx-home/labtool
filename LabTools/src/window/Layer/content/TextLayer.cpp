/*
 * TextLayer.cpp
 *
 *  Created on: 10 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "TextLayer.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "../../../utils/opengl/FontLoader.h"

namespace window {

TextLayer::TextLayer(const std::string& text, unsigned int size, bool resizable, uint8_t alignment, const sf::Color& textColor) :
		Layer(Layer::NoBorders), textSize(size), alignment(alignment), resizable(resizable), textColor(textColor) {
	setText(text);

	{
		sf::Text textShape("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@", *utils::opengl::FontLoader::getArialFont(),
				textSize);
		textHeight = textShape.getGlobalBounds().height;
	}

}

TextLayer::~TextLayer() {
}

void TextLayer::update() {
}

void TextLayer::setMargin(unsigned short margin) {
	this->margin = margin;
}

void TextLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	if (lastWidth != width) {
		setWidthMax(width - (alignment & CENTERED ? 2 * margin : margin));
	}

	sf::Text textShape;
	textShape.setFont(*utils::opengl::FontLoader::getArialFont());
	textShape.setFillColor(textColor);
	textShape.setCharacterSize(textSize);

	static bool first = true;

	for (unsigned int i = 0; i < lines.size(); ++i) {

		if (first){
			lines[i] = "><à'(),|{}[]!@#$%^&*_+\\/°";// todo dirtfix
			first = false;
		}

		textShape.setString(lines[i]);

		float width = textShape.getGlobalBounds().width;

		if (alignment == CENTERED)
			textShape.setPosition(std::floor((this->width - width) / 2.f + x) + margin, std::floor(textHeight * i + y));
		else if (alignment == RIGHTALIGN)
			textShape.setPosition(std::floor(this->width - width + x) - margin, std::floor(textHeight * i + y));
		else
			textShape.setPosition(std::floor(x) + margin, std::floor(textHeight * i + y));

		window->draw(textShape);
	}
}

void TextLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
}

float TextLayer::getHeight() const {
	return height;
}

void TextLayer::setWidthMax(float width) {
	this->lastWidth = width;
	this->width = width;
	updateTexture();
}

float TextLayer::getTextWidth() const {
	return textWidth;
}

const std::string& TextLayer::getText() const {
	return text;
}

void TextLayer::setText(const std::string& text) {
	this->text = text;
	this->lastWidth = -1.f;

	sf::Text textShape(text, *utils::opengl::FontLoader::getArialFont(), textSize);
	textWidth = textShape.getGlobalBounds().width;
}

void TextLayer::updateTexture() {
	if (!resizable || width == -1.f)
		width = textWidth;

	lines.clear();
	bool resized = false;

	std::vector<std::string> words;
	{
		std::string word = "";

		for (unsigned int i = 0; i < this->text.size(); ++i) {
			if (this->text.c_str()[i] == ' ' || this->text.c_str()[i] == '\n' || this->text.c_str()[i] == '\t') {
				if (word.size() > 0)
					words.push_back(word);
				words.push_back(this->text.substr(i, 1));
				word = "";
			} else
				word += this->text.c_str()[i];
		}

		words.push_back(word);
	}

	std::string line = "";
	sf::Text textShape(text, *utils::opengl::FontLoader::getArialFont(), textSize);
	textShape.setFillColor(sf::Color(0, 0, 0));

	for (const auto& word : words) {
		if (word == "\n") {
			lines.push_back(line);
			line = "";
			continue;
		}

		textShape.setString(line + word);

		if (textShape.getGlobalBounds().width > width) {
			textShape.setString(word);

			if (textShape.getGlobalBounds().width > width) {
				for (unsigned int i = 0; i < word.size(); ++i) {
					textShape.setString(line + word.c_str()[i]);

					if (textShape.getGlobalBounds().width > width) {
						if (line == "") {
							std::cerr << "Error : error in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
							return;
						}

						lines.push_back(line);
						line = "";
						--i;
					} else
						line += word.c_str()[i];
				}
			} else {
				lines.push_back(line);
				line = word;
			}
		} else
			line += word;
	}

	lines.push_back(line);

	height = textHeight * lines.size() + textSize / 3.f;
}

} /* namespace window */
