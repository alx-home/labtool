/*
 * XMLReader.h
 *
 *  Created on: 27 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_MAIN_EXE_XMLREADER_H_
#define SRC_MAIN_EXE_XMLREADER_H_

#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../datas/Box.h"

class GroupMarker;
class SplashScreen;

namespace utils {
namespace xml {
class Tag;
} /* namespace xml */
} /* namespace utils */

class XMLReader {
public:
	XMLReader() = delete;
	virtual ~XMLReader() = delete;

	static void read(const std::shared_ptr<std::string>& modelFilePath,
			std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker> > >& estimationSets,
			std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker> >& groupMarkers,
			std::vector<std::tuple<std::string, labeliser::Box> >& labelisationBoxes, unsigned int& gapFramesSize,
			SplashScreen& splashScreen, double& probaMin, double& interFrameDistMax);
};

#endif /* SRC_MAIN_EXE_XMLREADER_H_ */
