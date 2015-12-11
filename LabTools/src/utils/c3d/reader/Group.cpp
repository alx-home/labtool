/*
 * Group.cpp
 *
 *  Created on: 30 déc. 2015
 *      Author: alex
 */

#include "Group.h"

#include <cstdint>
#include <iostream>
#include <string>

namespace utils {
namespace c3d {
namespace reader {

Group::Group(std::ifstream& file, const std::string& name, int8_t entityId, uint16_t nextEntityPtr) :
		Entity(file, name, -entityId, nextEntityPtr) {
	uint8_t groupDescriptionSize;
	file.read(&reinterpret_cast<char&>(groupDescriptionSize), sizeof(uint8_t));

	description = "";

	if (groupDescriptionSize > 0) {
		description.resize(groupDescriptionSize);
		file.read(const_cast<char*>(description.c_str()), groupDescriptionSize);
		description = "(" + description + ")";
	}

#ifdef c3dReaderDebug
	std::cout << "Group <" << name << ">[" << std::to_string(-entityId) << "]" << description << std::endl;
#endif

	//file.seekg(nextEntityPtr - groupDescriptionSize - 3, file.cur);
}

Group::~Group() {
}

void Group::attachParameter(const std::shared_ptr<Parameter>& parameter) {
	parameters[parameter->getName()] = parameter;
}

std::shared_ptr<Parameter> Group::getParameter(const std::string& name) const {
	const auto& it = parameters.find(name);
	if (it == parameters.end())
		return nullptr;

	return it->second;
}

const std::unordered_map<std::string, std::shared_ptr<Parameter>>& Group::getParameters() const {
	return parameters;
}

} /* namespace reader */
} /* namespace c3d */
} /* namespace utils */
