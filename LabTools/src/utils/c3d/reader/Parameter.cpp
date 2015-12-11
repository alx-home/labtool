/*
 * Parameter.cpp
 *
 *  Created on: 30 déc. 2015
 *      Author: alex
 */

#include "Parameter.h"

#include <exception>

#include "../../../Language/LanguageLoader.h"
#include "ParameterChild.h"

namespace utils {
namespace c3d {
namespace reader {

Parameter::Parameter(std::ifstream& file, const std::string& name, int8_t entityId, uint16_t nextEntityPtr) :
		Entity(file, name, entityId, nextEntityPtr) {
}

Parameter::~Parameter() {
}

std::shared_ptr<Parameter> Parameter::getParameterData(std::ifstream& file, const std::string& name, int8_t entityId,
		uint16_t nextEntityPtr) {
	int8_t parameterType;
	file.read(&reinterpret_cast<char&>(parameterType), sizeof(uint8_t));

	if (parameterType == -1)
		return std::make_shared<ParameterChild<Parameter::Character>>(file, name, entityId, nextEntityPtr);
	else if (parameterType == 1)
		return std::make_shared<ParameterChild<Parameter::Byte>>(file, name, entityId, nextEntityPtr);
	else if (parameterType == 2)
		return std::make_shared<ParameterChild<Parameter::Integer>>(file, name, entityId, nextEntityPtr);
	else if (parameterType == 4)
		return std::make_shared<ParameterChild<Parameter::Float>>(file, name, entityId, nextEntityPtr);
	else if (parameterType == 0)
		return nullptr;
	else {
		std::cerr << SERIALIZER->getInvalidParameterType1() << std::to_string(parameterType) << SERIALIZER->getInvalidParameterType2() << std::endl;

		throw std::exception(); //todo exception
	}
}

} /* namespace reader */
} /* namespace c3d */
} /* namespace utils */
