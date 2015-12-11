/*
 * Content.cpp
 *
 *  Created on: 11 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "Content.h"

namespace utils {
namespace xml {

Content::Content(const std::string& content) :
		content(content) {
}

Content::~Content() {
}

const std::string& Content::getContent() const {
	return content;
}

} /* namespace xml */
} /* namespace utils */
