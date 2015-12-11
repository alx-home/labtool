/*
 * Installer.h
 *
 *  Created on: 28 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_MAIN_EXE_INSTALLER_H_
#define SRC_MAIN_EXE_INSTALLER_H_

#include <exception>
#include <functional>
#include <stack>

#ifdef WITH_INSTALLER
class Installer {
public:
	Installer() = delete;
	virtual ~Installer() = delete;

	static void perform();

	class AdminPrivilegeRequiredException: public std::exception {
	public:
		AdminPrivilegeRequiredException(std::stack<std::function<void()>>& uninstaller);
		virtual ~AdminPrivilegeRequiredException();
	};
};
#endif
#endif /* SRC_MAIN_EXE_INSTALLER_H_ */
