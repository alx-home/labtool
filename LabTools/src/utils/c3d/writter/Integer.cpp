/*
 * Integer.cpp
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "Integer.h"

#include "Group.h"

namespace utils {
namespace c3d {
namespace writter {

void Integer::writeData(std::ofstream& file) const {
	uint8_t type = 2;
	file.write(&reinterpret_cast<char&>(type), sizeof(uint8_t));
	type = 0;
	file.write(&reinterpret_cast<char&>(type), sizeof(uint8_t));
	file.write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
}

uint16_t Integer::getSize() const {
	return 0x7 + description.size();
}

std::shared_ptr<Parameter> Integer::getParameter(const std::string& name, uint16_t value, Group& parent, const std::string& description) {
	class make_shared_enabler: public Integer {
	public:
		make_shared_enabler(const std::string& name, uint16_t value, Group& parent, const std::string& description) :
				Integer(name, value, parent, description) {
		}
		virtual ~make_shared_enabler() {
		}
	};

	auto result = std::make_shared<make_shared_enabler>(name, value, parent, description);

	attachChildToParent(result, parent);

	return result;
}

Integer::Integer(const std::string& name, uint16_t value, Group& parent, const std::string& description) :
		Parameter(name, parent.getEntityId(), description), value(value) {
}

Integer::~Integer() {
}

} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */
