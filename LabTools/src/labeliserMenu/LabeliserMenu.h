/*
 * LabeliserMenu.h
 *
 *  Created on: 8 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_LABELISERMENU_LABELISERMENU_H_
#define SRC_LABELISERMENU_LABELISERMENU_H_

#include <memory>
#include <string>

namespace window {
class SplitLayer;
class Button;
class TextLayer;
class Window;
} /* namespace window */

namespace window {

class LabeliserMenu {
public:
	bool exitAutomaticMode = false;

	virtual ~LabeliserMenu();
	static std::shared_ptr<LabeliserMenu> create(std::shared_ptr<SplitLayer>& splitLayerBottom,
			const std::shared_ptr<window::SplitLayer>& splitLayerPlot, const std::shared_ptr<Button>& validate,
			const std::shared_ptr<Button>& cancel, Window& window);

	void firstLabelisation();
	void labelise();
	void applyChanges();
	void update(unsigned int frame);
	void disable();
	void enable();
	void setText(const std::string& text);
	const std::string& getText() const;
	void startAutomaticMode();
	void stopAutomaticMode();
	bool isAutomaticModeEnable() const;
	bool isFirstLabelisation() const;
	bool isInLabelisation() const;
	void abordLabelisation();
	void emptyCurves();

private:
	LabeliserMenu(const std::shared_ptr<Button>& emptyCurves, const std::shared_ptr<Button>& makeFirst, const std::shared_ptr<Button>& autoMode,
			const std::shared_ptr<Button>& labeliseMissingPoints, const std::shared_ptr<Button>& stop,
			const std::shared_ptr<TextLayer>& text, Window& window);
	Window& window;
	std::shared_ptr<Button> emptyCurvesBtn;
	std::shared_ptr<Button> makeFirst;
	std::shared_ptr<Button> autoMode;
	std::shared_ptr<Button> labeliseMissingPoints;
	std::shared_ptr<Button> stop;
	std::shared_ptr<TextLayer> textLayer;
	bool firstLabelisationFlag = true;
	bool autoValidation = false;
	bool inLabelisation = false;
	bool isWaitingFlag = false;
	bool ended = false;

	void setAutomaticMode(bool flag = true);
};

} /* namespace window */

#endif /* SRC_LABELISERMENU_LABELISERMENU_H_ */
