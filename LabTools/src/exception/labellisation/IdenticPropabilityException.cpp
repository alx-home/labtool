/*
 * IdenticPropabilityException.cpp
 *
 *  Created on: 2 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "IdenticPropabilityException.h"

namespace exception {
namespace labelisation {

IdenticPropabilityException::IdenticPropabilityException(const std::vector<std::string>& labels) : labels(labels) {
}

IdenticPropabilityException::~IdenticPropabilityException() {
}

const std::vector<std::string>& IdenticPropabilityException::getLabels() const {
	return labels;
}

} /* namespace labellisation */
} /* namespace exception */
