/*
 * EndofFileException.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_EXCEPTIONS_ENDOFFILEEXCEPTION_H_
#define SRC_UTILS_XML_EXCEPTIONS_ENDOFFILEEXCEPTION_H_

#include <exception>

namespace utils {
namespace xml {
namespace exceptions {

class EndofFileException: public std::exception {
public:
	EndofFileException();
	virtual ~EndofFileException();
};

} /* namespace exceptions */
} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_EXCEPTIONS_ENDOFFILEEXCEPTION_H_ */
