/*
 * Tag.h
 *
 *  Created on: 8 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_TAG_H_
#define SRC_UTILS_XML_TAG_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace utils {
namespace xml {

class Tag {
protected:
	std::vector<std::shared_ptr<Tag>> childs;
	std::unordered_map<std::string, std::string> params;
	std::string name = "";

public:
	Tag();
	virtual ~Tag();

	const std::vector<std::shared_ptr<Tag>>& getChilds() const;
	const std::shared_ptr<Tag>& getFirstChild(const std::string& name) const;
	const std::shared_ptr<Tag>& getOrCreateChild(const std::string& name);
	const std::shared_ptr<Tag>& createChild(const std::string& name);
	void removeChild(const std::string& name);
	void removeChilds(const std::string& name);
	void removeChild(const std::shared_ptr<Tag>& child);
	void addChilds(std::vector<std::shared_ptr<Tag>>& childs);
	void addChild(const std::shared_ptr<Tag>& childs);
	void setName(const std::string& name);
	void addParam(const std::string& paramName, const std::string& value);
	const std::unordered_map<std::string, std::string>& getParams() const;
	const std::string& getParam(const std::string& name) const;
	const std::string& getValue(const std::string& param) const;
	const std::string& getName();
};

} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_TAG_H_ */
