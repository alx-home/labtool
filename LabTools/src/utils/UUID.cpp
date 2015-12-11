/*
 * UniqueId.cpp
 *
 *  Created on: 5 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "UUID.h"

namespace utils {

UUID::UUID() {
}

UUID::~UUID() {
}

unsigned long long int UUID::getUUID() {
	if (availibleUUID.empty())
		return lastUUID++;

	auto result = availibleUUID.top();
	availibleUUID.pop();

	return result;
}

void UUID::freeUUID(unsigned long long int UUID) {
	if (UUID == lastUUID - 1)
		--lastUUID;
	else {
		availibleUUID.push(UUID);
	}
}

} /* namespace utils */
