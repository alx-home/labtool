/*
 * Writter.cpp
 *
 *  Created on: 29 déc. 2015
 *      Author: alex
 */

#include "Writter.h"

#include <unordered_map>
#include <vector>

#include "exceptions/OpenFileException.h"
#include "tag/RootTag.h"

namespace utils {
namespace xml {

Writter::File::File(const std::string& filePath) :
		std::ofstream(filePath) {
	if (!*this)
		throw exceptions::OpenFileException();
}

Writter::File::~File() {
	std::ofstream::close();
}

void Writter::File::incrementTabulation() {
	++tabulationOffset;
}

void Writter::File::decrementTabulation() {
	--tabulationOffset;
}

void Writter::File::writeTabulation() {
	for (unsigned int i = 0; i < tabulationOffset; ++i)
		*this << "\t";
}

void Writter::write(const std::string& filePath, const std::shared_ptr<RootTag>& rootTag) {
	File file(filePath);

	for (auto& child : rootTag->getChilds())
		writeSubTag(file, child, true);
}

void Writter::writeSubTag(File& file, const std::shared_ptr<Tag>& tag, bool root) {
	if (!root)
		file.incrementTabulation();

	file.writeTabulation();

	file << "<" << tag->getName();

	for (const auto& param : tag->getParams())
		file << " " << param.first << "="
				<< ((param.second.find_first_of(" ") == std::string::npos && param.second.find_first_of("\n") == std::string::npos
						&& param.second.find_first_of("\t") == std::string::npos) ? param.second : "\"" + param.second + "\"");

	if (tag->getChilds().size() == 0)
		file << "/>\n";
	else {
		file << ">\n";

		for (const auto& child : tag->getChilds())
			writeSubTag(file, child);

		file.writeTabulation();

		file << "</" << tag->getName() << ">\n";
	}

	if (!root)
		file.decrementTabulation();
}

}
/* namespace xml */
} /* namespace utils */
