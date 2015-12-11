/*
 * C3dReader.h
 *
 *  Created on: 27 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_MAIN_C3DREADER_H_
#define SRC_MAIN_C3DREADER_H_

#include <windows.h>
#include <memory>
#include <string>
#include <unordered_map>

#include "../datas/DataStruct.h"

class C3dReader {
public:
	C3dReader() = delete;
	virtual ~C3dReader() = delete;

	static void read(double& frameRate, std::unordered_map<std::string, generic::DataStruct>& inputModel,
			std::unordered_map<std::string, generic::DataStruct>& inputScene, const std::shared_ptr<std::string>& modelFilePath,
			const std::shared_ptr<std::string>& sceneFilePath, const std::shared_ptr<unsigned short>& loadingPercentage,
			const std::shared_ptr<bool>& programCloser, HWND hwnd);
};

#endif /* SRC_MAIN_C3DREADER_H_ */
