/*
 * Writter.cpp
 *
 *  Created on: 1 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "Writter.h"

#include <cmath>
#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>

#include "Float.h"
#include "Group.h"
#include "Integer.h"
#include "String.h"

namespace utils {
namespace c3d {

void Writter::write(const std::string& filePath, unsigned int nbMarkers, unsigned int firstFrameNbr, unsigned int lastFrameNbr,
		unsigned int maxIntGap, float frameRate, const std::vector<std::string>& labels,
		const std::function<void(float& x, float& y, float& z, uint32_t& res, unsigned int frame)>& dataWritter) {
	std::vector<utils::c3d::writter::Group> groups;

	groups.push_back(utils::c3d::writter::Group("POINT", 1));
	utils::c3d::writter::Integer::getParameter("USED", nbMarkers, groups.back());
	utils::c3d::writter::Float::getParameter("SCALE", -1.f, groups.back());
	utils::c3d::writter::Float::getParameter("RATE", 250.f, groups.back());
	utils::c3d::writter::Integer::getParameter("DATA_START", 18, groups.back());
	utils::c3d::writter::Integer::getParameter("FRAMES", lastFrameNbr - firstFrameNbr + 1, groups.back());
	unsigned int imax = std::ceil(((double) labels.size()) / 255.);

	for (unsigned int i = 0; i < imax; ++i)
		utils::c3d::writter::String::getParameter("LABELS" + (i > 0 ? std::to_string(i + 1) : ""),
				std::vector<std::string>(labels.begin() + i * 255,
						(i + 1) * 255 - 1 > labels.size() ? labels.end() : labels.begin() + (i + 1) * 255), 30, groups.back(),
				"Marker labels");

	utils::c3d::writter::String::getParameter("UNITS", "m", 4, groups.back());
	groups.push_back(utils::c3d::writter::Group("MANUFACTURER", 2));
	utils::c3d::writter::String::getParameter("COMPANY", "Chu - Rangueil", 14, groups.back());
	utils::c3d::writter::String::getParameter("SOFTWARE", "LabTools", 8, groups.back());
	utils::c3d::writter::String::getParameter("AUTHOR", "Alexandre GARCIN", 16, groups.back());
	utils::c3d::writter::String::getParameter("VERSION", "1.0", 3, groups.back());

	std::ofstream file;
	class FileAllocator {
	public:
		FileAllocator(std::ofstream& file, const std::string& filePath) :
				file(file) {
			file.open(filePath, std::ios::binary | std::ios::out);
		}

		virtual ~FileAllocator() {
			file.close();
		}

	private:
		std::ofstream& file;
	} fileAllocator(file, filePath);

	if (!file)
		throw std::exception();

	uint8_t dataOffset = 0x2;
	file.write(&reinterpret_cast<char&>(dataOffset), sizeof(uint8_t));

	uint8_t fileType = 0x50;
	file.write(&reinterpret_cast<char&>(fileType), sizeof(uint8_t));
	file.write(&reinterpret_cast<char&>(nbMarkers), sizeof(uint16_t));

	uint16_t nbAlogMeasurementsPerFrame = 0;
	file.write(&reinterpret_cast<char&>(nbAlogMeasurementsPerFrame), sizeof(uint16_t));
	file.write(&reinterpret_cast<char&>(firstFrameNbr), sizeof(uint16_t));
	file.write(&reinterpret_cast<char&>(lastFrameNbr), sizeof(uint16_t));
	file.write(&reinterpret_cast<char&>(maxIntGap), sizeof(uint16_t));

	float scaleFactor = -1.f;
	file.write(&reinterpret_cast<char&>(scaleFactor), sizeof(uint32_t));

	uint16_t firstDataBlock = 0;
	file.write(&reinterpret_cast<char&>(firstDataBlock), sizeof(uint16_t));

	uint16_t analogSampleNbr = 0;
	file.write(&reinterpret_cast<char&>(analogSampleNbr), sizeof(uint16_t));
	file.write(&reinterpret_cast<char&>(frameRate), sizeof(uint32_t));

	for (unsigned int i = file.tellp(); i < 514; ++i) {
		uint8_t buff = 0;
		file.write(&reinterpret_cast<char&>(buff), 1);
	}

	std::ios::pos_type parameterBlockNbr = file.tellp();
	file.write(&reinterpret_cast<char&>(parameterBlockNbr), sizeof(uint8_t));

	uint8_t processorType = 0x54;
	file.write(&reinterpret_cast<char&>(processorType), sizeof(uint8_t));

	for (auto& group : groups) {
		{
			uint8_t size = group.getName().size();
			file.write(&reinterpret_cast<char&>(size), sizeof(uint8_t));

			uint8_t groupId = -group.getEntityId();
			file.write(&reinterpret_cast<char&>(groupId), sizeof(uint8_t));

			file.write(group.getName().c_str(), size);

			uint16_t length = 2 + group.getDescription().size();

			file.write(&reinterpret_cast<char&>(length), sizeof(uint16_t));
			file.write(group.getDescription().c_str(), length - 2);
		}

		for (auto& parameter : group.getParameters()) {
			uint8_t size = parameter->getName().size();
			file.write(&reinterpret_cast<char&>(size), sizeof(uint8_t));

			uint8_t groupId = parameter->getEntityId();
			file.write(&reinterpret_cast<char&>(groupId), sizeof(uint8_t));

			file.write(parameter->getName().c_str(), size);

			uint16_t length = parameter->getSize();

			file.write(&reinterpret_cast<char&>(length), sizeof(uint16_t));

			parameter->writeData(file);

			length = parameter->getDescription().size();
			file.write(&reinterpret_cast<char&>(length), sizeof(uint8_t));
			if (length != 0)
				file.write(parameter->getDescription().c_str(), length);
		}
	}

	std::ios::pos_type endPos = file.tellp();

	file.seekp(parameterBlockNbr);
	parameterBlockNbr = endPos - parameterBlockNbr + 2;
	parameterBlockNbr = std::ceil(((float) parameterBlockNbr) / 512.f);

	file.write(&reinterpret_cast<char&>(parameterBlockNbr), sizeof(uint8_t));

	unsigned short iMax = std::abs((parameterBlockNbr + (long long int) 1) * 512 - (endPos - file.tellp())) - 3;

	file.seekp(0, std::ios::end);

	for (unsigned int i = 0; i < iMax; ++i) {
		char buff = 0;
		file.write(&reinterpret_cast<char&>(buff), sizeof(uint8_t));
	}

	endPos = file.tellp();
	file.seekp(0x10);

	firstDataBlock = parameterBlockNbr + (long long int) 3;
	file.write(&reinterpret_cast<char&>(firstDataBlock), sizeof(uint16_t));

	file.seekp(0, std::ios::end);

	for (unsigned int frame = firstFrameNbr; frame <= lastFrameNbr; ++frame)
		for (unsigned int markerNb = 0; markerNb < nbMarkers; ++markerNb) {
			float x { 0 }, y { 0 }, z { 0 };
			uint32_t res;
			dataWritter(x, y, z, res, frame);

			file.write(&reinterpret_cast<char&>(x), sizeof(uint32_t));
			file.write(&reinterpret_cast<char&>(y), sizeof(uint32_t));
			file.write(&reinterpret_cast<char&>(z), sizeof(uint32_t));
			file.write(&reinterpret_cast<char&>(res), sizeof(uint32_t)); /* not implemented
			 (Byte 1: cameras that measured the marker (1 bit per camera using bits 0-7)
			 Byte 2: average residual divided by the POINT:SCALE)*/
		}
}

} /* namespace c3d */
} /* namespace utils */
