/*
 * File.cpp
 *
 *  Created on: 23 d�c. 2015
 *      Author: Alexandre GARCIN
 */

#include "File.h"

#include <windows.h>
#include <cderr.h>
#include <commdlg.h>
#include <libloaderapi.h>
#include <minwinbase.h>
#include <minwindef.h>
#include <processenv.h>
#include <shellapi.h>
#include <SFML/Graphics/Image.hpp>
#include <winbase.h>
#include <winnt.h>
#include <winuser.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <shlobj.h>

namespace utils {
namespace window {

bool File::isDirExist(const std::string& path) {
	DWORD ftyp = GetFileAttributes(path.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}

int CALLBACK File::browserFolderCallBack(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
	if (uMsg == BFFM_INITIALIZED) {
		SendMessage(hWnd, BFFM_SETSELECTION, true, lpData);
		return 1;
	}
	return 0;
}

std::string File::browseFolder(const std::string& title, HWND hwndOwner, const std::string& defaultPath) {
	char buffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buffer);

	class PathRestorer {
	public:
		char* buffer;

		PathRestorer(char* buffer) :
				buffer(buffer) {
		}

		~PathRestorer() {
			SetCurrentDirectory(buffer);
		}

		PathRestorer& operator=(const PathRestorer&) = delete;
		PathRestorer(const PathRestorer&) = delete;

	} pathRestorer(buffer);

	char folder[MAX_PATH];

	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	std::string defaultPathFormated;

	bi.hwndOwner = hwndOwner;
	bi.pidlRoot = nullptr;
	bi.pszDisplayName = folder;
	bi.lpszTitle = title.c_str();
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;

	if (defaultPath == "") {
		bi.lParam = 0;
		bi.lpfn = nullptr;
	} else {
		defaultPathFormated = defaultPath;
		std::replace(defaultPathFormated.begin(), defaultPathFormated.end(), '/', '\\');

		bi.lParam = (LPARAM) (LPSTR) defaultPathFormated.c_str();
		bi.lpfn = browserFolderCallBack;
	}

	pidl = SHBrowseForFolder(&bi);

	if (SHGetPathFromIDList(pidl, folder) == TRUE) {
		return folder;
	} else {
		throw BrowserException(CommDlgExtendedError()); // todo exception
	}
}

std::string File::browseOutputFile(const std::string& title, const LPCSTR& filesFilter) {
	char buffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buffer);

	class PathRestorer {
	public:
		char* buffer;

		PathRestorer(char* buffer) :
				buffer(buffer) {
		}

		~PathRestorer() {
			SetCurrentDirectory(buffer);
		}

		PathRestorer& operator=(const PathRestorer&) = delete;
		PathRestorer(const PathRestorer&) = delete;

	} pathRestorer(buffer);

	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory( &filename, sizeof( filename ) );
	ZeroMemory( &ofn, sizeof( ofn ) );
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = filesFilter;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;

	if (GetSaveFileName(&ofn)) {
		return filename;
	} else {
		throw BrowserException(CommDlgExtendedError()); // todo exception
	}
}

std::string File::browseFile(const std::string& title, const LPCSTR& filesFilter) {
	char buffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buffer);

	class PathRestorer {
	public:
		char* buffer;

		PathRestorer(char* buffer) :
				buffer(buffer) {
		}

		~PathRestorer() {
			SetCurrentDirectory(buffer);
		}

		PathRestorer& operator=(const PathRestorer&) = delete;
		PathRestorer(const PathRestorer&) = delete;

	} pathRestorer(buffer);

	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory( &filename, sizeof( filename ) );
	ZeroMemory( &ofn, sizeof( ofn ) );
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = filesFilter;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;

	if (GetOpenFileName(&ofn)) {
		return filename;
	} else {
		throw BrowserException(CommDlgExtendedError()); // todo exception
	}
}

File::BrowserException::BrowserException(DWORD errorCode) :
		errorCode(errorCode) {
}

File::BrowserException::~BrowserException() {
}

DWORD File::BrowserException::getErrorCode() const {
	return errorCode;
}

void File::removeDirectory(std::string path) {

	HMODULE hModule = GetModuleHandleW(NULL);
	std::string postPath = "";
	postPath.resize(MAX_PATH);

	int result = GetModuleFileName(hModule, const_cast<char*>(postPath.c_str()), MAX_PATH);

	postPath.resize(result);

	if (result > MAX_PATH)
		int result = GetModuleFileName(hModule, const_cast<char*>(postPath.c_str()), MAX_PATH);

	postPath = postPath.substr(0, postPath.size() - 13);
	std::replace(postPath.begin(), postPath.end(), '\\', '/');

	if (path.substr(0, postPath.size()) != postPath)
		path = postPath + "/" + path;

	SHFILEOPSTRUCT shfo = {
	NULL,
	FO_DELETE, std::string(path + '\0', path.size() + 1).c_str(),
	NULL,
	FOF_SILENT | FOF_NOCONFIRMATION,
	FALSE,
	NULL,
	NULL };

	if (result = SHFileOperation(&shfo)) {
		std::cout << "(" << result << ") " << std::endl;
		throw std::exception();
	}
}

} /* namespace window */
} /* namespace utils */
