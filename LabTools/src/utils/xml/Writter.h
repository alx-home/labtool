/*
 * Writter.h
 *
 *  Created on: 29 déc. 2015
 *      Author: alex
 */

#ifndef SRC_UTILS_XML_WRITTER_H_
#define SRC_UTILS_XML_WRITTER_H_

#include <fstream>
#include <memory>
#include <string>

namespace utils {
namespace xml {
class RootTag;
class Tag;
} /* namespace xml */
} /* namespace utils */

namespace utils {
namespace xml {

class Writter {
public:
	class File: public std::ofstream {
	public:
		File(const std::string& filePath);
		virtual ~File();

		void incrementTabulation();
		void decrementTabulation();
		void writeTabulation();

	private:
		unsigned int tabulationOffset = 0;
	};

	static void write(const std::string& path, const std::shared_ptr<RootTag>&);
	static void writeSubTag(File& file, const std::shared_ptr<Tag>&, bool root = false);

private:
	Writter() = delete;
	virtual ~Writter() = delete;
};

} /* namespace xml */
} /* namespace utils */

#endif /* SRC_UTILS_XML_WRITTER_H_ */
