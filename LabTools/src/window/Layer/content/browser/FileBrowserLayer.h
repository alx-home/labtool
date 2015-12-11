/*
 * FileBrowserLayer.h
 *
 *  Created on: 17 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_BROWSER_FILEBROWSERLAYER_H_
#define SRC_WINDOW_LAYER_CONTENT_BROWSER_FILEBROWSERLAYER_H_

#include <functional>
#include <string>

#include "BrowserLayer.h"

namespace window {

class FileBrowserLayer: public BrowserLayer {
public:
	FileBrowserLayer(const std::string& defaultPath = "Empty", unsigned int size = 25, const std::function<void(float)>& callback =
			[](float timestamp) {}, const std::string& title = "LabTools",
			const std::string& pattern = std::string("c3d Files\0*.c3d\0\0", 17));
	virtual ~FileBrowserLayer();

	void setPattern(const std::string&);

protected:
	std::string pattern;

	virtual std::string browse() const override;
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_CONTENT_BROWSER_FILEBROWSERLAYER_H_ */
