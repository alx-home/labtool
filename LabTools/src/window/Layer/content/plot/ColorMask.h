/*
 * ColorMask.h
 *
 *  Created on: 7 févr. 2016
 *      Author: alex
 */

#ifndef SRC_WINDOW_LAYER_CONTENT_PLOT_COLORMASK_H_
#define SRC_WINDOW_LAYER_CONTENT_PLOT_COLORMASK_H_

#include <SFML/Graphics/Color.hpp>

namespace utils {

class ColorMask {
public:
	ColorMask(sf::Color color, unsigned short priority, unsigned long long int id);
	virtual ~ColorMask();
	sf::Color getColor() const;
	unsigned short getPriority() const;
	unsigned long long int getId() const;

private:
	sf::Color color;
	unsigned short priority;
	unsigned long long int id;
};

} /* namespace utils */

#endif /* SRC_WINDOW_LAYER_CONTENT_PLOT_COLORMASK_H_ */
