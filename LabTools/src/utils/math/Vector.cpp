/*
 * Vector.cpp
 *
 *  Created on: 15 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "Vector.h"

#include <cmath>
#include <string>

namespace utils {
namespace math {

template<typename Type, unsigned short dim>
Vector<Type, dim>::Vector() :
		coords() {
	empty();
}

template<typename Type, unsigned short dim>
Vector<Type, dim>::Vector(const std::array<Type, dim>& args) :
		coords(args) {
}

template<typename Type, unsigned short dim>
Vector<Type, dim>::Vector(const Vector<Type, dim>& vec) :
		coords() {
	*this = vec;
}

template<typename Type, unsigned short dim>
Vector<Type, dim>::~Vector() {
}

template<typename Type, unsigned short dim>
double Vector<Type, dim>::getNorm() const {
	double result = 0;

	for (Type coord : coords)
		result += pow(coord, 2);

	return sqrt(result);
}

template<typename Type, unsigned short dim>
template<unsigned short dim2>
typename std::enable_if<dim2 == 3, std::tuple<Type, Vector<Type, dim>>>::type Vector<Type, dim>::getRotationWith(const Vector<Type, dim>& vec) const {
	Vector<Type, dim> y = vec;
	y.normalize();
	Vector<Type, dim> x = *this;
	x.normalize();

	if (y == x)
	return std::tuple<Type, Vector<Type, dim>> {0, *this};

	Vector<Type, dim> axis = (y ^ x).normalized();
	x = axis ^ y;

	return std::tuple<Type, Vector<Type, dim>> {atan2((*this) * x, (*this) * y), axis};
}

template<typename Type, unsigned short dim>
double Vector<Type, dim>::normalize() {
	double norm = 0;

	for (Type coord : coords)
		norm += pow(coord, 2);

	norm = sqrt(norm);

	*this /= norm;

	return norm;
}

template<typename Type, unsigned short dim>
Vector<Type, dim> Vector<Type, dim>::normalized() const {
	double norm = 0;

	for (Type coord : coords)
		norm += pow(coord, 2);

	norm = sqrt(norm);

	return *this / (Type) norm;
}

template<typename Type, unsigned short dim>
unsigned short Vector<Type, dim>::size() const {
	return dim;
}

template<typename Type, unsigned short dim>
void Vector<Type, dim>::empty() {
	for (Type& coord : coords)
		coord = 0;
}

template<typename Type, unsigned short dim>
Type& Vector<Type, dim>::operator[](unsigned short rhs) const {
	return const_cast<std::array<Type, dim>&>(coords)[rhs];
}

template<typename Type, unsigned short dim>
Vector<Type, dim>& Vector<Type, dim>::operator=(const Vector<Type, dim>& rhs) {
	this->coords = rhs.coords;

	return *this;
}

template<typename Type, unsigned short dim>
Vector<Type, dim>& Vector<Type, dim>::operator+=(const Vector<Type, dim>& rhs) {
	for (unsigned int i = 0; i < dim; ++i)
		this->coords[i] += rhs.coords[i];

	return *this;
}

template<typename Type, unsigned short dim>
Vector<Type, dim>& Vector<Type, dim>::operator*=(Type rhs) {
	for (unsigned int i = 0; i < dim; ++i)
		this->coords[i] *= rhs;

	return *this;
}

template<typename Type, unsigned short dim>
Vector<Type, dim>& Vector<Type, dim>::operator/=(Type rhs) {
	for (unsigned int i = 0; i < dim; ++i)
		this->coords[i] /= rhs;

	return *this;
}

template<typename Type, unsigned short dim>
Vector<Type, dim>& Vector<Type, dim>::operator-=(const Vector<Type, dim>& rhs) {
	for (unsigned int i = 0; i < dim; ++i)
		this->coords[i] -= rhs.coords[i];

	return *this;
}

template<typename Type, unsigned short dim>
Vector<Type, dim> Vector<Type, dim>::operator-() const {
	Vector<Type, dim> result;

	for (unsigned int i = 0; i < dim; ++i)
		result[i] = -this->coords[i];

	return result;
}

template<typename Type, unsigned short dim>
Vector<Type, dim> Vector<Type, dim>::operator+() const {
	Vector<Type, dim> result;

	for (unsigned int i = 0; i < dim; ++i)
		result[i] = this->coords[i];

	return result;
}

template<typename Type, unsigned short dim>
template<typename Type2>
typename std::enable_if<dim == 3, Vector<Type2, dim>>::type Vector<Type, dim>::operator^=(const Vector<Type, dim>& rhs) {
	*this = *this ^ rhs;

	return *this;
}

template<typename Type, unsigned short dim>
template<typename Type2>
typename std::enable_if<dim == 3, Vector<Type2, dim>&>::type Vector<Type, dim>::rotate(const Vector<Type, dim>& axisDir, double angle) {
	if (angle == 0)
		return *this;

	double c = cos(angle);
	double s = sin(angle);

	Vector<Type, dim> axis = axisDir;
	axis.normalize();
	Type xCoord = coords[0];
	Type yCoord = coords[1];
	Type zCoord = coords[2];

	coords[0] = (pow(axis[0], 2) * (1.0 - c) + c) * xCoord + (axis[0] * axis[1] * (1.0 - c) - axis[2] * s) * yCoord
			+ (axis[2] * axis[0] * (1.0 - c) + axis[1] * s) * zCoord;
	coords[1] = (axis[0] * axis[1.0] * (1.0 - c) + axis[2] * s) * xCoord + (pow(axis[1], 2) * (1.0 - c) + c) * yCoord
			+ (axis[1] * axis[2] * (1.0 - c) - axis[0] * s) * zCoord;
	coords[2] = (axis[0] * axis[2] * (1.0 - c) - axis[1] * s) * xCoord + (axis[1] * axis[2] * (1.0 - c) + axis[0] * s) * yCoord
			+ (pow(axis[2], 2) * (1.0 - c) + c) * zCoord;

	return *this;
}

template<typename Type, unsigned short dim>
Type operator*(const Vector<Type, dim>& lhs, const Vector<Type, dim>& rhs) {
	Type result = 0;

	for (unsigned int i = 0; i < dim; ++i)
		result += rhs[i] * lhs[i];

	return result;
}

template<typename Type, unsigned short dim>
Vector<Type, dim> operator*(const Vector<Type, dim>& lhs, Type rhs) {
	Vector<Type, dim> result;

	for (unsigned int i = 0; i < dim; ++i)
		result[i] = lhs[i] * rhs;

	return result;
}

template<typename Type, unsigned short dim>
Vector<Type, dim> operator*(Type lhs, const Vector<Type, dim>& rhs) {
	Vector<Type, dim> result;

	for (unsigned int i = 0; i < dim; ++i)
		result[i] = rhs[i] * lhs;

	return result;
}

template<typename Type, unsigned short dim>
Vector<Type, dim> operator/(const Vector<Type, dim>& lhs, Type rhs) {
	Vector<Type, dim> result;

	for (unsigned int i = 0; i < dim; ++i)
		result[i] = lhs[i] / rhs;

	return result;
}

template<typename Type>
Vector<Type, 3> operator^(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) {
	Vector<Type, 3> result;

	result[0] = rhs[1] * lhs[2] - rhs[2] * lhs[1];
	result[1] = rhs[2] * lhs[0] - rhs[0] * lhs[2];
	result[2] = rhs[0] * lhs[1] - rhs[1] * lhs[0];

	return result;
}

template<typename Type, unsigned short dim>
Vector<Type, dim> operator+(const Vector<Type, dim>& lhs, const Vector<Type, dim>& rhs) {
	Vector<Type, dim> result;

	for (unsigned int i = 0; i < dim; ++i)
		result[i] = rhs[i] + lhs[i];

	return result;
}

template<typename Type, unsigned short dim>
Vector<Type, dim> operator-(const Vector<Type, dim>& lhs, const Vector<Type, dim>& rhs) {
	Vector<Type, dim> result;

	for (unsigned int i = 0; i < dim; ++i)
		result[i] = lhs[i] - rhs[i];

	return result;
}

template<typename Type, unsigned short dim>
bool operator==(const Vector<Type, dim>& lhs, const Vector<Type, dim>& rhs) {
	for (unsigned int i = 0; i < dim; ++i)
		if (std::fabs(rhs[i] - lhs[i]) > 0.00001)
			return false;

	return true;
}

template<typename Type, unsigned short dim>
bool operator!=(const Vector<Type, dim>& lhs, const Vector<Type, dim>& rhs) {
	return !(rhs == lhs);
}

template<typename Type, unsigned short dim>
std::ostream& operator<<(std::ostream& stream, const Vector<Type, dim>& rhs) {
	stream << std::string("{");

	for (unsigned int i = 0; i < dim; ++i)
		if (i == dim - 1)
			stream << std::to_string(rhs[i]);
		else
			stream << std::to_string(rhs[i]) + ", ";

	stream << std::string("}");

	return stream;
}

template<typename Type>
Vector3Util<Type>::Vector3Util() {
}

template<typename Type>
Vector3Util<Type>::~Vector3Util() {
}

template<typename Type>
Vector2Util<Type>::Vector2Util() {
}

template<typename Type>
Vector2Util<Type>::~Vector2Util() {
}

}
/* namespace math */
} /* namespace utils */

#include "Vector.cxx"
