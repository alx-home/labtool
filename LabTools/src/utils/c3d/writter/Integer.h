/*
 * Integer.h
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_C3D_WRITTER_INTEGER_H_
#define SRC_UTILS_C3D_WRITTER_INTEGER_H_

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

class Integer: public Parameter {
public:
	virtual ~Integer();

	void writeData(std::ofstream& file) const override;
	uint16_t getSize() const override;
	static std::shared_ptr<Parameter> getParameter(const std::string& name, uint16_t value, Group& parent, const std::string& description =
			"");

private:
	uint16_t value;

protected:
	Integer(const std::string& name, uint16_t value, Group& parrent, const std::string& description);
};

} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_WRITTER_INTEGER_H_ */
