/*
 * CcsdsFrame.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: Mark Doyle
 */

#include "CcsdsFrame.h"
#include <WProgram.h>

namespace model {

CcsdsFrame::CcsdsFrame(const int spacecraftIdIn, const int virtualChannelIdIn, const byte payloadIn[], const int payloadSizeIn,
		const boolean isNextFrameIn, const long timeStampIn) :
		spacecraftId(spacecraftIdIn), virtualChannelId(virtualChannelIdIn), isNextFrame(isNextFrameIn), timeStamp(0), frameSize(payloadSizeIn) {

	for (int i = 0; i < frameSize; i++) {
		payload[i] = payloadIn[i];
	}
}

CcsdsFrame::~CcsdsFrame() {
	// TODO Auto-generated destructor stub
}

void CcsdsFrame::dumpFrame() const {
	for (int i = 0; i < frameSize; i++) {
		Serial.println(payload[i], HEX);
	}
}

} /* namespace model */
