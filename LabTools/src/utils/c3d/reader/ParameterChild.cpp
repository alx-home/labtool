/*
 * Parameter.cpp
 *
 *  Created on: 30 déc. 2015
 *      Author: alex
 */

#include "ParameterChild.h"

#include <regex>
#include <stdint.h>

#include "../../../Language/LanguageLoader.h"

namespace utils {
namespace c3d {
namespace reader {

template class ParameterChild<Parameter::Character> ;
template class ParameterChild<Parameter::Float> ;
template class ParameterChild<Parameter::Integer> ;
template class ParameterChild<Parameter::Byte> ;

template<>
std::string ParameterChild<Parameter::Character>::typeName = SERIALIZER->getCharacterType();
template<>
std::string ParameterChild<Parameter::Float>::typeName = SERIALIZER->getFloatType();
template<>
std::string ParameterChild<Parameter::Integer>::typeName = SERIALIZER->getIntegerType();
template<>
std::string ParameterChild<Parameter::Byte>::typeName = SERIALIZER->getByteType();

template<typename Type_>
ParameterChild<Type_>::ParameterChild(std::ifstream& file, const std::string& name, int8_t entityId, uint16_t nextEntityPtr) :
		Parameter(file, name, entityId, nextEntityPtr) {
	uint8_t nbDims;
	std::vector<uint8_t> dims;

	file.read(&reinterpret_cast<char&>(nbDims), sizeof(uint8_t));

	for (uint8_t i = 0; i < nbDims; ++i) {
		uint8_t dim;
		file.read(&reinterpret_cast<char&>(dim), sizeof(uint8_t));

		dims.push_back(dim);
	}

	readData(file, dims);

	uint8_t parameterDescriptionSize;
	file.read(&reinterpret_cast<char&>(parameterDescriptionSize), sizeof(uint8_t));

	if (parameterDescriptionSize > 0) {
		description.resize(parameterDescriptionSize);
		file.read(const_cast<char*>(description.c_str()), parameterDescriptionSize);
	}

#ifdef c3dReaderDebug
	std::cout << "Parameter <" << name << ">[" << std::to_string(entityId) << "]"
	<< (description.size() != 0 ? "(" + description + ")" : "") << " : " << "<" << typeName << ">["
	<< (dims.size() != 0 && dims[1] > 1 ? "\n" : "");

	bool firstFlag = false;

	for (const auto& dataIt : datas) {
		bool virguleFlag = false;

		for (const auto& data : dataIt) {
			if (virguleFlag)
			std::cout << ", ";
			else if (dims.size() != 0 && dims[1] > 1 && firstFlag)
			std::cout << ";\n";

			std::cout << data.toString();

			virguleFlag = true;
			firstFlag = true;
		}
	}

	std::cout << (dims.size() != 0 && dims[1] > 1 ? "\n]" : "]") << std::endl;
#endif
}

template<typename Type_>
void ParameterChild<Type_>::readData(std::ifstream& file, const std::vector<uint8_t>& dims) {
	if (dims.size() == 0) {
		Type_ data;

		file.read(&reinterpret_cast<char&>(data.value), sizeof(data.value));

		datas.resize(1);
		datas[0].push_back(data);

		return;
	}

	datas.resize(dims.size());

	for (uint8_t i = 0; i < dims.size(); ++i) {
		uint8_t dim = dims[i];

		datas[i].resize(dim);

		for (uint8_t j = 0; j < dim; ++j) {
			Type_ data;

			file.read(&reinterpret_cast<char&>(data.value), sizeof(data.value));

			datas[i].push_back(data);
		}
	}
}

template<>
void ParameterChild<Parameter::Character>::readData(std::ifstream& file, const std::vector<uint8_t>& dims) {
	if (dims.size() > 2 || dims.size() == 0) {
		std::cerr << "Error: ill-formed character parameter in c3d file" << std::endl;

		throw std::exception(); // todo exception
	}

	if (dims.size() == 1)
		const_cast<std::vector<uint8_t>&>(dims).push_back(1);

	datas.resize(dims[1]);

	for (uint8_t i = 0; i < dims[1]; ++i) {
		Parameter::Character data;
		data.value.resize(dims[0]);

		file.read(const_cast<char*>(data.value.c_str()), dims[0]);

		std::regex e("(.*[^ ]) *");

		data.value = std::regex_replace(data.value, e, "$1");

		datas[i].push_back(data);
	}
}

template<typename Type_>
ParameterChild<Type_>::~ParameterChild() {
}

template<typename Type_>
Type_ ParameterChild<Type_>::getData(unsigned int i, unsigned int j) const {
	if (i > datas.size() || j > datas[i].size()) {
		std::cerr << SERIALIZER->getParameterChildOverflowException1() << __FILE__ <<
		SERIALIZER->getParameterChildOverflowException2() << __LINE__ <<
		SERIALIZER->getParameterChildOverflowException3() << std::to_string(datas.size()) <<
		"," << std::to_string(datas[0].size()) <<
		SERIALIZER->getParameterChildOverflowException4() << i << "," << j << ")." << std::endl;
		throw std::exception(); //todo exception
	}

	return datas[i][j];
}

template<typename Type_>
unsigned int ParameterChild<Type_>::getRows() const {
	return datas.size();
}

template<typename Type_>
unsigned int ParameterChild<Type_>::getCols() const {
	return datas[0].size();
}

template<typename Type_>
std::string ParameterChild<Type_>::toString() {
	std::string result;

	unsigned int i = 0;
	unsigned int j = 0;

	for (const auto& dataIt : datas) {
		for (const auto& data : dataIt) {
			++i;

			result += data.toString();

			if (i != dataIt.size() && dataIt.size() > 1)
				result += ";";
		}

		++j;

		if (j != datas.size() && datas.size() > 1)
			result += ",";
	}

	return result;
}

template<typename Type_>
const std::string& ParameterChild<Type_>::getTypeName() {
	return typeName;
}

} /* namespace reader */
} /* namespace c3d */
} /* namespace utils */
