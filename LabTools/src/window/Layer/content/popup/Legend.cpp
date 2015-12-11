/*
 * Legend.cpp
 *
 *  Created on: 21 déc. 2015
 *      Author: alex
 */

#include "Legend.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "../../../../utils/opengl/FontLoader.h"
#include "../../../Window.h"
#include "../../Layer.h"
#include "../plot/point/Point.h"

namespace window {

Legend::Legend(float x, float y, float width, float height) :
		x(x), y(y), width(width), height(height), Layer(Layer::AllBorders), plot(Vector3d( { sqrt(2.) / 2., sqrt(2.) / 2., 0.0 }) * 12.5,
				Vector3d::center, 0.f, 0.f, 0.f, sf::Color::White, 0) {
	plot.hideAxis();
	plot.addPointToPlot(std::make_shared<utils::DefaultPoint>(0.f, 0.f, 0.67f, window::Window::labellisedColor, 0.08f));
	plot.addPointToPlot(std::make_shared<utils::DefaultPoint>(0.f, 0.f, 0.4f, window::Window::outlierColor, 0.05f));
	plot.addPointToPlot(std::make_shared<utils::DefaultPoint>(0.f, 0.f, 0.15f, window::Window::sceneColor, 0.05f));
	plot.addPointToPlot(std::make_shared<utils::DefaultPoint>(0.f, 0.f, -0.15f, window::Window::modelColor, 0.05f));
	plot.addPointToPlot(std::make_shared<utils::DefaultPoint>(0.f, 0.f, -0.45f, window::Window::incompletePointColor, 0.05f));
	plot.addPointToPlot(std::make_shared<utils::DefaultPoint>(0.f, 0.f, -0.7f, window::Window::newlySuppressedColorPoint, 0.08f));
}

Legend::~Legend() {
}

void Legend::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	if (hidded)
		return;

	static class TextProxy {
	public:
		sf::Text outlier;
		sf::Text labelised;
		sf::Text scene;
		sf::Text model;
		sf::Text incompletePoint;
		sf::Text newlySuppressed;

		TextProxy() :
				outlier(), labelised(), scene(), model(), newlySuppressed(), incompletePoint() {
			labelised.setFont(*utils::opengl::FontLoader::getArialFont());
			outlier.setFont(*utils::opengl::FontLoader::getArialFont());
			scene.setFont(*utils::opengl::FontLoader::getArialFont());
			model.setFont(*utils::opengl::FontLoader::getArialFont());
			incompletePoint.setFont(*utils::opengl::FontLoader::getArialFont());
			newlySuppressed.setFont(*utils::opengl::FontLoader::getArialFont());

			labelised.setCharacterSize(18);
			outlier.setCharacterSize(18);
			scene.setCharacterSize(18);
			model.setCharacterSize(18);
			incompletePoint.setCharacterSize(18);
			newlySuppressed.setCharacterSize(18);

			labelised.setColor(sf::Color(0, 0, 0));
			outlier.setColor(sf::Color(0, 0, 0));
			scene.setColor(sf::Color(0, 0, 0));
			model.setColor(sf::Color(0, 0, 0));
			incompletePoint.setColor(sf::Color(0, 0, 0));
			newlySuppressed.setColor(sf::Color(0, 0, 0));

			outlier.setString("Point supprimé lors d'une étape précédante");
			labelised.setString("Point en cours de Labelisation");
			scene.setString("Point de la scène");
			model.setString("Point du modèle");
			incompletePoint.setString("Point comportant des données incomplètes");
			newlySuppressed.setString("Point en cours de suppression");
		}

		virtual ~TextProxy() {
		}

	} textProxy;

	sf::RectangleShape rec;
	float yPos = y + height - this->height - 20.f;
	float xPos = x + 20.f;

	rec.setFillColor(sf::Color(255, 255, 255));
	rec.setSize(sf::Vector2f(this->width, this->height));
	rec.setPosition(sf::Vector2f(xPos, yPos));

	window->draw(rec);

	Layer::draw(window, xPos, yPos, this->width, this->height);

	float margin = 10.f;

	plot.draw(window, xPos + margin - this->width / 2.f + margin, yPos + margin - 4.f, this->width - 2.f * margin,
			this->height - 2.f * margin + 10.f);

	textProxy.labelised.setPosition(sf::Vector2f(std::floor(xPos + 20.f), std::floor(yPos + 8.f)));
	textProxy.outlier.setPosition(
			sf::Vector2f(std::floor(xPos + 20.f),
					std::floor(textProxy.labelised.getPosition().y + textProxy.labelised.getGlobalBounds().height + 3.f)));
	textProxy.scene.setPosition(
			sf::Vector2f(std::floor(xPos + 20.f),
					std::floor(textProxy.outlier.getPosition().y + textProxy.outlier.getGlobalBounds().height)));
	textProxy.model.setPosition(
			sf::Vector2f(std::floor(xPos + 20.f),
					std::floor(5.f + textProxy.scene.getPosition().y + textProxy.scene.getGlobalBounds().height)));
	textProxy.incompletePoint.setPosition(
			sf::Vector2f(std::floor(xPos + 20.f),
					std::floor(5.f + textProxy.model.getPosition().y + textProxy.model.getGlobalBounds().height)));
	textProxy.newlySuppressed.setPosition(
			sf::Vector2f(std::floor(xPos + 20.f),
					std::floor(textProxy.incompletePoint.getPosition().y + textProxy.incompletePoint.getGlobalBounds().height)));

	window->draw(textProxy.labelised);
	window->draw(textProxy.outlier);
	window->draw(textProxy.scene);
	window->draw(textProxy.model);
	window->draw(textProxy.incompletePoint);
	window->draw(textProxy.newlySuppressed);
}

void Legend::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
}

void Legend::update() {
}

bool Legend::grabEvent(const sf::Event& event, float x, float y, float width, float height) const {
	if (hidded)
		return false;

	float xPos = x + 20.f;
	float yPos = y + height - this->height - 20.f;

	switch (event.type) {
	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased:
		return event.mouseButton.x > xPos && event.mouseButton.x < xPos + this->width && event.mouseButton.y > yPos
				&& event.mouseButton.y < yPos + this->height;

	default:
		return false;
	}
}

void Legend::hide() {
	hidded = true;
}

void Legend::display() {
	hidded = false;
}

} /* namespace window */
