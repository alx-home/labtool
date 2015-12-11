/*
 * Float.h
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_C3D_WRITTER_FLOAT_H_
#define SRC_UTILS_C3D_WRITTER_FLOAT_H_

#include <cstdint>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>

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

class Float: public Parameter {
public:
	virtual ~Float();

	void writeData(std::ofstream& file) const override;
	uint16_t getSize() const override;
	static std::shared_ptr<Parameter> getParameter(const std::string& name, float value, Group& parent, const std::string& description =
			"");

private:
	float value;

protected:
	Float(const std::string& name, float value, Group& parrent, const std::string& description);
};

} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_WRITTER_FLOAT_H_ */
