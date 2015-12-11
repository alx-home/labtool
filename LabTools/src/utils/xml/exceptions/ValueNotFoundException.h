/*
 * ValueNotFoundException.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_EXCEPTIONS_VALUENOTFOUNDEXCEPTION_H_
#define SRC_UTILS_XML_EXCEPTIONS_VALUENOTFOUNDEXCEPTION_H_

#include <exception>

namespace utils {
namespace xml {
namespace exceptions {

class ValueNotFoundException: public std::exception {
public:
	ValueNotFoundException();
	virtual ~ValueNotFoundException();
};

} /* namespace exceptions */
}
/* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_EXCEPTIONS_VALUENOTFOUNDEXCEPTION_H_ */
