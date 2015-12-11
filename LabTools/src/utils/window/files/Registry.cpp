/*
 * Registry.cpp
 *
 *  Created on: 27 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "Registry.h"

#include <minwindef.h>
#include <shlwapi.h>
#include <winerror.h>
#include <winnt.h>
#include <winreg.h>
#include <exception>
#include <iostream>

namespace utils {
namespace windows {

void Registry::deleteKey() {
	HKEY key;

	class RegisterCloser {
	public:
		RegisterCloser(HKEY& key) :
				key(key) {

		}
		virtual ~RegisterCloser() {
			RegCloseKey(key);
		}

		RegisterCloser(RegisterCloser&) = delete;
		RegisterCloser& operator=(const RegisterCloser&) = delete;

	private:
		HKEY& key;
	} registerCloser(key);

	if (SHDeleteKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\LabTools")) != ERROR_SUCCESS)
		std::cerr << "Error: impossible de supprimer la clé de registre : LabTools" << std::endl;
}

void Registry::setStringKeyValue(LPCTSTR valueName, const std::string& value) {
	HKEY key;
	DWORD lpdwDisposition;
	DWORD pdwType;
	unsigned short errorCode = 0;

	class RegisterCloser {
	public:
		RegisterCloser(HKEY& key) :
				key(key) {

		}
		virtual ~RegisterCloser() {
			RegCloseKey(key);
		}

		RegisterCloser(RegisterCloser&) = delete;
		RegisterCloser& operator=(const RegisterCloser&) = delete;

	private:
		HKEY& key;
	} registerCloser(key);

	try {
		if ((errorCode = RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\LabTools"), 0, nullptr, REG_OPTION_NON_VOLATILE,
		KEY_SET_VALUE | KEY_QUERY_VALUE, nullptr, &key, &lpdwDisposition)) != ERROR_SUCCESS)
			throw std::exception();

		if ((errorCode = RegSetValueEx(key, valueName, 0, REG_SZ, (unsigned char*) value.c_str(), value.size() + 1)) != ERROR_SUCCESS)
			throw std::exception();
	} catch (...) {
		std::cerr << "Error: une erreur est survenue lors de la lecture de la valeur : " << valueName
				<< ", du registre HKEY_CURENT_USER\\SOFTWARE\\LabTools.\n\terror code : " << errorCode << std::endl;
	}
}

std::string Registry::getStringKeyValue(LPCTSTR valueName, const std::string& defaultValue) { //todo safe checks
	HKEY key;
	DWORD lpdwDisposition;
	DWORD pdwType;
	DWORD pcbData = MAX_PATH;
	DWORD lpType;
	std::string result;
	result.resize(MAX_PATH);
	unsigned short errorCode = 0;

	class RegisterCloser {
	public:
		RegisterCloser(HKEY& key) :
				key(key) {

		}
		virtual ~RegisterCloser() {
			RegCloseKey(key);
		}

		RegisterCloser(RegisterCloser&) = delete;
		RegisterCloser& operator=(const RegisterCloser&) = delete;

	private:
		HKEY& key;
	} registerCloser(key);

	try {
		if ((errorCode = RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\LabTools"), 0, nullptr, REG_OPTION_NON_VOLATILE,
		KEY_SET_VALUE | KEY_QUERY_VALUE, nullptr, &key, &lpdwDisposition)) != ERROR_SUCCESS)
			throw std::exception();

		if (lpdwDisposition == REG_CREATED_NEW_KEY) {
			if ((errorCode = RegSetValueEx(key, valueName, 0, REG_SZ, (unsigned char*) defaultValue.c_str(), defaultValue.size() + 1))
					!= ERROR_SUCCESS)
				throw std::exception();

			return defaultValue;
		} else {
			errorCode = RegQueryValueEx(key, valueName, nullptr, &lpType, (unsigned char*) const_cast<char*>(result.c_str()), &pcbData);

			if (errorCode != ERROR_SUCCESS)
				if (lpType != REG_SZ) {
					if (lpType != 0) {
						errorCode = 0xffff;
						throw std::exception();
					}

					if ((errorCode = RegSetValueEx(key, valueName, 0, REG_SZ, (unsigned char*) defaultValue.c_str(),
							defaultValue.size() + 1)) != ERROR_SUCCESS)
						throw std::exception();

					return defaultValue;
				} else if (errorCode == ERROR_MORE_DATA) {
					result.resize(pcbData);

					if ((errorCode = RegQueryValueEx(key, valueName, nullptr, nullptr, (unsigned char*) const_cast<char*>(result.c_str()),
							&pcbData)) != ERROR_SUCCESS)
						throw std::exception();
				} else
					throw std::exception();

			result.resize(pcbData - 1);
		}
	} catch (...) {
		if (errorCode != 0xffff)
			std::cerr << "Error: une erreur est survenue lors de la lecture de la valeur : " << valueName
					<< ", du registre HKEY_CURENT_USER\\SOFTWARE\\LabTools.\n\terror code : " << errorCode << std::endl;
		else
			std::cerr << "Error: une erreur est survenue lors de la lecture de la valeur : " << valueName
					<< ", du registre HKEY_CURENT_USER\\SOFTWARE\\LabTools.\n\tLe type de la clée est incorrect, expected : " << REG_SZ
					<< ", received : " << lpType << "." << std::endl;
		return defaultValue;
	}

	return result;
}

} /* namespace windows */
} /* namespace utils */
