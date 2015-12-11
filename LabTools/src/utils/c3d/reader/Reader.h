/*
 * Reader.h
 *
 *  Created on: 29 déc. 2015
 *      Author: alex
 */

#ifndef SRC_UTILS_C3D_READER_H_
#define SRC_UTILS_C3D_READER_H_

#include <functional>
#include <memory>
#include <string>

#include "Group.h"

namespace utils {
namespace c3d {

class Reader {
public:
	typedef enum {
		INTEGER = 0x1, FLOAT = 0x10, ALL = 0x11
	} DataFormat;

	static void read(const std::string& path,
			std::function<void(float x, float y, float z, unsigned int nbFrames, unsigned int frame, const std::string& markerLabel)> datasWriter,
			std::function<void(const std::shared_ptr<reader::Group>& group)> parameterReader, std::function<void(const std::string& text)> headerPrinter, DataFormat dataFormats = ALL);

private:
	Reader() = delete;
	virtual ~Reader() = delete;
};

} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_READER_H_ */
