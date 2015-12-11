/*
 * RootTag.h
 *
 *  Created on: 8 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_XML_TAG_ROOTTAG_H_
#define SRC_UTILS_XML_TAG_ROOTTAG_H_

#include "Tag.h"

namespace utils {
namespace xml {

class RootTag: public Tag {
public:
	RootTag();
	virtual ~RootTag();
};

} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_TAG_ROOTTAG_H_ */
