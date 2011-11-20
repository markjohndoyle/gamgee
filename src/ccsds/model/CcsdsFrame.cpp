/*
 * CcsdsFrame.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: Mark Doyle
 */

#include "CcsdsFrame.h"
#include <WProgram.h>

namespace model {

CcsdsFrame::CcsdsFrame(const int spacecraftId, const int virtualChannelId, const byte payload[], const int payloadSize, const boolean isNextFrame, const long timeStamp) :
		spacecraftId(spacecraftId),
		virtualChannelId(virtualChannelId),
		isNextFrame(isNextFrame),
		timeStamp(0) {

	for(int i = 0; i < payloadSize; i++) {
		this->payload[i] = payload[i];
	}
}

CcsdsFrame::~CcsdsFrame() {
	// TODO Auto-generated destructor stub
}

} /* namespace model */
