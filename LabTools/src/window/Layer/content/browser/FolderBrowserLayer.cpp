/*
 * FolderBrowserLayer.cpp
 *
 *  Created on: 17 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "FolderBrowserLayer.h"

#include <memory>

#include "../../../../utils/window/files/File.h"
#include "../../Layer.h"
#include "../Buttons/Button.h"
#include "../TextField.h"

namespace window {

FolderBrowserLayer::FolderBrowserLayer(HWND hwndOwner, const std::string& defaultPathText, const std::string& defaultPath,
		unsigned int size, const std::string& title, const std::function<void(float)>& callback) :
		BrowserLayer(std::make_shared<TextField>(defaultPathText, size), std::make_shared<Button>(false, "...", size, callback), title), hwnd(
				hwndOwner), defaultPathText(defaultPathText), defaultPath(defaultPath) {
	init();
}

FolderBrowserLayer::~FolderBrowserLayer() {
}

std::string FolderBrowserLayer::browse() const {
	return utils::window::File::browseFolder(this->title, hwnd,
			textField->getText() == defaultPathText && defaultPath != "\n" ? defaultPath : textField->getText());
}

} /* namespace window */
