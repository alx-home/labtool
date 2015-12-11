/*
 * AutoModeEndException.h
 *
 *  Created on: 14 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EXCEPTION_LABELLISATION_AUTOMODEENDEXCEPTION_H_
#define SRC_EXCEPTION_LABELLISATION_AUTOMODEENDEXCEPTION_H_

#include <exception>

namespace exception {
namespace labelisation {

class AutoModeEndException: public std::exception {
public:
	AutoModeEndException();
	virtual ~AutoModeEndException();
};

} /* namespace labelisation */
} /* namespace exception */

#endif /* SRC_EXCEPTION_LABELLISATION_AUTOMODEENDEXCEPTION_H_ */
