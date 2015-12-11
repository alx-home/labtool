/*
 * Vector.h
 *
 *  Created on: 15 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_MATH_VECTOR_H_
#define SRC_UTILS_MATH_VECTOR_H_

#include <array>
#include <iostream>
#include <tuple>
#include <type_traits>

namespace utils {
namespace math {

template<typename Type>
class Vector2Util;
template<typename Type>
class Vector3Util;
class VectorNoUtil {
};

template<typename Type, unsigned short dim>
class Vector: public std::conditional<dim == 3, Vector3Util<Type>,
		typename std::conditional<dim == 2, Vector2Util<Type>, VectorNoUtil>::type>::type {
public:
	Vector(const std::array<Type, dim>& args);
	Vector(const Vector<Type, dim>&);
	Vector();
	virtual ~Vector();

	double getNorm() const;
	template<unsigned short dim2 = dim>
	typename std::enable_if<dim2 == 3, std::tuple<Type, Vector<Type, dim>>>::type getRotationWith(const Vector<Type, dim>&) const;
	unsigned short size() const;
	double normalize();
	Vector<Type, dim> normalized() const;
	template<typename Type2 = Type>
	typename std::enable_if<dim == 3, Vector<Type2, dim>&>::type rotate(const Vector<Type, dim>& axis, double angle);
	//Vector<Type, dim>& rotate(double angle) = delete;
	void empty();

	Type& operator[](unsigned short) const;
	Vector<Type, dim>& operator=(const Vector<Type, dim>&);
	Vector<Type, dim>& operator+=(const Vector<Type, dim>&);
	Vector<Type, dim>& operator-=(const Vector<Type, dim>&);
	Vector<Type, dim>& operator*=(const Vector<Type, dim>&) = delete;
	Vector<Type, dim>& operator*=(Type);
	Vector<Type, dim>& operator/=(Type);
	Vector<Type, dim> operator-() const;
	Vector<Type, dim> operator+() const;
	template<typename Type2 = Type>
	typename std::enable_if<dim == 3, Vector<Type2, dim>>::type operator^=(const Vector<Type, dim>& rhs);

private:
	std::array<Type, dim> coords;
};

template<typename Type>
class Vector3Util {
public:
	static const Vector<Type, 3> xAxis;
	static const Vector<Type, 3> yAxis;
	static const Vector<Type, 3> zAxis;
	static const Vector<Type, 3> center;

	Vector3Util();
	virtual ~Vector3Util();
};

template<typename Type>
class Vector2Util {
public:
	static const Vector<Type, 2> xAxis;
	static const Vector<Type, 2> yAxis;
	static const Vector<Type, 2> center;

	Vector2Util();
	virtual ~Vector2Util();
};

template<typename Type, unsigned short dim>
Type operator*(const Vector<Type, dim>& lhs, const Vector<Type, dim>& rhs);

template<typename Type, unsigned short dim>
Vector<Type, dim> operator/(const Vector<Type, dim>& lhs, Type rhs);

template<typename Type, unsigned short dim>
Vector<Type, dim> operator*(const Vector<Type, dim>& lhs, Type rhs);

template<typename Type, unsigned short dim>
Vector<Type, dim> operator*(Type lhs, const Vector<Type, dim>& rhs);

template<typename Type>
Vector<Type, 3> operator^(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs);

template<typename Type, unsigned short dim>
Vector<Type, dim> operator+(const Vector<Type, dim>& lhs, const Vector<Type, dim>& rhs);

template<typename Type, unsigned short dim>
Vector<Type, dim> operator-(const Vector<Type, dim>& lhs, const Vector<Type, dim>& rhs);

template<typename Type, unsigned short dim>
bool operator==(const Vector<Type, dim>& lhs, const Vector<Type, dim>& rhs);

template<typename Type, unsigned short dim>
bool operator!=(const Vector<Type, dim>& lhs, const Vector<Type, dim>& rhs);

template<typename Type, unsigned short dim>
std::ostream& operator<<(std::ostream& stream, const Vector<Type, dim>& rhs);

}/* namespace math */
} /* namespace utils */

using Vector2d = class utils::math::Vector<double, 2>;
using Vector3d = class utils::math::Vector<double, 3>;
using Vector2f = class utils::math::Vector<float, 2>;
using Vector3f = class utils::math::Vector<float, 3>;
#endif /* SRC_UTILS_MATH_VECTOR_H_ */
