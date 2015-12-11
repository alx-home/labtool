/*
 * Editor.h
 *
 *  Created on: 8 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EDITOR_EDITOR_H_
#define SRC_EDITOR_EDITOR_H_

#include <limits>
#include <memory>
#include <queue>
#include <vector>

#include "../utils/opengl/ColorPicker.h"

namespace utils {
namespace Editor {
class Event;
} /* namespace Editor */
} /* namespace utils */

namespace window {
class Button;
class ConstrainedLayer;
class Window;
class SplitLayer;
class SplitBar;
} /* namespace window */

namespace window {
/**
 * @class Editor
 * @author Alexandre GARCIN
 * @date 8 déc. 2015
 *
 * @brief permet de gérer les éditions depuis le GUI (menu de droite lorsqu'un point est séléctionné)
 */
class Editor {
public:
	/**
	 * @enum SplitType
	 * @brief parametre pour le découpage des points
	 * @see splitPoints()
	 */
	typedef enum {
		Previous /** découper jusqu'à la frame précédante **/, Next /** découper à partir de la frame suivante **/, Selection /** découper les frames séléctionnées **/
	} SplitType;

	virtual ~Editor();

	/**
	 * @brief constructeur
	 *
	 * @param[out] splitLayerButtonsRight layer de découpage comportant l'éditeur à droite et le plot3d à gauche
	 * @param[in] window line vers la classe principale du GUI
	 *
	 * @return l'éditeur ainsi créé
	 */
	static std::shared_ptr<Editor> create(std::shared_ptr<window::SplitLayer>& splitLayerButtonsRight, Window& window);

	/**
	 *  @brief permet de mettre à jour le menu d'édition.
	 *  à executer à chaque fois que le selecteur est modifier ou qu'un des points du plot3d est changer
	 */
	void update();

	/**
	 * @brief permet de délabelliser entierement un point
	 */
	void erasePoint();

	/**
	 *
	 * @param type
	 */
	void splitPoints(SplitType type);

	/**
	 *
	 */
	void renamePoint();

	/**
	 *
	 */
	void unlinkPoints();

	/**
	 *
	 */
	void linkPoints();

	/**
	 *
	 */
	void addMarkersToGroups();

	/**
	 *
	 */
	void setMarkerGroupMargin();

	/**
	 *
	 */
	void removeMarkersFromGroups();

	/**
	 *
	 */
	void removeMarkerGroups();

	/**
	 *
	 */
	void createGroupFromMarkers();

	/**
	 *
	 * @return
	 */
	Window& getWindow() const;

	/**
	 *
	 */
	void disable();

	/**
	 *
	 */
	void enable();

	/**
	 *
	 * @param flag
	 */
	void setInEdition(bool flag = true);

	/**
	 *
	 * @return
	 */
	const std::queue<std::shared_ptr<utils::Editor::Event>>& getEvents() const;

	/**
	 *
	 */
	void applyEvents();

	/**
	 *
	 */
	void updateCurves();

	/**
	 *
	 * @return
	 */
	unsigned int getFirstSelection() const;

	/**
	 *
	 * @return
	 */
	unsigned int getLastSelection() const;

	/**
	 *
	 * @param
	 */
	void setFirstSelection(unsigned int);

	/**
	 *
	 * @param
	 */
	void setLastSelection(unsigned int);

private:
	std::shared_ptr<Button> eraseMarkers;
	std::shared_ptr<Button> renameMarker;
	std::shared_ptr<Button> linkMarkers;
	std::shared_ptr<Button> unlinkMarkers;
	std::shared_ptr<Button> splitSelectedFrames;
	std::shared_ptr<Button> splitPreviousFrames;
	std::shared_ptr<Button> splitNextFrames;
	std::shared_ptr<Button> setMarkerGroupMarginButton;
	std::shared_ptr<Button> addMarkersToGroupsButton;
	std::shared_ptr<Button> removeMarkersFromGroupsButton;
	std::shared_ptr<Button> removeMarkerGroupsButton;
	std::shared_ptr<Button> createGroupFromMarkersButton;
	std::shared_ptr<window::SplitBar> groupsSplitBar;
	std::queue<std::shared_ptr<utils::Editor::Event>> events = std::queue<std::shared_ptr<utils::Editor::Event>>();
	Window& window;
	std::shared_ptr<std::vector<std::shared_ptr<window::ConstrainedLayer> > > stackLayers;
	bool isDisable = false;
	ColorPicker curveColors = ColorPicker();
	unsigned int firstSelection = std::numeric_limits<unsigned int>::max();
	unsigned int lastSelection = std::numeric_limits<unsigned int>::max();

	Editor(const std::shared_ptr<Button>& splitSelectedFrames, const std::shared_ptr<Button>& splitNextFrames,
			const std::shared_ptr<Button>& splitPreviousFrames, const std::shared_ptr<Button>& eraseMarker,
			const std::shared_ptr<Button>& renameMarker, const std::shared_ptr<Button>& linkMarkers,
			const std::shared_ptr<Button>& unlinkMarkers, const std::shared_ptr<Button>& setMarkerGroupMargin,
			const std::shared_ptr<Button>& addMarkersToGroups, const std::shared_ptr<Button>& removeMarkersFromGroups,
			const std::shared_ptr<Button>& removeMarkerGroups, const std::shared_ptr<Button>& createGroupFromMarkers,
			const std::shared_ptr<std::vector<std::shared_ptr<window::ConstrainedLayer> > >& stackLayers,
			const std::shared_ptr<window::SplitBar>& groupsSplitBar, Window& window);
	void updateLabelsText();
};

} /* namespace window */

#endif /* SRC_EDITOR_EDITOR_H_ */
