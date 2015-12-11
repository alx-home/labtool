/*
 * Writter.h
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_C3D_WRITTER_H_
#define SRC_UTILS_C3D_WRITTER_H_

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace utils {
namespace c3d {

class Writter {
public:
	static void write(const std::string& filePath, unsigned int nbMarkers, unsigned int firstFrameNbr, unsigned int lastFrameNbr,
			unsigned int maxIntGap, float frameRate, const std::vector<std::string>& labels,
			const std::function<void(float& x, float& y, float& z, uint32_t& res, unsigned int frame)>& dataWritter);

private:
	Writter() = delete;
	virtual ~Writter() = delete;
};

} /* namespace c3d */
} /* namespace utils */

#endif /* SRC_UTILS_C3D_WRITTER_H_ */
