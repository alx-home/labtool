/*
 * Vector.cxx
 *
 *  Created on: 17 janv. 2016
 *      Author: alex
 */

#ifndef SRC_UTILS_MATH_VECTOR_CXX_
#define SRC_UTILS_MATH_VECTOR_CXX_

#include "Vector.h"

namespace utils {
namespace math {

template class Vector<double, 3> ;

template double operator*(const Vector<double, 3>& lhs, const Vector<double, 3>& rhs);
template Vector<double, 3> operator*(const Vector<double, 3>& lhs, double rhs);
template Vector<double, 3> operator*(double lhs, const Vector<double, 3>& rhs);
template Vector<double, 3> operator/(const Vector<double, 3>& lhs, double rhs);
template Vector<double, 3> operator+(const Vector<double, 3>& lhs, const Vector<double, 3>& rhs);
template Vector<double, 3> operator-(const Vector<double, 3>& lhs, const Vector<double, 3>& rhs);
template bool operator==(const Vector<double, 3>& lhs, const Vector<double, 3>& rhs);
template bool operator!=(const Vector<double, 3>& lhs, const Vector<double, 3>& rhs);
template std::ostream& operator<<(std::ostream& lhs, const Vector<double, 3>& rhs);
template class Vector<double, 2> ;

template double operator*(const Vector<double, 2>& lhs, const Vector<double, 2>& rhs);
template Vector<double, 2> operator*(const Vector<double, 2>& lhs, double rhs);
template Vector<double, 2> operator*(double lhs, const Vector<double, 2>& rhs);
template Vector<double, 2> operator/(const Vector<double, 2>& lhs, double rhs);
template Vector<double, 2> operator+(const Vector<double, 2>& lhs, const Vector<double, 2>& rhs);
template Vector<double, 2> operator-(const Vector<double, 2>& lhs, const Vector<double, 2>& rhs);
template bool operator==(const Vector<double, 2>& lhs, const Vector<double, 2>& rhs);
template bool operator!=(const Vector<double, 2>& lhs, const Vector<double, 2>& rhs);
template std::ostream& operator<<(std::ostream& lhs, const Vector<double, 2>& rhs);
template Vector<double, 3> operator^(const Vector<double, 3>& lhs, const Vector<double, 3>& rhs);
template typename std::enable_if<true, Vector<double, 3>&>::type Vector<double, 3>::rotate(const Vector<double, 3>&, double);
template typename std::enable_if<true, std::tuple<double, Vector<double, 3>>>::type Vector<double, 3>::getRotationWith(const Vector<double, 3>&) const;

template class Vector<float, 3> ;

template float operator*(const Vector<float, 3>& lhs, const Vector<float, 3>& rhs);
template Vector<float, 3> operator*(const Vector<float, 3>& lhs, float rhs);
template Vector<float, 3> operator*(float lhs, const Vector<float, 3>& rhs);
template Vector<float, 3> operator/(const Vector<float, 3>& lhs, float rhs);
template Vector<float, 3> operator+(const Vector<float, 3>& lhs, const Vector<float, 3>& rhs);
template Vector<float, 3> operator-(const Vector<float, 3>& lhs, const Vector<float, 3>& rhs);
template bool operator==(const Vector<float, 3>& lhs, const Vector<float, 3>& rhs);
template bool operator!=(const Vector<float, 3>& lhs, const Vector<float, 3>& rhs);
template std::ostream& operator<<(std::ostream& lhs, const Vector<float, 3>& rhs);
template class Vector<float, 2> ;

template float operator*(const Vector<float, 2>& lhs, const Vector<float, 2>& rhs);
template Vector<float, 2> operator*(const Vector<float, 2>& lhs, float rhs);
template Vector<float, 2> operator*(float lhs, const Vector<float, 2>& rhs);
template Vector<float, 2> operator/(const Vector<float, 2>& lhs, float rhs);
template Vector<float, 2> operator+(const Vector<float, 2>& lhs, const Vector<float, 2>& rhs);
template Vector<float, 2> operator-(const Vector<float, 2>& lhs, const Vector<float, 2>& rhs);
template bool operator==(const Vector<float, 2>& lhs, const Vector<float, 2>& rhs);
template bool operator!=(const Vector<float, 2>& lhs, const Vector<float, 2>& rhs);
template std::ostream& operator<<(std::ostream& lhs, const Vector<float, 2>& rhs);
template Vector<float, 3> operator^(const Vector<float, 3>& lhs, const Vector<float, 3>& rhs);
template typename std::enable_if<true, Vector<float, 3>&>::type Vector<float, 3>::rotate(const Vector<float, 3>&, double);
template typename std::enable_if<true, std::tuple<float, Vector<float, 3>>>::type Vector<float, 3>::getRotationWith(const Vector<float, 3>&) const;

template<>
Vector3d const Vector3Util<double>::xAxis = Vector3d( { 1.0, 0.0, 0.0 });
template<>
Vector3d const Vector3Util<double>::yAxis = Vector3d( { 0.0, 1.0, 0.0 });
template<>
Vector3d const Vector3Util<double>::zAxis = Vector3d( { 0.0, 0.0, 1.0 });
template<>
Vector3d const Vector3Util<double>::center = Vector3d( { 0.0, 0.0, 0.0 });

template<>
Vector3f const Vector3Util<float>::xAxis = Vector3f( { 1.0, 0.0, 0.0 });
template<>
Vector3f const Vector3Util<float>::yAxis = Vector3f( { 0.0, 1.0, 0.0 });
template<>
Vector3f const Vector3Util<float>::zAxis = Vector3f( { 0.0, 0.0, 1.0 });
template<>
Vector3f const Vector3Util<float>::center = Vector3f( { 0.0, 0.0, 0.0 });

template<>
Vector2d const Vector2Util<double>::xAxis = Vector2d( { 1.0, 0.0 });
template<>
Vector2d const Vector2Util<double>::yAxis = Vector2d( { 0.0, 1.0 });
template<>
Vector2d const Vector2Util<double>::center = Vector2d( { 0.0, 0.0 });

template<>
Vector2f const Vector2Util<float>::xAxis = Vector2f( { 1.0, 0.0 });
template<>
Vector2f const Vector2Util<float>::yAxis = Vector2f( { 0.0, 1.0 });
template<>
Vector2f const Vector2Util<float>::center = Vector2f( { 0.0, 0.0 });
}
/* namespace math */
} /* namespace utils */

#endif /* SRC_UTILS_MATH_VECTOR_CXX_ */
