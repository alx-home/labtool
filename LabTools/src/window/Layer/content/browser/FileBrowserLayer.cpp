/*
 * FileBrowserLayer.cpp
 *
 *  Created on: 17 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "FileBrowserLayer.h"

#include <winnt.h>
#include <memory>

#include "../../../../utils/window/files/File.h"
#include "../Buttons/Button.h"
#include "../TextField.h"

namespace window {

FileBrowserLayer::FileBrowserLayer(const std::string& defaultPath, unsigned int size, const std::function<void(float)>& callback,
		const std::string& title, const std::string& pattern) :
		BrowserLayer(std::make_shared<TextField>(defaultPath, size), std::make_shared<Button>(false, "...", size, callback), title), pattern(
				pattern) {
	init();
}

FileBrowserLayer::~FileBrowserLayer() {
}

std::string FileBrowserLayer::browse() const {
	return utils::window::File::browseFile(this->title, (LPSTR) this->pattern.c_str());
}

void FileBrowserLayer::setPattern(const std::string& pattern) {
	this->pattern = pattern;
}

} /* namespace window */
