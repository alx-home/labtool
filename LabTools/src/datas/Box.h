/*
 * Box.h
 *
 *  Created on: 10 févr. 2016
 *      Author: alex
 */

#ifndef SRC_DATAS_BOX_H_
#define SRC_DATAS_BOX_H_

#include "../utils/math/Vector.h"

namespace labeliser {

/**
 * @class Box
 * @brief container de coordonées définissant une boite
 * @author Alexandre GARCIN
 * @date 10 févr. 2016
 */
class Box {
public:
	/**
	 * @brief constructor
	 *
	 * @param beggin coordonnées haut gauche de la boite
	 * @param end coordonnées bas droite de la boite
	 */
	Box(const Vector3d& beggin, const Vector3d& end);

	virtual ~Box();

	/**
	 * @return coordonnées haut gauche de la boite
	 */
	const Vector3d& getBeggin() const;

	/**
	 * @return coordonnées bas droite de la boite
	 */
	const Vector3d& getEnd() const;

	/**
	 * @brief permet de savoir si un point se situe dans ou en dehors de la boite
	 *
	 * @param point le point considéré
	 * @return true si dedans, false sinon
	 */
	bool isInside(const Vector3d& point) const;

	/**
	 * @brief définit les coordonnées haut gauche de la boite
	 *
	 * @param beggin les coordonnées à définir
	 * @warning il est de la responsabilité du programmeur de vérifier que les coordonnées sont bien celles
	 * du coin haut gauche et non pas celles du coin bas droite
	 */
	void setBeggin(const Vector3d& beggin);

	/**
	 * @brief définit les coordonnées haut gauche de la boite
	 *
	 * @param end les coordonnées à définir
	 * @warning il est de la responsabilité du programmeur de vérifier que les coordonnées sont bien celles
	 * du coin bas droite et non pas celles du coin haut gauche
	 */
	void setEnd(const Vector3d& end);

private:
	Vector3d beggin;
	Vector3d end;
};

}  // namespace labeliser

#endif /* SRC_DATAS_BOX_H_ */
