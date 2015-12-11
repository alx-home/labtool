/*
 * Group.h
 *
 *  Created on: 30 déc. 2015
 *      Author: alex
 */

#ifndef SRC_UTILS_C3D_GROUP_H_
#define SRC_UTILS_C3D_GROUP_H_

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "Entity.h"
#include "Parameter.h"

namespace utils {
namespace c3d {
namespace reader {

class Group: public Entity {
public:
	virtual ~Group();

	void attachParameter(const std::shared_ptr<Parameter>& parameter);
	std::shared_ptr<Parameter> getParameter (const std::string& name) const;
	const std::unordered_map<std::string, std::shared_ptr<Parameter>>& getParameters () const;

protected:
	std::unordered_map<std::string, std::shared_ptr<Parameter>> parameters = std::unordered_map<std::string, std::shared_ptr<Parameter>>();

	Group(std::ifstream& file, const std::string& name, int8_t entityId, uint16_t nextEntityPtr);
};

} /* namespace reader */
} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_GROUP_H_ */
