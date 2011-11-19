/*
 * FrameListener.h
 *
 *  Created on: Nov 19, 2011
 *      Author: mark
 */

#ifndef FRAMELISTENER_H_
#define FRAMELISTENER_H_

#include <WProgram.h>

namespace transport {


class FrameListener {
public:
	FrameListener();
	virtual ~FrameListener();

	virtual void receiveCompleteFrame(byte frame[], int sizeOfFrame) = 0;

};

} /* namespace transport */
#endif /* FRAMELISTENER_H_ */
