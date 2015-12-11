/*
 * Float.cpp
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "Float.h"

#include "Group.h"

namespace utils {
namespace c3d {
namespace writter {

void Float::writeData(std::ofstream& file) const {
	uint8_t type = 4;
	file.write(&reinterpret_cast<char&>(type), sizeof(uint8_t));
	type = 0;
	file.write(&reinterpret_cast<char&>(type), sizeof(uint8_t));
	file.write(&reinterpret_cast<const char&>(value), sizeof(uint32_t));
}

uint16_t Float::getSize() const {
	return 0x9 + description.size();
}

std::shared_ptr<Parameter> Float::getParameter(const std::string& name, float value, Group& parent, const std::string& description) {
	class make_shared_enabler: public Float {
	public:
		make_shared_enabler(const std::string& name, float value, Group& parent, const std::string& description) :
			Float(name, value, parent, description) {
		}
		virtual ~make_shared_enabler() {
		}
	};

	auto result = std::make_shared<make_shared_enabler>(name, value, parent, description);

	attachChildToParent(result, parent);

	return result;
}

Float::Float(const std::string& name, float value, Group& parent, const std::string& description) :
		Parameter(name, parent.getEntityId(), description), value(value) {
}

Float::~Float() {
}

} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */
