/*
 * FolderBrowserLayer.h
 *
 *  Created on: 17 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_BROWSER_FOLDERBROWSERLAYER_H_
#define SRC_WINDOW_LAYER_CONTENT_BROWSER_FOLDERBROWSERLAYER_H_

#include <windef.h>
#include <functional>
#include <string>

#include "BrowserLayer.h"

namespace window {

class FolderBrowserLayer: public BrowserLayer {
public:
	FolderBrowserLayer(HWND hwndOwner, const std::string& defaultPathText = "Empty", const std::string& defaultPath = "\n",
			unsigned int size = 25, const std::string& title = "LabTools", const std::function<void(float)>& callback =
					[](float timestamp) {});
	virtual ~FolderBrowserLayer();

	FolderBrowserLayer(const FolderBrowserLayer&) = delete;
	FolderBrowserLayer& operator=(const FolderBrowserLayer&) = delete;

protected:
	HWND hwnd;
	std::string defaultPath;
	std::string defaultPathText;

	std::string browse() const override;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_BROWSER_FOLDERBROWSERLAYER_H_ */
