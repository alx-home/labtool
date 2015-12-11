/*
 * StopDrawingCalculationException.h
 *
 *  Created on: 16 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EXCEPTION_STOPPOLLEVENTEXCEPTION_H_
#define SRC_EXCEPTION_STOPPOLLEVENTEXCEPTION_H_

#include <exception>

namespace exception {

class StopPollEventException: public std::exception {
public:
	StopPollEventException();
	virtual ~StopPollEventException();
};

} /* namespace exception */

#endif /* SRC_EXCEPTION_STOPPOLLEVENTEXCEPTION_H_ */
