/*
 * Reader.cpp
 *
 *  Created on: 29 déc. 2015
 *      Author: alex
 */

#include "Reader.h"

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>

#include "exceptions/CloseTagSymbolNotFoundException.h"
#include "exceptions/CloseTagSymbolUnexpectedException.h"
#include "exceptions/EndofFileException.h"
#include "exceptions/OpenFileException.h"
#include "exceptions/ParamNameNotFoundException.h"
#include "exceptions/TagContentException.h"
#include "exceptions/TagNameNotFoundException.h"
#include "exceptions/TagsNameMismatchException.h"
#include "exceptions/UnexpectedSymbolException.h"
#include "exceptions/ValueNotFoundException.h"
#include "tag/Content.h"

namespace utils {
namespace xml {

Reader::File::File(const std::string& filePath) :
		std::ifstream(filePath, std::ios::binary) {
	if (!*this)
		throw exceptions::OpenFileException();
}

Reader::File::~File() {
	std::ifstream::close();
}

char Reader::File::get() {
	char result = std::ifstream::get();

	if (result == '\n') {
		++line;
		lastCols.push(col);
		col = 0;
	} else
		++col;

	return result;
}

char Reader::File::getNextChar() {
	char character;
	character = get();

	if (character == '\\') {
		character = get();

		if (character == '"')
			return 0;

		throw exceptions::UnexpectedSymbolException(character, std::to_string(getLine()) + ":" + std::to_string(getCol()));
	} else if (character == '/') {
		character = get();

		if (character == '/') {
			while (!eof()) {
				if (character == '\n' || character == '\r') {
					return get();
				}

				character = get();

			}

			throw exceptions::EndofFileException();
		} else if (character == '*') {
			character = get();

			while (!eof()) {
				if (character == '*') {
					character = get();

					if (character == '/') {
						return get();
					} else {
						unget();

					}
				}

				character = get();

			}

			throw exceptions::EndofFileException();
		} else {
			unget();

			return '/';
		}
	}

	return character;
}

void Reader::File::unget() {
	char result = std::ifstream::peek();

	if (result == '\n') {
		col = lastCols.top();
		lastCols.pop();
		--line;
	} else
		--col;

	std::ifstream::unget();
}

unsigned long long int Reader::File::getLine() const {
	return line;
}

unsigned long long int Reader::File::getCol() const {
	return col;
}

std::shared_ptr<RootTag> Reader::read(const std::string& filePath) {
	File file(filePath);
	std::shared_ptr<RootTag> tag = std::make_shared<RootTag>();

	{
		auto tmp = readSubTags(file, "root", true);
		tag->addChilds(tmp);
	}

	return tag;
}

std::vector<std::shared_ptr<Tag>> Reader::readSubTags(File& file, const std::string& tagName, bool root) {
	std::vector<std::shared_ptr<Tag>> tags;

	std::string content;
	bool containContent = false;
	std::shared_ptr<Tag> currentTag = std::make_shared<Tag>();
	char character = file.getNextChar();

	while (!file.eof()) {

		if (character != '\t' && character != '\n' && character != '\r' && character != ' ' && character != '<' && character != '/'
				&& character != '>') {
			containContent = true;
		}

		if (character == '<') {
			character = file.getNextChar();

			if (character == '/') {
				unsigned int pos = 0;

				while (!file.eof()) {
					character = file.getNextChar();

					if (tagName.size() == pos)
						if (character != '>')
							throw exceptions::CloseTagSymbolNotFoundException();
						else {
							if (tags.size()) {
								if (containContent)
									throw exceptions::TagContentException();
							} else if (containContent)
								tags.push_back(std::make_shared<Content>(content));

							return tags;
						}
					else if (character != *tagName.substr(pos, 1).c_str())
						throw exceptions::TagsNameMismatchException();

					++pos;
				}

				throw exceptions::EndofFileException();
			} else {
				file.unget();

				if (readTagParams(file, currentTag)) {
					auto tmp = readSubTags(file, currentTag->getName());
					currentTag->addChilds(tmp);
				}

				tags.push_back(currentTag);
				currentTag = std::make_shared<Tag>();
			}
		} else if (character == '>')
			throw exceptions::CloseTagSymbolUnexpectedException();
		else
			content += character;

		character = file.getNextChar();
	}

	if (!root)
		throw exceptions::EndofFileException();

	return tags;
}

bool Reader::isAlphaNumeric(char charactere) {
	return (charactere > 47 && charactere < 58) || (charactere > 64 && charactere < 91) || (charactere > 96 && charactere < 123)
			|| charactere == '.' || charactere == ',' || charactere == '-';
}

bool Reader::readTagParams(File& file, std::shared_ptr<Tag>& tag) {
	enum {
		TagName = 0x1,
		ParameterName = TagName << 1,
		Value = ParameterName << 1,
		inCotation = Value << 1,
		WaitForNext = inCotation << 1,
		Unknown = 0x0
	} state = TagName;

	std::string tagName = "";
	std::string paramName = "";
	std::string value = "";

	std::function<bool(char character)> escapeSequence = [](char character)->bool {
		return character == '\t' || character == ' ' || character == '/' || character == '>';
	};

	char character;
	character = file.getNextChar();

	while (!file.eof()) {
		if (!isAlphaNumeric(character))
			switch (state) {
			case WaitForNext:
				if (!escapeSequence(character))
					throw exceptions::UnexpectedSymbolException(character,
							std::to_string(file.getLine()) + ":" + std::to_string(file.getCol()));
				break;

			case Value:
				if (!escapeSequence(character) && character != '\"')
					throw exceptions::UnexpectedSymbolException(character,
							std::to_string(file.getLine()) + ":" + std::to_string(file.getCol()));
				break;

			case ParameterName:
				if (character != '=')
					throw exceptions::UnexpectedSymbolException(character,
							std::to_string(file.getLine()) + ":" + std::to_string(file.getCol()));
				break;

			case TagName:
				if (!escapeSequence(character))
					throw exceptions::UnexpectedSymbolException(character,
							std::to_string(file.getLine()) + ":" + std::to_string(file.getCol()));
				break;

			case inCotation:
				if (!escapeSequence(character) && character != '\"' && character != 0)
					throw exceptions::UnexpectedSymbolException(character,
							std::to_string(file.getLine()) + ":" + std::to_string(file.getCol()));
				break;

			case Unknown:
			default:
				std::cerr << "Error: fatal error in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
				throw std::exception();
			}

		switch (state) {
		case TagName:
			if (isAlphaNumeric(character))
				tagName += character;
			else {
				if (!tagName.size())
					throw exceptions::TagNameNotFoundException();

				state = WaitForNext;

				tag->setName(tagName);

				if (character == '/') {
					character = file.getNextChar();

					if (character != '>')
						throw exceptions::CloseTagSymbolNotFoundException();

					return false;
				} else if (character == '>')
					return true;
			}

			break;

		case ParameterName:
			if (character == '=') {
				if (!paramName.size())
					throw exceptions::ParamNameNotFoundException();

				state = Value;
			} else
				paramName += character;
			break;

		case Value:
			if (character == '\"') {
				if (value.size())
					throw exceptions::UnexpectedSymbolException(character,
							std::to_string(file.getLine()) + ":" + std::to_string(file.getCol()));
				else
					state = inCotation;
			} else if (escapeSequence(character)) {
				file.unget();

				if (!value.size())
					throw exceptions::ValueNotFoundException();

				state = WaitForNext;

				tag->addParam(paramName, value);
				paramName = "";
				value = "";
			} else
				value += character;
			break;

		case inCotation:
			if (character == '\"') {
				character = file.getNextChar();

				if (!escapeSequence(character))
					throw exceptions::UnexpectedSymbolException(character,
							std::to_string(file.getLine()) + ":" + std::to_string(file.getCol()));

				file.unget();

				if (!value.size())
					throw exceptions::ValueNotFoundException();

				state = WaitForNext;

				tag->addParam(paramName, value);
				paramName = "";
				value = "";

			} else {
				if (character == 0)
					value += '"';
				else
					value += character;
			}
			break;

		case WaitForNext:
			if (character == '/') {
				character = file.getNextChar();

				if (character != '>')
					throw exceptions::CloseTagSymbolNotFoundException();

				return false;
			} else if (character == '>') {
				return true;
			}

			if (isAlphaNumeric(character)) {
				state = ParameterName;

				file.unget();

			}

			break;

		case Unknown:
		default:
			std::cerr << "Error: fatal error in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
			throw std::exception();
		}

		character = file.getNextChar();
	}

	throw exceptions::EndofFileException();
}

//todo what exceptions
}
/* namespace xml */
} /* namespace utils */
