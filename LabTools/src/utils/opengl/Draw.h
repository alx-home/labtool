/*
 * Drawable.h
 *
 *  Created on: 6 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_OPENGL_DRAW_H_
#define SRC_UTILS_OPENGL_DRAW_H_

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "../math/Vector.h"

namespace sf {
class Color;
class RenderTexture;
class Window;
} /* namespace sf */

namespace utils {
namespace opengl {

class Draw {
public:
	static void drawCube(const sf::Color& color);
	static void drawSphere(const sf::Color& color, unsigned int resolution, bool fond = true);
	static void drawCubeFace(const sf::Color& color);
	static GLuint loadTexture(const std::string& filename);
	static void draw2Dshape(const sf::RenderTexture& textureOut, sf::Window& window, float x, float y, float width, float height);

	static std::unordered_map<unsigned int, std::vector<::Vector3d>> sphereVertices;
};

} /* namespace opengl */
} /* namespace utils */

#endif /* SRC_UTILS_OPENGL_DRAW_H_ */
