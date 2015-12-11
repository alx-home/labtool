/*
 * EmptyLabelDrawerFunctionException.h
 *
 *  Created on: 18 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TYPES_POINT_EXCEPTION_EMPTYLABELDRAWERFUNCTIONEXCEPTION_H_
#define SRC_TYPES_POINT_EXCEPTION_EMPTYLABELDRAWERFUNCTIONEXCEPTION_H_

#include <exception>

namespace exception {

class EmptyLabelDrawerFunctionException: public std::exception {
public:
	EmptyLabelDrawerFunctionException();
	virtual ~EmptyLabelDrawerFunctionException();
};

} /* namespace exception */

#endif /* SRC_TYPES_POINT_EXCEPTION_EMPTYLABELDRAWERFUNCTIONEXCEPTION_H_ */
