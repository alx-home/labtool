/*
 * math.cpp
 *
 *  Created on: 25 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "math.h"

#include <exception>
#include <sstream>

namespace math {

template<typename Type>
Type StringManipulator<Type>::convert(const std::string& string) {
	std::stringstream stream(string);
	Type result;

	if (!(stream >> result))
		throw std::exception(); //todo exception

	return result;
}

} /* namespace math */
