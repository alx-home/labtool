/*
 * UniqueId.h
 *
 *  Created on: 5 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_UUID_H_
#define SRC_UTILS_UUID_H_

#include <stack>

namespace utils {

class UUID {
public:
	UUID();
	virtual ~UUID();

	unsigned long long int getUUID();
	void freeUUID(unsigned long long int);

private:
	unsigned long long int lastUUID = 0;
	std::stack<unsigned long long int> availibleUUID = std::stack<unsigned long long int>();
};

} /* namespace utils */

#endif /* SRC_UTILS_UUID_H_ */
