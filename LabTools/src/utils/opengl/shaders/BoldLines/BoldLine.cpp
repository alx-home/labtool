/*
 * BoldLine.cpp
 *
 *  Created on: 21 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include "BoldLine.h"
/*
#include <stddef.h>
#include <exception>
#include <iostream>

namespace utils {
namespace opengl {
namespace shaders {

std::unique_ptr<BoldLine::Instance> BoldLine::instance;

std::array<char, PIXEL_SHADER_SIZE> BoldLine::pixelSrc = { PIXEL_SHADER_CONTENT };

BoldLine::Instance::Instance() {
	try {
		if (!GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader) {
			std::cerr << "Error : fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
			throw std::exception(); //todo exception
		}

		program = glCreateProgram();

		loadShader(pixelShader, program, &pixelSrc[0], GL_FRAGMENT_SHADER);

		glLinkProgram(program);

		GLint status = GL_TRUE;

		glGetProgramiv(program, GL_LINK_STATUS, &status);

		if (status != GL_TRUE) {
			GLint logsize;
			std::cerr << "Error : fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << "\n";

			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logsize);

			char logInfo[logsize + 1];

			glGetProgramInfoLog(program, logsize, &logsize, logInfo);

			std::cerr << logInfo << std::endl;

			throw std::exception(); //todo exception
		}
	} catch (const std::exception& e) {
		if (pixelShader != 0) {
			pixelShader = 0;

			glDeleteShader(pixelShader);
			glDetachShader(program, pixelShader);
		}
		throw e;
	}
}

void BoldLine::Instance::loadShader(GLuint& shader, GLuint& program, char* srcPtr, GLuint type) {
	shader = glCreateShader(type);

	if (shader == 0) {
		std::cerr << "Error : fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
		throw std::exception(); //todo exception
	}

	glShaderSource(shader, 1, &srcPtr, NULL);
	glCompileShader(shader);

	GLint status = GL_TRUE;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		GLint logsize;
		std::cerr << "Error : fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << "\n";

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);

		char logInfo[logsize + 1];

		glGetShaderInfoLog(shader, logsize, &logsize, logInfo);

		std::cerr << logInfo << std::endl;

		throw std::exception(); //todo exception
	}

	glAttachShader(program, shader);
}

void BoldLine::init() {
	if (instance == nullptr) {
		class make_unique_enabler: public BoldLine::Instance {
		public:
			make_unique_enabler() {
			}

			~make_unique_enabler() {
			}
		};

		instance = std::unique_ptr<BoldLine::Instance>(new make_unique_enabler());
	}
}

void BoldLine::unuseShader() {
	glUseProgram(0);
}

void BoldLine::useShader() {
	glUseProgram(instance->program);
}

GLuint BoldLine::getProgram() {
	return instance->program;
}

BoldLine::Instance::~Instance() {
	if (program != 0) {
		program = 0;

		glDeleteProgram(program);
	}

	if (pixelShader != 0) {
		pixelShader = 0;

		glDeleteShader(pixelShader);
		glDetachShader(program, pixelShader);
	}
}

} /* namespace shaders *//*
} /* namespace opengl *//*
} /* namespace utils */
