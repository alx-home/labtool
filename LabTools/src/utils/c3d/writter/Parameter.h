/*
 * Parameter.h
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_C3D_WRITTER_PARAMETER_H_
#define SRC_UTILS_C3D_WRITTER_PARAMETER_H_

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

namespace utils {
namespace c3d {
namespace writter {
class Group;
} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */

namespace utils {
namespace c3d {
namespace writter {

class Parameter {
public:
	virtual ~Parameter();

	virtual void writeData(std::ofstream& file) const = 0;
	virtual uint16_t getSize() const = 0;
	const std::string& getDescription() const;
	uint8_t getEntityId() const;
	const std::string& getName() const;

protected:
	std::string name;
	std::string description;
	uint8_t entityId;

	Parameter(std::string name, uint8_t entityId, std::string description);

	static void attachChildToParent(const std::shared_ptr<Parameter>& child, Group& parent);
};

} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_WRITTER_PARAMETER_H_ */
