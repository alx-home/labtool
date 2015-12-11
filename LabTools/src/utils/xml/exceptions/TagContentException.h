/*
 * TagContentException.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_EXCEPTIONS_TAGCONTENTEXCEPTION_H_
#define SRC_UTILS_XML_EXCEPTIONS_TAGCONTENTEXCEPTION_H_

#include <exception>

namespace utils {
namespace xml {
namespace exceptions {

class TagContentException: public std::exception {
public:
	TagContentException();
	virtual ~TagContentException();
};

} /* namespace exceptions */
} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_EXCEPTIONS_TAGCONTENTEXCEPTION_H_ */
