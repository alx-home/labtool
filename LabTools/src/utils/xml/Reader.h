/*
 * Reader.h
 *
 *  Created on: 29 déc. 2015
 *      Author: alex
 */

#ifndef SRC_UTILS_XML_READER_H_
#define SRC_UTILS_XML_READER_H_

#include <fstream>
#include <memory>
#include <stack>
#include <string>
#include <vector>
#include "tag/RootTag.h"

namespace utils {
namespace xml {

class Reader {
public:
	class File: public std::ifstream {
	public:
		File(const std::string& filePath);
		virtual ~File();

		unsigned long long int getLine() const;
		unsigned long long int getCol() const;
		char getNextChar();
		void unget();

	protected:
		unsigned long long int line = 1;
		unsigned long long int col = 0;
		std::stack<unsigned long long int> lastCols = std::stack<unsigned long long int>();

		char get();
	};

	static std::shared_ptr<RootTag> read(const std::string& path);

private:
	Reader() = delete;
	virtual ~Reader() = delete;

	static std::vector<std::shared_ptr<Tag>> readSubTags(File& file, const std::string& tagName, bool root = false);
	static bool readTagParams(File& file, std::shared_ptr<Tag>& tag);
	static bool isAlphaNumeric(char charactere);
	static char getNextChar(File& file);
};

} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_READER_H_ */
