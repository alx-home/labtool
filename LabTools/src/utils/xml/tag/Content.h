/*
 * Content.h
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_TAG_CONTENT_H_
#define SRC_UTILS_XML_TAG_CONTENT_H_

#include <string>

#include "Tag.h"

namespace utils {
namespace xml {

class Content: public Tag {
public:
	Content(const std::string& content);
	virtual ~Content();

	const std::string& getContent() const;

protected:
	std::string content;
};

} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_TAG_CONTENT_H_ */
