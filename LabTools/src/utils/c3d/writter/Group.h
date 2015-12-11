/*
 * Group.h
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_C3D_WRITTER_GROUP_H_
#define SRC_UTILS_C3D_WRITTER_GROUP_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace utils {
namespace c3d {
namespace writter {
class Parameter;
} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */

namespace utils {
namespace c3d {
namespace writter {

class Group {
public:
	Group(const std::string& name, uint8_t entityId, const std::string& description = std::string("\0", 1));
	virtual ~Group();
	const std::string& getName() const;
	const std::string& getDescription() const;
	uint8_t getEntityId() const;
	const std::vector<std::shared_ptr<Parameter> >& getParameters() const;

private:
	std::string name;
	std::string description;
	uint8_t entityId;
	std::vector<std::shared_ptr<Parameter>> parameters = std::vector<std::shared_ptr<Parameter>>();

	void attachParameter(const std::shared_ptr<Parameter>& parameter);

	friend class Parameter;
};

} /* namespace writter */
} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_WRITTER_GROUP_H_ */
