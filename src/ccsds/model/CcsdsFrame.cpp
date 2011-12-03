/*
 * CcsdsFrame.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: Mark Doyle
 */

#include "CcsdsFrame.h"
#include <WProgram.h>

namespace model {

CcsdsFrame::CcsdsFrame(const int spacecraftIdIn, const int virtualChannelIdIn, const byte packetIn[], const int payloadSizeIn,
		const boolean isNextFrameIn, const long timeStampIn) :
		spacecraftId(spacecraftIdIn), virtualChannelId(virtualChannelIdIn), isNextFrame(isNextFrameIn), timeStamp(0), frameSize(payloadSizeIn) {

	for (int i = 0; i < frameSize; i++) {
		packet[i] = packetIn[i];
	}
}

CcsdsFrame::~CcsdsFrame() {
	// TODO Auto-generated destructor stub
}

} /* namespace model */
