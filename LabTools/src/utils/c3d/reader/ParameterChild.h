/*
 * ParameterChild.h
 *
 *  Created on: 30 déc. 2015
 *      Author: alex
 */

#ifndef SRC_UTILS_C3D_PARAMETERCHILD_H_
#define SRC_UTILS_C3D_PARAMETERCHILD_H_

#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Parameter.h"

namespace utils {
namespace c3d {
namespace reader {

template<typename Type_>
class ParameterChild: public Parameter {
public:
	static std::string typeName;

	ParameterChild(std::ifstream& file, const std::string& name, int8_t entityId, uint16_t nextEntityPtr);
	virtual ~ParameterChild();

	Type_ getData(unsigned int i, unsigned int j) const;
	unsigned int getRows() const;
	unsigned int getCols() const;

	std::string toString() override;
	const std::string& getTypeName() override;

protected:
	std::vector<std::vector<Type_>> datas = std::vector<std::vector<Type_>>();

	void readData(std::ifstream& file, const std::vector<uint8_t>& dims);
};

} /* namespace reader */
} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_PARAMETERCHILD_H_ */
