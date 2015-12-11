/*
 * Parameter.h
 *
 *  Created on: 30 déc. 2015
 *      Author: alex
 */

#ifndef SRC_UTILS_C3D_PARAMETER_H_
#define SRC_UTILS_C3D_PARAMETER_H_

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include "Entity.h"

namespace utils {
namespace c3d {
namespace reader {

class Parameter: public Entity {
public:
	template<typename Type_>
	struct Type {
	public:
		Type() {
		}
		virtual ~Type() {
		}

		virtual std::string toString() const = 0;
	};

	struct Character: Type<std::string> {
	public:
		Character() {
		}
		virtual ~Character() {
		}

		std::string value = "";

		std::string toString() const override {
			return value;
		}
	};

	struct Byte: Type<uint8_t> {
	public:
		uint8_t value = 0x0;

		std::string toString() const override {
			return std::to_string(value);
		}
	};

	struct Integer: Type<uint16_t> {
	public:
		uint16_t value = 0x0;

		std::string toString() const override {
			return std::to_string(value);
		}
	};

	struct Float: Type<uint32_t> {
	public:
		uint32_t value = 0x0;

		std::string toString() const override {
			return std::to_string(reinterpret_cast<const float&>(value));
		}
	};

	virtual ~Parameter();

	static std::shared_ptr<Parameter> getParameterData(std::ifstream& file, const std::string& name, int8_t entityId,
			uint16_t nextEntityPtr);
	virtual std::string toString() = 0;
	virtual const std::string& getTypeName() = 0;

protected:
	Parameter(std::ifstream& file, const std::string& name, int8_t entityId, uint16_t nextEntityPtr);
};

} /* namespace reader */
} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_PARAMETER_H_ */
