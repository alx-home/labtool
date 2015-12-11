/*
 * Tag.cpp
 *
 *  Created on: 8 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "Tag.h"

#include <algorithm>

#include "../exceptions/ParamNameNotFoundException.h"

namespace utils {
namespace xml {

Tag::Tag() :
		childs(), params() {
}

Tag::~Tag() {
}

const std::vector<std::shared_ptr<Tag>>& Tag::getChilds() const {
	return childs;
}

const std::shared_ptr<Tag>& Tag::getFirstChild(const std::string& name) const {
	for (const auto& child : childs)
		if (child->getName() == name)
			return child;

	throw std::exception(); //todo exceptions
}

const std::shared_ptr<Tag>& Tag::getOrCreateChild(const std::string& name) {
	try {
		return getFirstChild(name);
	} catch (...) {
		return createChild(name);
	}
}

const std::shared_ptr<Tag>& Tag::createChild(const std::string& name) {
	std::shared_ptr<Tag> child = std::make_shared<Tag>();
	child->setName(name);
	addChild(child);

	return childs.back();
}

void Tag::removeChild(const std::string& name) {
	removeChild(getFirstChild(name));
}

void Tag::removeChilds(const std::string& name) {
	auto childs = this->childs;

	for (auto child : childs)
		if (child->getName() == name)
			removeChild(child->getName());
}

void Tag::removeChild(const std::shared_ptr<Tag>& child) {
	const auto& childIt = std::find(childs.begin(), childs.end(), child);

	if (childIt != childs.end())
		childs.erase(childIt);
}

void Tag::addChilds(std::vector<std::shared_ptr<Tag>>& childs) {
	for (auto& child : childs)
		addChild(child);
}

void Tag::addChild(const std::shared_ptr<Tag>& child) {
	if (std::find(childs.begin(), childs.end(), child) == childs.end())
		this->childs.push_back(child);
}

void Tag::addParam(const std::string& paramName, const std::string& value) {
	params[paramName] = value;
}

const std::unordered_map<std::string, std::string>& Tag::getParams() const {
	return params;
}

const std::string& Tag::getParam(const std::string& name) const {
	return params.at(name);
}

const std::string& Tag::getValue(const std::string& param) const {
	const auto& it = params.find(param);

	if (it != params.end())
		return it->second;

	throw exceptions::ParamNameNotFoundException();
}

void Tag::setName(const std::string& name) {
	this->name = name;
}

const std::string& Tag::getName() {
	return name;
}

} /* namespace xml */
} /* namespace utils */
