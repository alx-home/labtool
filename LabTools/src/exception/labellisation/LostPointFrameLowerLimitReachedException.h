/*
 * FrameGapLowerLimitReachedException.h
 *
 *  Created on: 3 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EXCEPTION_LABELLISATION_LOSTPOINTFRAMELOWERLIMITREACHEDEXCEPTION_H_
#define SRC_EXCEPTION_LABELLISATION_LOSTPOINTFRAMELOWERLIMITREACHEDEXCEPTION_H_

#include <exception>

namespace exception {
namespace labelisation {

class LostPointFrameLowerLimitReachedException: public std::exception {
public:
	LostPointFrameLowerLimitReachedException();
	virtual ~LostPointFrameLowerLimitReachedException();
};

} /* namespace labelisation */
} /* namespace exception */

#endif /* SRC_EXCEPTION_LABELLISATION_LOSTPOINTFRAMELOWERLIMITREACHEDEXCEPTION_H_ */
