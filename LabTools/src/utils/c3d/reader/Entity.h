/*
 * Entity.h
 *
 *  Created on: 30 déc. 2015
 *      Author: alex
 */

#ifndef SRC_UTILS_C3D_ENTITY_H_
#define SRC_UTILS_C3D_ENTITY_H_

#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace utils {
namespace c3d {
namespace reader {

class Entity {
public:
	static std::shared_ptr<Entity> getNextEntity(std::ifstream& file);
	virtual ~Entity();

	int8_t getEntityId() const;
	const std::string& getName() const;
	const std::string& getDescription() const;

protected:
	Entity(std::ifstream& file, const std::string& name, int8_t id, uint16_t nextEntityPtr);

	std::string name = "";
	std::string description = "";
	int8_t entityId = 0;
	uint16_t nextEntityPtr = 0;
};

} /* namespace reader */
} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_ENTITY_H_ */
