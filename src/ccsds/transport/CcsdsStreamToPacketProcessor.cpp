/*
 * CcsdsStreamToPacketProcessor.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: mark
 */

#include "CcsdsStreamToPacketProcessor.h"

namespace transport {

CcsdsStreamToPacketProcessor::CcsdsStreamToPacketProcessor() {
	this->syncer.regsiterForFrameOnCompletion(this);
}

CcsdsStreamToPacketProcessor::~CcsdsStreamToPacketProcessor() {
	// TODO Auto-generated destructor stub
}

void CcsdsStreamToPacketProcessor::processByte(byte b) {
	this->syncer.processByte(b);
}

void CcsdsStreamToPacketProcessor::receiveCompleteFrame(byte frame[], int sizeOfFrame) {
	for(int i = 0; i < sizeOfFrame; i++) {
		Serial.println(frame[i]);
	}
}

}
