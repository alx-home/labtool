/*
 * Point.cpp
 *
 *  Created on: 5 nov. 2015
 *      Author: Alexandre GARCIN
 */

#include "Point.h"

#include <GL/glew.h>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iterator>

#include "../../../../../utils/opengl/Draw.h"
#include "../../../../Window.h"
#include "../line/Line.h"
#include "../Plot3d.h"

namespace utils {

Point::Point(const Vector3d& position, const sf::Color& color, float size, std::string label,
		const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack) :
		color(color), size(size), position(position), callBack(callBack), label(label) {
}

Point::Point(double x, double y, double z, const sf::Color& color, float size, std::string label,
		const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& callBack) :
		color(color), size(size), position( { x, y, z }), callBack(callBack), label(label) {

}

Point::~Point() {
}

void Point::set2DColor(const sf::Color& color) {
	color2d = color;
}

void Point::linkPointTo(const std::shared_ptr<Point>& point, const sf::Color& linkColor, float linkSize,
		const std::shared_ptr<Line>& line) {
	for (auto lineIt : lines)
		if (point == lineIt->getPointA() || point == lineIt->getPointB())
			return;

	lines.push_back(line);
}

void Point::unlinkPointTo(const Line& line) {
	for (auto lineIt = lines.begin(); lineIt != lines.end(); ++lineIt)
		if (lineIt->get() == &line) {
			lines.erase(lineIt);
			break;
		}
}

void Point::unlinkPoint() {
	for (auto line = lines.end() - 1; line != lines.begin() - 1; --line)
		(*line)->clear();
}

void Point::setError(bool flag) {
	error = flag;
}

void Point::clear() {
	unlinkPoint();

	suppressed = true;
}

bool Point::isSuppressed() {
	return suppressed;
}

bool Point::isSelected() {
	return selected;
}

void Point::setLabel(const std::string& label) {
	if (!label.size())
		return;

	this->label = label;
}

void Point::display() {
	displayFlag = true;
}

void Point::hide() {
	displayFlag = false;
}

bool Point::isDisplayed() const {
	return displayFlag;
}

bool Point::isSelectable() {
	return true;
}

void Point::displayLabel() {
	showLabel = true;
}

void Point::setLabelDrawer(const std::function<void(const std::shared_ptr<sf::RenderTexture>&, float& width, float& height)>& labelDrawer) {
	this->labelDrawer = labelDrawer;
}

void Point::addColorMask(ColorMask mask) {
	auto& masks = colorMasks[mask.getPriority()];

	for (const auto& maskIt : masks)
		if (maskIt.getId() == mask.getId())
			return;

	masks.push_back(mask);
}

void Point::removeColorMask(ColorMask mask) {
	try {
		auto& masks = colorMasks.at(mask.getPriority());

		for (auto maskIt = masks.begin(); maskIt != masks.end(); ++maskIt)
			if (maskIt->getId() == mask.getId()) {
				masks.erase(maskIt);

				if (masks.size() == 0)
					colorMasks.erase(mask.getPriority());
				return;
			}
	} catch (...) {
	}
}

void Point::clearColorMasks() {
	colorMasks.clear();
}

void Point::hideLabel() {
	showLabel = false;
}

bool Point::isLabelEnable() const {
	return showLabel;
}

void Point::draw2d(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) const {
	if (!displayFlag)
		return;

	sf::RectangleShape rec;
	constexpr float size = 2.5f;
	constexpr float demiSize = size / 2.f;

	rec.setSize(sf::Vector2f(size, size));
	rec.setPosition(x - demiSize, y - demiSize);
	rec.setFillColor(color2d);
	window->draw(rec);
}

void Point::draw3d() const {
	if (!displayFlag)
		return;

	glPushMatrix();
	{
		glTranslated(position[0], position[1], position[2]);

		glPushMatrix();
		{
			glScalef(size, size, size);

			if (color.a != 255)
				glDepthMask(GL_FALSE);

			utils::opengl::Draw::drawCube(color);

			if (lines.size() > 1 || error) {
				constexpr float sizeErrorFactor = 2.f;
				glPushMatrix();
				glScalef(sizeErrorFactor, sizeErrorFactor, sizeErrorFactor);
				utils::opengl::Draw::drawCube(window::Window::errorPoint);
			}

			float sizeSelecFactor = 0.f;

			glPushMatrix();
			{
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);

				for (const auto& masks : colorMasks)
					for (const auto& mask : masks.second) {
						glPushMatrix();

						sizeSelecFactor += 0.002f;
						float factor = (sizeSelecFactor + size) / size;

						glScalef(factor, factor, factor);

						utils::opengl::Draw::drawCube(mask.getColor());
						glPopMatrix();
					}

				glDisable(GL_CULL_FACE);
			}
			glPopMatrix();

			if (selected) {
				glPushMatrix();
				{
					float factor = (0.004f + sizeSelecFactor + size) / size;
					glScalef(factor, factor, factor);
					utils::opengl::Draw::drawCube(window::Window::selectColorPoint);
				}
				glPopMatrix();
			}

			if (lines.size() > 1 || error)
				glPopMatrix();

			glDepthMask(GL_TRUE);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void Point::drawLabel(const std::shared_ptr<sf::RenderTarget>& window, ::Vector3d cameraRight, ::Vector3d cameraUp, float width, float height) const {
	if (!displayFlag)
		return;

	static class RenderTextureProxy {
	public:
		RenderTextureProxy() {
			renderTexture->create(widthMax, heightMax);
			renderTexture->setSmooth(true);
		}

		virtual ~RenderTextureProxy() {
		}

		std::shared_ptr<sf::RenderTexture> renderTexture = std::make_shared<sf::RenderTexture>();
		const float widthMax = 200.f;
		const float heightMax = 200.f;
	} renderTextureProxy;

	float labelWidth = renderTextureProxy.widthMax;
	float labelHeight = renderTextureProxy.heightMax;

	renderTextureProxy.renderTexture->setActive(true);
	renderTextureProxy.renderTexture->clear(sf::Color(0, 0, 0, 0));

	try {
		labelDrawer(renderTextureProxy.renderTexture, labelWidth, labelHeight);
	} catch (const exception::EmptyLabelDrawerFunctionException&) {
		if (std::dynamic_pointer_cast<sf::RenderWindow>(window) != nullptr)
			std::static_pointer_cast<sf::RenderWindow>(window)->setActive(true);
		else if (std::dynamic_pointer_cast<sf::RenderTexture>(window) != nullptr)
			std::static_pointer_cast<sf::RenderTexture>(window)->setActive(true);

		return;
	}

	renderTextureProxy.renderTexture->display();

	if (std::dynamic_pointer_cast<sf::RenderWindow>(window) != nullptr)
		std::static_pointer_cast<sf::RenderWindow>(window)->setActive(true);
	else if (std::dynamic_pointer_cast<sf::RenderTexture>(window) != nullptr)
		std::static_pointer_cast<sf::RenderTexture>(window)->setActive(true);

	float constexpr invFact = 1.f / 1000.f;

	float widthRatio = labelWidth * invFact;
	float heightRatio = labelHeight * invFact;

	cameraRight *= widthRatio;
	cameraUp *= -heightRatio;
	::Vector3d diag = cameraRight + cameraUp;

	glPushMatrix();
	{
		glTranslated(position[0], position[1], position[2]);

		glEnable(GL_TEXTURE_2D);
		sf::Texture::bind(&renderTextureProxy.renderTexture->getTexture(), sf::Texture::Pixels);

		glColor3f(255, 255, 255);

		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, labelHeight);
			glVertex3d(cameraUp[0], cameraUp[1], cameraUp[2]);

			glTexCoord2f(labelWidth, labelHeight);
			glVertex3d(diag[0], diag[1], diag[2]);

			glTexCoord2f(labelWidth, 0);
			glVertex3d(cameraRight[0], cameraRight[1], cameraRight[2]);

			glTexCoord2f(0, 0);
			glVertex3d(0.f, 0.f, 0.f);
		}
		glEnd();

		sf::Texture::bind(NULL);
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}

void Point::setColor(sf::Color color) {
	this->color = color;
}

sf::Color Point::getColor() const {
	return color;
}

const std::vector<std::shared_ptr<Line> >& Point::getLines() const {
	return lines;
}

const std::shared_ptr<std::function<void(const sf::Event&, bool)>>& Point::getCallBack() const {
	return callBack;
}

void Point::setCallBack(const std::shared_ptr<std::function<void(const sf::Event&, bool)> >& callBack) {
	this->callBack = callBack;
}

const std::string& Point::getLabel() const {
	return this->label;
}

void Point::setLines(const std::vector<std::shared_ptr<Line> >& lines) {
	this->lines = lines;
}

const Vector3d& Point::getPosition() const {
	return position;
}

void Point::setPosition(const Vector3d& position) {
	this->position = position;
}

float Point::getSize() const {
	return size;
}

void Point::setSize(float size) {
	this->size = size;
}

} /* namespace plot */
