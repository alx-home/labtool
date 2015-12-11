/*
 * CloseTagSymbolException.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_EXCEPTIONS_CLOSETAGSYMBOLUNEXPECTEDEXCEPTION_H_
#define SRC_UTILS_XML_EXCEPTIONS_CLOSETAGSYMBOLUNEXPECTEDEXCEPTION_H_

#include <exception>

namespace utils {
namespace xml {
namespace exceptions {

class CloseTagSymbolUnexpectedException: public std::exception {
public:
	CloseTagSymbolUnexpectedException();
	virtual ~CloseTagSymbolUnexpectedException();
};

} /* namespace exceptions */
} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_EXCEPTIONS_CLOSETAGSYMBOLUNEXPECTEDEXCEPTION_H_ */
