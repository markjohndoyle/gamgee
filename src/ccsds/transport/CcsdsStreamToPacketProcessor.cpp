/*
 * CcsdsStreamToPacketProcessor.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: Mark Doyle
 */

#include "CcsdsStreamToPacketProcessor.h"

namespace transport {

CcsdsStreamToPacketProcessor::CcsdsStreamToPacketProcessor(int frameLength) : lengthOfFrames(frameLength), decoding(false) {
	this->frameDecoder = new CcsdsFrameDecoder(frameLength);
	this->syncer = new CcsdsAsmSyncer();
	this->syncer->regsiterForFrameOnCompletion(this);
	Serial.println(this->frameDecoder->name);
}

CcsdsStreamToPacketProcessor::~CcsdsStreamToPacketProcessor() {
}

void CcsdsStreamToPacketProcessor::processByte(byte b) {
	Serial.println("Sending byte to ASM syncer");
	syncer->processByte(b);
}

void CcsdsStreamToPacketProcessor::receiveCompleteFrame(byte frame[], int sizeOfFrame) {
	decoding = true;
	Serial.print("StreamToPacketProcessor received a complete frame of size: ");
	Serial.println((String)sizeOfFrame);

	util::ArrayUtils::dumpArray(frame, 0, sizeOfFrame, util::ArrayUtils::BASE_HEX);

	const model::CcsdsFrame decodedFrame = frameDecoder->decode(frame, sizeOfFrame);
	decodedFrame.dumpFrame();

	if(decodedFrame.spacecraftId != -1) {
		String frameSize = (String)decodedFrame.frameSize;
		Serial.println("Decoded frame size = " + frameSize);
	}
	else {
		Serial.println("Frame was null");
	}

	decoding = false;
}

const bool CcsdsStreamToPacketProcessor::isDecoding() const {
	return decoding;
}

}
