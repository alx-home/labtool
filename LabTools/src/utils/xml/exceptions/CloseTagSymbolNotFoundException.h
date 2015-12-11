/*
 * SlashNotFollowedByGreaterSymbolException.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_EXCEPTIONS_CLOSETAGSYMBOLNOTFOUNDEXCEPTION_H_
#define SRC_UTILS_XML_EXCEPTIONS_CLOSETAGSYMBOLNOTFOUNDEXCEPTION_H_

#include <exception>

namespace utils {
namespace xml {
namespace exceptions {

class CloseTagSymbolNotFoundException: public std::exception {
public:
	CloseTagSymbolNotFoundException();
	virtual ~CloseTagSymbolNotFoundException();
};

} /* namespace exceptions */
} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_EXCEPTIONS_CLOSETAGSYMBOLNOTFOUNDEXCEPTION_H_ */
