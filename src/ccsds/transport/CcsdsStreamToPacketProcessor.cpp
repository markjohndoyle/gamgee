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
	this->frameDecoder->decode(frame, sizeOfFrame);
}

}
