/*
 * UnexpectedSymbolException.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_EXCEPTIONS_UNEXPECTEDSYMBOLEXCEPTION_H_
#define SRC_UTILS_XML_EXCEPTIONS_UNEXPECTEDSYMBOLEXCEPTION_H_

#include <cstddef>
#include <exception>
#include <string>

namespace utils {
namespace xml {
namespace exceptions {

class UnexpectedSymbolException: public std::exception {
public:
	UnexpectedSymbolException(char symbol, const std::string& line);
	virtual ~UnexpectedSymbolException();

	const char* what() const _GLIBCXX_USE_NOEXCEPT override;

private:
	char symbol;
	std::string line;
};

} /* namespace exceptions */
} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_EXCEPTIONS_UNEXPECTEDSYMBOLEXCEPTION_H_ */
