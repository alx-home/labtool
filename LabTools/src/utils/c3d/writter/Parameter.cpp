/*
 * Parameter.cpp
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "Parameter.h"

#include "Group.h"

namespace utils {
namespace c3d {
namespace writter {

Parameter::Parameter(std::string name, uint8_t entityId, std::string description) :
		name(name), entityId(entityId), description(description) {
}

Parameter::~Parameter() {
}

const std::string& Parameter::getDescription() const {
	return description;
}

uint8_t Parameter::getEntityId() const {
	return entityId;
}

const std::string& Parameter::getName() const {
	return name;
}

void Parameter::attachChildToParent(const std::shared_ptr<Parameter>& child, Group& parent) {
	parent.attachParameter(child);
}

} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */
