/*
 * ParamNameNotFoundException.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_EXCEPTIONS_PARAMNAMENOTFOUNDEXCEPTION_H_
#define SRC_UTILS_XML_EXCEPTIONS_PARAMNAMENOTFOUNDEXCEPTION_H_

#include <exception>

namespace utils {
namespace xml {
namespace exceptions {

class ParamNameNotFoundException: public std::exception {
public:
	ParamNameNotFoundException();
	virtual ~ParamNameNotFoundException();
};

} /* namespace exceptions */
} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_EXCEPTIONS_PARAMNAMENOTFOUNDEXCEPTION_H_ */
