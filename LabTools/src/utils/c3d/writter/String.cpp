/*
 * String.cpp
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "String.h"

#include "Group.h"

namespace utils {
namespace c3d {
namespace writter {

void String::writeData(std::ofstream& file) const {
	uint8_t type = -1;
	file.write(&reinterpret_cast<char&>(type), sizeof(uint8_t));
	uint8_t buff = 2;

	if (values.size() > 1) {
		file.write(&reinterpret_cast<char&>(buff), sizeof(uint8_t));
		buff = stringSize;
		file.write(&reinterpret_cast<char&>(buff), sizeof(uint8_t));
		buff = values.size();
		file.write(&reinterpret_cast<char&>(buff), sizeof(uint8_t));
	} else {
		buff = 1;
		file.write(&reinterpret_cast<char&>(buff), sizeof(uint8_t));
		buff = stringSize;
		file.write(&reinterpret_cast<char&>(buff), sizeof(uint8_t));
	}

	for (auto& value : values) {
		std::string text = value;

		for (unsigned int i = text.size(); i < stringSize; ++i)
			text += " ";

		file.write(text.c_str(), stringSize);
	}
}

uint16_t String::getSize() const {
	return values.size() * stringSize + 5 + (values.size() > 1 ? 2 : 1) + description.size();
}

std::shared_ptr<Parameter> String::getParameter(const std::string& name, const std::string& value, unsigned short stringSize, Group& parent,
		const std::string& description) {
	std::vector<std::string> values;

	values.push_back(value);

	return getParameter(name, values, stringSize, parent, description);
}

std::shared_ptr<Parameter> String::getParameter(const std::string& name, const std::vector<std::string>& values, unsigned short stringSize,
		Group& parent, const std::string& description) {
	class make_shared_enabler: public String {
	public:
		make_shared_enabler(const std::string& name, const std::vector<std::string>& values, unsigned short stringSize, Group& parent,
				const std::string& description) :
				String(name, values, stringSize, parent, description) {
		}
		virtual ~make_shared_enabler() {
		}
	};

	auto result = std::make_shared<make_shared_enabler>(name, values, stringSize, parent, description);

	attachChildToParent(result, parent);

	return result;
}

String::String(const std::string& name, const std::vector<std::string>& values, unsigned short stringSize, Group& parent,
		const std::string& description) :
		Parameter(name, parent.getEntityId(), description), values(values), stringSize(stringSize) {
}

String::~String() {
}

} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */
