/*
 * TagsNameMismatchException.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_EXCEPTIONS_TAGSNAMEMISMATCHEXCEPTION_H_
#define SRC_UTILS_XML_EXCEPTIONS_TAGSNAMEMISMATCHEXCEPTION_H_

#include <exception>

namespace utils {
namespace xml {
namespace exceptions {

class TagsNameMismatchException: public std::exception {
public:
	TagsNameMismatchException();
	virtual ~TagsNameMismatchException();
};

} /* namespace exceptions */
} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_EXCEPTIONS_TAGSNAMEMISMATCHEXCEPTION_H_ */
