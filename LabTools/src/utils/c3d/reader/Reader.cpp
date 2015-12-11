/*
 * Reader.cpp
 *
 *  Created on: 29 déc. 2015
 *      Author: alex
 */

#include "Reader.h"

#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../../../Language/LanguageLoader.h"
#include "Group.h"
#include "Parameter.h"
#include "ParameterChild.h"

namespace utils {
namespace c3d {

void Reader::read(const std::string& filePath,
		std::function<void(float x, float y, float z, unsigned int nbFrames, unsigned int frame, const std::string& markerLabel)> datasWriter,
		std::function<void(const std::shared_ptr<reader::Group>& group)> parameterReader,
		std::function<void(const std::string& text)> headerPrinter, DataFormat dataFormats) {
	std::ifstream file;
	class FileAllocator {
	public:
		FileAllocator(std::ifstream& file, const std::string& filePath) :
			file(file) {
			file.open(filePath, std::ios::binary | std::ios::in);
		}

		virtual ~FileAllocator() {
			file.close();
		}

	private:
		std::ifstream& file;
	} fileAllocator(file, filePath);

	uint8_t dataOffset;
	file.read(&reinterpret_cast<char&>(dataOffset), sizeof(uint8_t));

	{
		uint8_t fileType;
		file.read(&reinterpret_cast<char&>(fileType), sizeof(uint8_t));

		if (fileType != 0x50)
			throw std::exception(); //todo exception
	}

	uint16_t nbMarkers;
	file.read(&reinterpret_cast<char&>(nbMarkers), sizeof(uint16_t));

	headerPrinter(SERIALIZER->getNumberOfMarker()+ std::to_string(static_cast<unsigned int>(nbMarkers)) + "\n");

	{
		uint16_t nbAlogMeasurementsPerFrame;
		file.read(&reinterpret_cast<char&>(nbAlogMeasurementsPerFrame), sizeof(uint16_t)); // inutile pour du numéric
	}

	uint16_t firstFrameNbr;
	file.read(&reinterpret_cast<char&>(firstFrameNbr), sizeof(uint16_t));

	headerPrinter(SERIALIZER->getFirstFrameNbr()+ std::to_string(static_cast<unsigned int>(firstFrameNbr)) + "\n");

	uint16_t lastFrameNbr;
	file.read(&reinterpret_cast<char&>(lastFrameNbr), sizeof(uint16_t));

	headerPrinter(SERIALIZER->getLastFrameNbr()+ std::to_string(static_cast<unsigned int>(lastFrameNbr)) + "\n");

	{
		//Maximum interpolation gap in 3D frames.
		uint16_t maxIntGap;
		file.read(&reinterpret_cast<char&>(maxIntGap), sizeof(uint16_t));
	}

	uint32_t scaleFactor;
	file.read(&reinterpret_cast<char&>(scaleFactor), sizeof(uint32_t));

	headerPrinter(SERIALIZER->getScaleFactor()+ std::to_string(reinterpret_cast<float&>(scaleFactor)) + "\n");

	DataFormat format = reinterpret_cast<float&>(scaleFactor) == -1.f ? DataFormat::FLOAT : DataFormat::INTEGER;

	if (!(format & dataFormats)) {
		throw std::exception(); //todo exception

		std::cerr << SERIALIZER->getInvalidDataFormat() << "\n";

		if (dataFormats & DataFormat::INTEGER)
			std::cerr << "\tExpected integer, received float." << std::endl;
		else
			std::cerr << "\tExpected float, received integer." << std::endl;
	}

	uint16_t firstDataBlock;
	file.read(&reinterpret_cast<char&>(firstDataBlock), sizeof(uint16_t));

	{
		std::stringstream stream;
		stream << std::hex << std::to_string(static_cast<int>(firstDataBlock));

#ifdef c3dReaderDebug
		std::cout << "First data block : " << stream.str() << "\n";
#endif
	}

	{
		//The number of analog samples per 3D frame.

		uint16_t analogSampleNbr;
		file.read(&reinterpret_cast<char&>(analogSampleNbr), sizeof(uint16_t));

		if (analogSampleNbr != 0) {
			std::cerr << SERIALIZER->getAnalogueDatasNotImplemented() << std::endl; //todo analogues datas

			throw std::exception();//todo exception
		}
	}

	uint32_t frameRate;
	file.read(&reinterpret_cast<char&>(frameRate), sizeof(uint32_t));

	headerPrinter(SERIALIZER->getAquisitionFrequency()+ std::to_string(reinterpret_cast<float&>(frameRate)) + "\n");

	file.seekg((((unsigned int) dataOffset) - 1) * 512 + 2);

	uint8_t parameterBlockNbr;
	file.read(&reinterpret_cast<char&>(parameterBlockNbr), sizeof(uint8_t));

	{
		std::stringstream stream;
		stream << std::hex << std::to_string(static_cast<unsigned int>(parameterBlockNbr));
#ifdef c3dReaderDebug
		std::cout << "number of parameter blocks : " << stream.str() << "\n";
#endif
	}

	{
		uint8_t processorType;
		file.read(&reinterpret_cast<char&>(processorType), sizeof(uint8_t));

		if (processorType == 84)
			headerPrinter(SERIALIZER->getProcessorUsed()+ "Intel\n");
		else if (processorType == 85)
			headerPrinter(SERIALIZER->getProcessorUsed() + "DEC (VAX, PDP-11)\n");
		else if (processorType == 86)
			headerPrinter(SERIALIZER->getProcessorUsed() + "MIPS (SGI/MIPS)\n");
		else
			std::cerr << SERIALIZER->getInvalidProcessorType() << std::endl;

	}

	std::unordered_map<int8_t, std::vector<std::shared_ptr<reader::Entity> > > entities;
	std::unordered_map<int8_t, std::shared_ptr<reader::Group>> groups;
	std::vector<std::shared_ptr<reader::ParameterChild<reader::Parameter::Character> > > labelsParameter;

	{
		std::shared_ptr<reader::Entity> entity;
		while ((entity = reader::Entity::getNextEntity(file)) != nullptr)
			if (std::dynamic_pointer_cast<reader::Group>(entity) != nullptr)
				groups[entity->getEntityId()] = std::static_pointer_cast<reader::Group>(entity);
			else {
				if (std::dynamic_pointer_cast<reader::ParameterChild<reader::Parameter::Character>>(entity) != nullptr) {
					const auto& it = std::static_pointer_cast<reader::ParameterChild<reader::Parameter::Character>>(entity);

					if (it->getName().substr(0, 6) == "LABELS")
						labelsParameter.push_back(it);
				}
				entities[entity->getEntityId()].push_back(entity);
			}
	}

	if (labelsParameter.size() == 0) {
		std::cerr << SERIALIZER->getParameterLabelsNotFound() << std::endl; //todo analogues datas

		throw std::exception();//todo exception
	}

	for (const auto& group : entities)
		for (const auto& entity : group.second)
			if (groups.find(entity->getEntityId()) == groups.end()) {
				std::cerr << SERIALIZER->getEntityGroupNotFound1() << std::to_string(entity->getEntityId())
				<< SERIALIZER->getEntityGroupNotFound2() << std::endl;

				throw std::exception(); // todo exception
			} else
				groups[entity->getEntityId()]->attachParameter(std::static_pointer_cast<reader::Parameter>(entity));

	for (const auto& group : groups)
		parameterReader(group.second);

	unsigned int dataStart = reinterpret_cast<unsigned int&>(firstDataBlock) - 1;
	dataStart *= 512;

	file.seekg(0, std::ios::end);
	unsigned int dataSize = ((unsigned int) file.tellg()) - dataStart;

	unsigned int nbFrames = lastFrameNbr - firstFrameNbr + 1;

	if (format & DataFormat::FLOAT) {

		unsigned int blockSize = static_cast<unsigned int>(nbMarkers) * sizeof(uint32_t) * 4;

#ifdef c3dReaderDebug
		std::cout << "blockSize : " << std::to_string(blockSize) << "\n";
#endif

		if (dataSize != nbFrames * blockSize) {
			std::cerr << SERIALIZER->getInvalidTypeOrNumberOf3DPoints() << "\n\t\t expected : "
					<< std::to_string((lastFrameNbr + 1) * blockSize) << ", received : " << std::to_string(dataSize) << "." << std::endl;

			throw std::exception();
		}

		for (unsigned int frame = 0; frame <= lastFrameNbr; ++frame) {
			file.seekg(dataStart + frame * blockSize);

			std::clog << SERIALIZER->getFrameReading1() << std::to_string(frame + 1) << "(" << SERIALIZER->getFrameReading2()
					<< std::to_string(dataStart + frame * blockSize) << ")" << std::endl;

			unsigned int labelsParameterIndex = 0;
			auto labelsParameterIt = labelsParameter[0];
			unsigned int offset = 0;
			unsigned int lastLabelsParameterSumSize = labelsParameterIt->getRows();

			for (unsigned int markerNb = 0; markerNb < nbMarkers; ++markerNb) {
				if (markerNb >= lastLabelsParameterSumSize) {
					++labelsParameterIndex;
					labelsParameterIt = labelsParameter[labelsParameterIndex];
					offset = lastLabelsParameterSumSize;
					lastLabelsParameterSumSize += labelsParameterIt->getRows();
				}

				uint32_t x, y, z;
				file.read(&reinterpret_cast<char&>(x), sizeof(uint32_t));
				file.read(&reinterpret_cast<char&>(y), sizeof(uint32_t));
				file.read(&reinterpret_cast<char&>(z), sizeof(uint32_t));

				datasWriter(reinterpret_cast<float&>(x), reinterpret_cast<float&>(y), reinterpret_cast<float&>(z), nbFrames, frame,
						labelsParameterIt->getData(markerNb - offset, 0).value);

				file.read(&reinterpret_cast<char&>(x), sizeof(uint32_t)); /* not implemented
				 (Byte 1: cameras that measured the marker (1 bit per camera using bits 0-7)
				 Byte 2: average residual divided by the POINT:SCALE)*/
			}
		}

	} else {
		std::cerr << SERIALIZER->getC3dIntegerDatasNotImplemented() << std::endl;

		throw std::exception(); //todo exception
	}
}

} /* namespace c3d */
} /* namespace utils */
