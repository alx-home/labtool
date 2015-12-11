/*
 * frameGapUpperLimitReachedException.h
 *
 *  Created on: 3 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EXCEPTION_LABELLISATION_LOSTPOINTFRAMEUPPERLIMITREACHEDEXCEPTION_H_
#define SRC_EXCEPTION_LABELLISATION_LOSTPOINTFRAMEUPPERLIMITREACHEDEXCEPTION_H_

#include <exception>

namespace exception {
namespace labelisation {

class LostPointFrameUpperLimitReachedException: public std::exception {
public:
	LostPointFrameUpperLimitReachedException();
	virtual ~LostPointFrameUpperLimitReachedException();
};

}
/* namespace labellisation */
} /* namespace exception */

#endif /* SRC_EXCEPTION_LABELLISATION_LOSTPOINTFRAMEUPPERLIMITREACHEDEXCEPTION_H_ */
