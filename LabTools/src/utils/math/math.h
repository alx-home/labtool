/*
 * math.h
 *
 *  Created on: 13 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_MATH_MATH_H_
#define SRC_UTILS_MATH_MATH_H_

#include <string>

#define M_PI 3.14159265358979323846  /* pi */

namespace math {

constexpr double degToRad = M_PI / 180.;
constexpr double radToDeg = 180. / M_PI;

template<typename Type>
class StringManipulator {
public:
	StringManipulator() = delete;
	virtual ~StringManipulator() = delete;

	static Type convert(const std::string&);
};

template class StringManipulator<double> ;

} /* namespace math */

#endif /* SRC_UTILS_MATH_MATH_H_ */
