/*
 * Group.cpp
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "Group.h"

namespace utils {
namespace c3d {
namespace writter {

Group::Group(const std::string& name, uint8_t entityId, const std::string& description) :
		name(name), description(description), entityId(entityId) {
}

Group::~Group() {
}

const std::string& Group::getName() const {
	return name;
}

const std::string& Group::getDescription() const {
	return description;
}

uint8_t Group::getEntityId() const {
	return entityId;
}

const std::vector<std::shared_ptr<Parameter> >& Group::getParameters() const {
	return parameters;
}

void Group::attachParameter(const std::shared_ptr<Parameter>& parameter) {
	parameters.push_back(parameter);
}

} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */
