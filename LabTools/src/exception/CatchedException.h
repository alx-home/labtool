/*
 * CatchedException.h
 *
 *  Created on: 16 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EXCEPTION_CATCHEDEXCEPTION_H_
#define SRC_EXCEPTION_CATCHEDEXCEPTION_H_

#include <exception>

namespace exception {

class CatchedException: public std::exception {
public:
	CatchedException();
	virtual ~CatchedException();
};

} /* namespace exception */

#endif /* SRC_EXCEPTION_CATCHEDEXCEPTION_H_ */
