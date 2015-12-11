/*
 * TagNameNotFoundException.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_EXCEPTIONS_TAGNAMENOTFOUNDEXCEPTION_H_
#define SRC_UTILS_XML_EXCEPTIONS_TAGNAMENOTFOUNDEXCEPTION_H_

#include <exception>

namespace utils {
namespace xml {
namespace exceptions {

class TagNameNotFoundException: public std::exception {
public:
	TagNameNotFoundException();
	virtual ~TagNameNotFoundException();
};

} /* namespace exceptions */
} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_EXCEPTIONS_TAGNAMENOTFOUNDEXCEPTION_H_ */
