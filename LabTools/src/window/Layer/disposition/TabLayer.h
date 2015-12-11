/*
 * TabLayer.h
 *
 *  Created on: 10 févr. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_LAYER_DISPOSITION_TABLAYER_H_
#define SRC_WINDOW_LAYER_DISPOSITION_TABLAYER_H_

#include <cstdint>
#include <memory>
#include <string>
#include <map>
#include <vector>

#include "StakeLayer.h"

namespace window {
class Button;
} /* namespace window */

namespace window {

class TabLayer: public Layer {
public:
	typedef enum {
		Top, Bottom
	} Disposition;

	TabLayer(Disposition tabDisposition, const uint8_t& borders,
			const std::map<std::string, std::vector<std::shared_ptr<Layer> > >& layers);
	virtual ~TabLayer();

	void draw(const std::shared_ptr<sf::RenderTarget>& window, float x, float y, float width, float height) override;
	void update() override;
	void pollEvent(const sf::Event& event, float x, float y, float width, float height) override;
	const std::shared_ptr<Layer>& getActiveLayer() const;
	void setActiveLayer(const std::string& name, unsigned short pos);

private:
	Disposition tabDisposition;
	std::map<std::string, std::vector<std::shared_ptr<Layer> > > layers;
	std::map<std::string, std::vector<std::shared_ptr<Button> > > tabButtons = std::map<std::string,
			std::vector<std::shared_ptr<Button> > >();
	std::shared_ptr<std::vector<std::shared_ptr<ConstrainedLayer> > > tabStacks = std::make_shared<
			std::vector<std::shared_ptr<ConstrainedLayer> > >();
	std::shared_ptr<Layer> activeLayer = nullptr;
	StakeLayer tabsStack = StakeLayer(0, tabStacks);
};

} /* namespace window */

#endif /* SRC_WINDOW_LAYER_DISPOSITION_TABLAYER_H_ */
