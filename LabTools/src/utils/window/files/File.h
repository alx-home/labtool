/*
 * File.h
 *
 *  Created on: 23 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_WINDOW_FILES_FILE_H_
#define SRC_UTILS_WINDOW_FILES_FILE_H_

#include <windows.h>
#include <exception>
#include <string>

namespace sf {
class Image;
} /* namespace sf */

namespace utils {
namespace window {

class File {
public:
	File() = delete;
	virtual ~File() = delete;

	static std::string browseFile(const std::string& title, const LPCSTR& filesFilter);
	static std::string browseOutputFile(const std::string& title, const LPCSTR& filesFilter);
	static std::string browseFolder(const std::string& title, HWND hwndOwner, const std::string& defaultPath = "");
	static int CALLBACK browserFolderCallBack(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	static void removeDirectory(std::string);
	static bool isDirExist(const std::string& path);

	class BrowserException: public std::exception {
	public:
		BrowserException(DWORD errorCode);
		virtual ~BrowserException();
		DWORD getErrorCode() const;

	private:
		DWORD errorCode;
	};
};

} /* namespace window */
} /* namespace utils */

#endif /* SRC_UTILS_WINDOW_FILES_FILE_H_ */
