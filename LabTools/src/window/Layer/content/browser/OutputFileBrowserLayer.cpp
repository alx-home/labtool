/*
 * OutputFileBrowserLayer.cpp
 *
 *  Created on: 17 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "OutputFileBrowserLayer.h"

#include <winnt.h>

#include "../../../../utils/window/files/File.h"

namespace window {

OutputFileBrowserLayer::OutputFileBrowserLayer(const std::string& defaultPath, unsigned int size,
		const std::function<void(float)>& callback, const std::string& title, const std::string& pattern) :
		FileBrowserLayer(defaultPath, size, callback, title, pattern) {
}

OutputFileBrowserLayer::~OutputFileBrowserLayer() {
}

std::string OutputFileBrowserLayer::browse() const {
	return utils::window::File::browseOutputFile(this->title, (LPSTR) this->pattern.c_str());
}

} /* namespace window */
