/*
 * Drawable.cpp
 *
 *  Created on: 6 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "Draw.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <iostream>

#include "../math/math.h"
#include "exception/LoadTextureException.h"

namespace utils {
namespace opengl {

std::unordered_map<unsigned int, std::vector<::Vector3d>> Draw::sphereVertices;

void Draw::drawCube(const sf::Color& color) {
	glPushMatrix();
	{
		glRotatef(-90.0f, 1.f, 0.f, 0.f);

		drawCubeFace(color);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glRotatef(180.0f, 0.f, 0.f, 1.f);

		drawCubeFace(color);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glRotatef(90.0f, 0.f, 0.f, 1.f);

		drawCubeFace(color);
	}
	glPopMatrix();

	glPushMatrix();
	{
		drawCubeFace(color);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glRotatef(-90.0f, 0.f, 0.f, 1.f);

		drawCubeFace(color);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glRotatef(90.0f, 1.f, 0.f, 0.f);

		drawCubeFace(color);
	}
	glPopMatrix();
}

void Draw::drawSphere(const sf::Color& color, unsigned int resolution, bool fond) {
	if (resolution > 100)
		resolution = 100;

	const auto& it = sphereVertices.find(resolution);

	if (it == sphereVertices.end()) {
		auto& vertices = sphereVertices[resolution];
		float dTheta = M_PI / resolution;

		for (unsigned int j = 0; j < resolution; ++j)
			for (unsigned int i = 0; i < resolution; ++i) {
				float theta = 2.f * dTheta * i;
				float psi = dTheta * j;

				vertices.push_back(Vector3d(std::array<double, 3> { sin(psi) * cos(theta), sin(theta) * sin(psi), cos(psi) }));
				theta += 2.f * dTheta;
				vertices.push_back(Vector3d(std::array<double, 3> { sin(psi) * cos(theta), sin(theta) * sin(psi), cos(psi) }));
				psi += dTheta;
				vertices.push_back(Vector3d(std::array<double, 3> { sin(psi) * cos(theta), sin(theta) * sin(psi), cos(psi) }));
				theta -= 2.f * dTheta;
				vertices.push_back(Vector3d(std::array<double, 3> { sin(psi) * cos(theta), sin(theta) * sin(psi), cos(psi) }));
			}
	} else {
		auto& vertices = it->second;
		float dTheta = M_PI / resolution;

		glPushMatrix();
		{
			for (unsigned int i = 0; i < resolution; ++i)
				for (unsigned int j = 0; j < resolution; ++j) {
					auto& vertice = vertices[(i * resolution + j) * 4];

					if (fond) {
						glBegin(GL_QUADS);
						{
							glColor4ub(color.r, color.g, color.b, color.a);

							glVertex3d(vertice[0], vertice[1], vertice[2]);
							vertice = vertices[(i * resolution + j) * 4 + 1];
							glVertex3d(vertice[0], vertice[1], vertice[2]);
							vertice = vertices[(i * resolution + j) * 4 + 2];
							glVertex3d(vertice[0], vertice[1], vertice[2]);
							vertice = vertices[(i * resolution + j) * 4 + 3];
							glVertex3d(vertice[0], vertice[1], vertice[2]);
						}
						glEnd();
					}
					glLineWidth(1.f);

					glBegin(GL_LINES);
					{
						glColor4ub(0.f, 0.f, 0.f, color.a);

						vertice = vertices[(i * resolution + j) * 4];
						glVertex3d(vertice[0], vertice[1], vertice[2]);
						vertice = vertices[(i * resolution + j) * 4 + 1];
						glVertex3d(vertice[0], vertice[1], vertice[2]);

						vertice = vertices[(i * resolution + j) * 4 + 1];
						glVertex3d(vertice[0], vertice[1], vertice[2]);
						vertice = vertices[(i * resolution + j) * 4 + 2];
						glVertex3d(vertice[0], vertice[1], vertice[2]);

						vertice = vertices[(i * resolution + j) * 4 + 2];
						glVertex3d(vertice[0], vertice[1], vertice[2]);
						vertice = vertices[(i * resolution + j) * 4 + 3];
						glVertex3d(vertice[0], vertice[1], vertice[2]);

						vertice = vertices[(i * resolution + j) * 4 + 3];
						glVertex3d(vertice[0], vertice[1], vertice[2]);
						vertice = vertices[(i * resolution + j) * 4];
						glVertex3d(vertice[0], vertice[1], vertice[2]);
					}
					glEnd();
				}
		}
		glPopMatrix();
	}
}

void Draw::drawCubeFace(const sf::Color& color) {
	glBegin(GL_QUADS);
	{
		glColor4ub(color.r, color.g, color.b, color.a);
		glVertex3d(1.f, 1.f, 1.f);
		glVertex3d(1.f, 1.f, -1.f);
		glVertex3d(-1.f, 1.f, -1.f);
		glVertex3d(-1.f, 1.f, 1.f);
	}
	glEnd();

	glLineWidth(1.f);

	glBegin(GL_LINES);
	{
		glColor4ub(0.f, 0.f, 0.f, color.a);

		glVertex3d(1.f, 1.f, 1.f);
		glVertex3d(1.f, 1.f, -1.f);
		glVertex3d(1.f, 1.f, -1.f);
		glVertex3d(-1.f, 1.f, -1.f);
		glVertex3d(-1.f, 1.f, -1.f);
		glVertex3d(-1.f, 1.f, 1.f);
		glVertex3d(-1.f, 1.f, 1.f);
		glVertex3d(1.f, 1.f, 1.f);
	}
	glEnd();
}

GLuint Draw::loadTexture(const std::string& filename) {
	GLuint texture_handle;

	sf::Image img;

	if (!img.loadFromFile(filename))
		throw exceptions::LoadTextureException(filename, __FILE__, __LINE__);

	glGenTextures(1, &texture_handle);
	glBindTexture(GL_TEXTURE_2D, texture_handle);
	glTexImage2D(
	GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0,
	GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return texture_handle;
}

void Draw::draw2Dshape(const sf::RenderTexture& textureOut, sf::Window& window, float x, float y, float width, float height) {
	try {
		window.setActive(true);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		{
			glLoadIdentity();

			glOrtho(0, 0, width, height, -1.0, 1.0);

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			{
				glViewport(x, window.getSize().y - (height + y), width, height);

				glLoadIdentity();
				glEnable(GL_TEXTURE_2D);
				sf::Texture::bind(&textureOut.getTexture());

				glColor3f(255, 255, 255);

				glBegin(GL_QUADS);
				{
					glTexCoord2d(0, 0);
					glVertex2d(-1.f, 1.f);

					glTexCoord2d(1, 0);
					glVertex2d(1.f, 1.f);

					glTexCoord2d(1, 1);
					glVertex2d(1.f, -1.f);

					glTexCoord2d(0, 1);
					glVertex2d(-1.f, -1.f);
				}
				glEnd();

				glDisable(GL_TEXTURE_2D);
				sf::Texture::bind(NULL);
			}
			glPopMatrix();

			glMatrixMode(GL_PROJECTION);
		}
		glPopMatrix();
	} catch (...) {
		std::cerr << "Error: fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
	}
}

} /* namespace opengl */
} /* namespace utils */
