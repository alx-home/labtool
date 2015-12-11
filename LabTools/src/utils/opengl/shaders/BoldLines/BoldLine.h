/*
 * BoldLine.h
 *
 *  Created on: 21 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_OPENGL_SHADERS_BOLDLINES_BOLDLINE_H_
#define SRC_UTILS_OPENGL_SHADERS_BOLDLINES_BOLDLINE_H_
/*
#include <GL/glew.h>
#include <array>
#include <memory>
#include "PixelShader.h"

namespace utils {
namespace opengl {
namespace shaders {

class BoldLine {
public:
	BoldLine() = delete;
	virtual ~BoldLine() = delete;

	static void useShader();
	static void unuseShader();
	static void init();
	static GLuint getProgram ();

	class Instance {
	public:
		GLuint pixelShader = 0;
		GLuint program = 0;

	protected:
		Instance();
		void loadShader(GLuint& shader, GLuint& program, char* srcPtr, GLuint type);
	public:
		virtual ~Instance();
	};

private:
	static std::array<char, PIXEL_SHADER_SIZE> pixelSrc;
	static std::unique_ptr<Instance> instance;
};

} /* namespace shaders *//*
} /* namespace opengl *//*
} /* namespace utils */

#endif /* SRC_UTILS_OPENGL_SHADERS_BOLDLINES_BOLDLINE_H_ */
