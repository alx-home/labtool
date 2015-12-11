/*
 * LoadFileException.h
 *
 *  Created on: 16 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_OPENGL_EXCEPTION_LOADTEXTUREEXCEPTION_H_
#define SRC_UTILS_OPENGL_EXCEPTION_LOADTEXTUREEXCEPTION_H_

#include <cstddef>
#include <exception>
#include <string>

namespace utils {
namespace opengl {
namespace exceptions {

class LoadTextureException: public std::exception {
public:
	LoadTextureException(const std::string& textureName, const std::string& file, int line);
	virtual ~LoadTextureException();

	const char* what() const _GLIBCXX_USE_NOEXCEPT override;

private:
	std::string textureName;
	std::string file;
	int line;
};

} /* namespace exceptions */
} /* namespace opengl */
} /* namespace utils */

#endif /* SRC_UTILS_OPENGL_EXCEPTION_LOADTEXTUREEXCEPTION_H_ */
