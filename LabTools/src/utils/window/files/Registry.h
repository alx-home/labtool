/*
 * Registry.h
 *
 *  Created on: 27 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_WINDOW_FILES_REGISTRY_H_
#define SRC_UTILS_WINDOW_FILES_REGISTRY_H_

#include <windows.h>
#include <string>

namespace utils {
namespace windows {

class Registry {
public:
	Registry() = delete;
	virtual ~Registry() = delete;

	static std::string getStringKeyValue(LPCTSTR keyName, const std::string& defaultValue);
	static void setStringKeyValue(LPCTSTR keyName, const std::string& value);
	static void deleteKey();
};

} /* namespace windows */
} /* namespace utils */

#endif /* SRC_UTILS_WINDOW_FILES_REGISTRY_H_ */
