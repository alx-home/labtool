/*
 * Controller.h
 *
 *  Created on: 4 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include <climits>
#include <memory>

namespace window {
class Button;
class CenteredLayer;
class LabeliserMenu;
class StakeLayer;
class SplitLayer;
class Window;
} /* namespace window */

/**
 * @namespace window
 *
 * @brief namespace de toutes les classes... concernant le GUI
 */
namespace window {
/**
 * @class Controller
 *
 * @brief permet de gérer la frame actuelle du GUI (play/pause/...)
 * @author Alexandre GARCIN
 * @date 4 déc. 2015
 */
class Controller {
public:
	virtual ~Controller();

	/**
	 * @brief Permet de reculler de time frame
	 *
	 * @param time le nombre de frames
	 * @param bypassLock true pour reculer dans le temps même si le controller est vérouillé
	 */
	void goToPrev(float time = 0.f, bool bypassLock = false);

	/**
	 * @brief Permet d'avancer de time frame
	 *
	 * @param time le nombre de frames
	 * @param bypassLock true pour avancer dans le temps même si le controller est vérouillé
	 */
	void goToNext(float time = 0.f, bool bypassLock = false);

	/**
	 *	Permet d'acceder à la frame précédante qui n'a pas encore été labellisée
	 *
	 * @param time (deprecated)
	 * @param bypassLock true pour acceder à cette frame même si le controller est vérouillé
	 */
	void goToPrevLabelisationFrame(float time = 0.f, bool bypassLock = false);

	/**
	 * @brief Permet d'acceder à la frame suivante qui n'a pas encore été labellisée
	 *
	 * @param time (deprecated)
	 * @param bypassLock true pour acceder à cette frame même si le controller est vérouillé
	 */
	void goToNextLabelisationFrame(float time = 0.f, bool bypassLock = false);

	/**
	 * @brief Permet d'acceder à une frame en particulier
	 *
	 * @param frame la frame à laquelle acceder
	 * @param bypassLock true pour acceder à cette frame même si le controller est vérouillé
	 */
	void goTo(unsigned int frame, bool bypassLock = false);

	/**
	 * @return La frame à laquelle est actuellement situé le controller
	 */
	unsigned int getCurrentFrame() const;

	/**
	 * @return Le nombre de frames accessible totale (nombre de frames du nuage de point de la scène)
	 */
	unsigned int getNbFrames() const;

	/**
	 * @brief Permet de récuperer la frame de référence
	 *
	 * @return La frame à laquelle la première labellisation à été effectuée
	 */
	unsigned int getModelFrame() const;

	/**
	 * @brief Permet de définir la frame servant de référance (frame à laquelle la première labellisation à été effectuée)
	 *
	 * @param frame la frame de référance à définir
	 */
	void setModelFrame(unsigned int frame);

	/**
	 * @brief Play : permet de lancer le mode play du controler dans le sens direct
	 */
	void forwardRun();

	/**
	 * @brief Play : permet de lancer le mode play du controler dans le sens indirecte
	 */
	void backwardRun();

	/**
	 * @brief Pause : Permet d'arreter le mode play
	 */
	void stop();

	/**
	 * @brief Permet de mettre à jour la frame actuelle (mode play : avance de x frames avec x la vitesse du mode play)
	 */
	void update();

	/**
	 * @brief Permet de désactiver le controller
	 */
	void disable();

	/**
	 * @brief Permet d'activer le controller
	 */
	void enable();

	/**
	 * @brief Permet de créer le controller (constructeur)
	 *
	 * @param[out] splitLayerBottom layer de découpage contenant le menu de labellisation (bottom) et le reste de la fenetre (top)
	 * @param[out] splitLayerTopMenu layer de découpage contenant la barre du controller (top) et le plot3d (bottom)
	 * @param[in] nbFrames nombre de frames totales (nombre de frames de la scène)
	 * @param[in] validate boutton de validation de l'éditeur
	 * @param[in] cancel boutton d'anulation de l'éditeur
	 * @param window lien vers la classe principale du GUI
	 * @param labeliserMenu lien vers le menu de labellisation
	 *
	 * @return un pointeur partagé pointant vers le controller ainsi créé
	 */
	static std::shared_ptr<Controller> create(std::shared_ptr<SplitLayer>& splitLayerBottom, std::shared_ptr<SplitLayer>& splitLayerTopMenu,
			unsigned int nbFrames, const std::shared_ptr<Button>& validate, const std::shared_ptr<Button>& cancel, Window& window,
			const std::shared_ptr<LabeliserMenu>& labeliserMenu);

private:
	unsigned int nbFrames;
	unsigned int currentFrame = 0;
	std::shared_ptr<CenteredLayer> frameInfo;
	std::shared_ptr<Button> prevFrame;
	std::shared_ptr<Button> nextFrame;
	std::shared_ptr<Button> forwardPlay;
	std::shared_ptr<Button> backwardPlay;
	std::shared_ptr<Button> pause;
	std::shared_ptr<Button> prevLabelisationFrame;
	std::shared_ptr<Button> nextLabelisationFrame;
	std::shared_ptr<LabeliserMenu> labeliserMenu;
	Window& window;
	bool running = false;
	bool forward = true;
	bool isDisable = false;
	unsigned int modelFrame = UINT_MAX;
	unsigned short speed = 1;

	/**
	 * @brief constructeur
	 *
	 * @param frameInfo pointeur vers le layer contenant l'indicateur de frame (textLayer)
	 * @param prevFrame lien vers le boutton permettant de reculer d'une frame
	 * @param nextFrame lien vers le boutton permettant d'avancer d'une frame
	 * @param prevLabelisationFrame lien vers le boutton permettant de reculer vers la frame non labellisé précédante
	 * @param nextLabelisationFrame lien vers le boutton permettant d'avancer vers la frame non labellisé suivante
	 * @param forwardPlay lien vers le boutton d'avance directe
	 * @param backwardPlay lien vers le boutton d'avance indirecte
	 * @param pause lien vers le boutton de mise en pause
	 * @param nbFrames nombre de frame totale (nombre de frames la scène)
	 * @param window lien vers la class principale du GUI
	 * @param labeliserMenu line vers le menu de labellisation
	 */
	Controller(const std::shared_ptr<CenteredLayer>& frameInfo, const std::shared_ptr<Button>& prevFrame,
			const std::shared_ptr<Button>& nextFrame, const std::shared_ptr<Button>& prevLabelisationFrame,
			const std::shared_ptr<Button>& nextLabelisationFrame, const std::shared_ptr<Button>& forwardPlay,
			const std::shared_ptr<Button>& backwardPlay, const std::shared_ptr<Button>& pause, unsigned int nbFrames, Window& window,
			const std::shared_ptr<LabeliserMenu>& labeliserMenu);
};

} /* namespace window */

#endif /* SRC_CONTROLLER_CONTROLLER_H_ */
