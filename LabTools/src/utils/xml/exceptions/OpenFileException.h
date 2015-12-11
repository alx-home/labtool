/*
 * OpenFileError.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_EXCEPTIONS_OPENFILEEXCEPTION_H_
#define SRC_UTILS_XML_EXCEPTIONS_OPENFILEEXCEPTION_H_

#include <exception>

namespace utils {
namespace xml {
namespace exceptions {

class OpenFileException: public std::exception {
public:
	OpenFileException();
	virtual ~OpenFileException();
};

} /* namespace exceptions */
} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_EXCEPTIONS_OPENFILEEXCEPTION_H_ */
