/*
 * String.h
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_C3D_WRITTER_STRING_H_
#define SRC_UTILS_C3D_WRITTER_STRING_H_

#include <cstdint>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "Parameter.h"

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

class String: public Parameter {
public:
	virtual ~String();

	void writeData(std::ofstream& file) const override;
	uint16_t getSize() const override;
	static std::shared_ptr<Parameter> getParameter(const std::string& name, const std::vector<std::string>& values,
			unsigned short stringSize, Group& parent, const std::string& description = "");
	static std::shared_ptr<Parameter> getParameter(const std::string& name, const std::string& value,
			unsigned short stringSize, Group& parent, const std::string& description = "");

private:
	std::vector<std::string> values;
	unsigned short stringSize;

protected:
	String(const std::string& name, const std::vector<std::string>& values, unsigned short stringSize, Group& parrent,
			const std::string& description);
};

} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_WRITTER_STRING_H_ */
