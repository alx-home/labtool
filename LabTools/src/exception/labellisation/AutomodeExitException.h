/*
 * autoEndException.h
 *
 *  Created on: 3 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EXCEPTION_LABELLISATION_AUTOMODEEXITEXCEPTION_H_
#define SRC_EXCEPTION_LABELLISATION_AUTOMODEEXITEXCEPTION_H_

#include <exception>

namespace exception {
namespace labelisation {

class AutomodeExitException: public std::exception {
public:
	AutomodeExitException();
	virtual ~AutomodeExitException();
};

} /* namespace labellisation */
} /* namespace exception */

#endif /* SRC_EXCEPTION_LABELLISATION_AUTOMODEEXITEXCEPTION_H_ */
