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
	syncer->processByte(b);
}

void CcsdsStreamToPacketProcessor::receiveCompleteFrame(byte frame[], int sizeOfFrame) {
	decoding = true;

	Serial.print("StreamToPacketProcessor received a complete frame of size: ");
	Serial.println((String)sizeOfFrame);

	util::ArrayUtils::dumpArray(frame, 0, sizeOfFrame, util::ArrayUtils::BASE_HEX);

	const model::CcsdsFrame decodedFrame = frameDecoder->decode(frame, sizeOfFrame);

	if(decodedFrame.spacecraftId != -1) {
		String packetSizeStr = (String)decodedFrame.packetSize;
		Serial.println("Decoded packet size = " + packetSizeStr);
		util::ArrayUtils::dumpArray(decodedFrame.packet, 0, decodedFrame.packetSize, util::ArrayUtils::BASE_HEX);
	}
	else {
		Serial.println("Frame was invalid - spacecraft id = -1");
	}

	decoding = false;
}

const bool CcsdsStreamToPacketProcessor::isDecoding() const {
	return decoding;
}

}
