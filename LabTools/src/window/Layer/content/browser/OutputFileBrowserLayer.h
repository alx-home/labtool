/*
 * OutputFileBrowserLayer.h
 *
 *  Created on: 17 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_BROWSER_OUTPUTFILEBROWSERLAYER_H_
#define SRC_WINDOW_LAYER_CONTENT_BROWSER_OUTPUTFILEBROWSERLAYER_H_

#include <functional>
#include <string>

#include "FileBrowserLayer.h"

namespace window {

class OutputFileBrowserLayer: public FileBrowserLayer {
public:
	OutputFileBrowserLayer(const std::string& defaultPath = "Empty", unsigned int size = 25, const std::function<void(float)>& callback =
			[](float timestamp) {}, const std::string& title = "LabTools",
			const std::string& pattern = std::string("c3d Files\0*.c3d\0\0", 17));
	virtual ~OutputFileBrowserLayer();

protected:
	std::string browse() const override;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_BROWSER_OUTPUTFILEBROWSERLAYER_H_ */
