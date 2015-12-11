/*
 * Entity.cpp
 *
 *  Created on: 30 déc. 2015
 *      Author: alex
 */

#include "Entity.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include "Group.h"
#include "Parameter.h"

namespace utils {
namespace c3d {
namespace reader {

std::shared_ptr<Entity> Entity::getNextEntity(std::ifstream& file) {
	int8_t groupNameLength, entityId;
	uint16_t nextEntityPtr;
	std::string entityName;

	file.read(&reinterpret_cast<char&>(groupNameLength), sizeof(uint8_t));
	file.read(&reinterpret_cast<char&>(entityId), sizeof(int8_t));

	entityName.resize(groupNameLength);
	file.read(const_cast<char*>(entityName.c_str()), groupNameLength);

	file.read(&reinterpret_cast<char&>(nextEntityPtr), sizeof(uint16_t));

	if (entityId < 0) {
		struct make_shared_enabler: public Group {
			make_shared_enabler(std::ifstream& file, const std::string& name, uint8_t entityId, uint16_t nextEntityPtr) :
					Group(file, name, entityId, nextEntityPtr) {
			}
		};

		return std::make_shared<make_shared_enabler>(file, entityName, entityId, nextEntityPtr);
	} else {
		return Parameter::getParameterData(file, entityName, entityId, nextEntityPtr);
	}

	return nullptr;
}

Entity::Entity(std::ifstream& file, const std::string& name, int8_t entityId, uint16_t nextEntityPtr) :
		name(name), entityId(entityId), nextEntityPtr(nextEntityPtr) {
}

Entity::~Entity() {
}

int8_t Entity::getEntityId() const {
	return entityId;
}

const std::string& Entity::getName() const {
	return name;
}

const std::string& Entity::getDescription() const {
	return description;
}

} /* namespace reader */
} /* namespace c3d */
} /* namespace utils */
