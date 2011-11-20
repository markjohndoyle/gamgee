/*
 * CcsdsStreamToPacketProcessor.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: mark
 */

#include "CcsdsStreamToPacketProcessor.h"

namespace transport {

CcsdsStreamToPacketProcessor::CcsdsStreamToPacketProcessor(int frameLength) : frameDecoder(new CcsdsFrameDecoder(frameLength)) {
	this->syncer.regsiterForFrameOnCompletion(this);
}

CcsdsStreamToPacketProcessor::~CcsdsStreamToPacketProcessor() {
	// TODO Auto-generated destructor stub
}

void CcsdsStreamToPacketProcessor::processByte(byte b) {
	this->syncer.processByte(b);
}

void CcsdsStreamToPacketProcessor::receiveCompleteFrame(byte frame[], int sizeOfFrame) {
	const model::CcsdsFrame* decodedFrame = this->frameDecoder->decode(frame, sizeOfFrame);
	if(decodedFrame != NULL) {
		String frameSize = (String)decodedFrame->frameSize;
		Serial.println("Decoded frame size = " + frameSize);
		decodedFrame->dumpFrame();
	}
	else {
		Serial.println("Frame was null");
	}
}

}
