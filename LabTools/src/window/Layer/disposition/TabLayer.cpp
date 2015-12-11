/*
 * TabLayer.cpp
 *
 *  Created on: 10 févr. 2016
 *      Author: Alexandre GARCIN
 */

#include "TabLayer.h"

#include <functional>
#include <utility>

#include "../content/Buttons/Button.h"
#include "ConstrainedLayer.h"

namespace window {

TabLayer::TabLayer(Disposition tabDisposition, const uint8_t& borders,
		const std::map<std::string, std::vector<std::shared_ptr<Layer>> >& layers) :
		tabDisposition(tabDisposition), layers(layers), Layer(borders) {

	for (const auto& layerIt : layers) {
		auto& buttonsIt = tabButtons[layerIt.first];

		for (auto layer : layerIt.second) {
			std::shared_ptr<Button> button;
			buttonsIt.push_back(button = std::make_shared<Button>(true, layerIt.first, 20));

			button->setCallBack([this, button, layer](float) {
				for (auto buttonIt : tabButtons)
				for (auto it : buttonIt.second)
				it->enable();

				button->disable();

				activeLayer = layer;
			});

			tabStacks->push_back(std::make_shared<ConstrainedLayer>(button->getTextWidth() + 20.f, 20.f, button));
		}
	}

	tabButtons.begin()->second.front()->disable();
	activeLayer = layers.begin()->second.front();
}

TabLayer::~TabLayer() {
}

void TabLayer::setActiveLayer(const std::string& name, unsigned short pos) {
	tabButtons.at(name)[0]->getCallBack()(1.f);
}

void TabLayer::draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) {
	Layer::draw(window, x, y, width, height);

	float tabSize = tabsStack.getHeight(x, y, width, height);

	switch (tabDisposition) {
	case Top:
		tabsStack.draw(window, x, y, width, height);
		activeLayer->draw(window, x, y + tabSize, width, height - tabSize);
		break;

	default:
		tabsStack.draw(window, x, y + height - tabSize, width, height);
		activeLayer->draw(window, x, y, width, height - tabSize);
		break;
	}
}

void TabLayer::update() {
	activeLayer->update();
}

const std::shared_ptr<Layer>& TabLayer::getActiveLayer() const {
	return activeLayer;
}

void TabLayer::pollEvent(const sf::Event& event, float x, float y, float width, float height) {
	float tabSize = tabsStack.getHeight(x, y, width, height);

	switch (tabDisposition) {
	case Top:
		tabsStack.pollEvent(event, x, y, width, height);
		activeLayer->pollEvent(event, x, y + tabSize, width, height - tabSize);
		break;

	default:
		tabsStack.pollEvent(event, x, y + height - tabSize, width, height);
		activeLayer->pollEvent(event, x, y, width, height - tabSize);
		break;
	}
}

} /* namespace window */
