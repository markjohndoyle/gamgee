/*
 * VirtualChannel.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: Mark Doyle
 */

#include "VirtualChannel.h"

namespace model {

VirtualChannel::~VirtualChannel() {
	// TODO Auto-generated destructor stub
}

const CcsdsFrame* VirtualChannel::processPayload(const int spacecraftId, const byte payload[], const int payloadLength,
		const int frameCount, const int firstHeaderPointer) {

	int payloadOffset = 0;
	bool isNext;

	if (VirtualChannel::isNextFrame(lastFrameCount, frameCount)) {
		isNext = true;
	}
	else {
		// we received frames out of order; payload before firstHeaderPointer must be thrown away.
		payloadOffset = firstHeaderPointer;
		isNext = false;
	}

	lastFrameCount = frameCount;

	byte goodPayload[payloadLength - payloadOffset];
	util::ArrayUtils::newByteArray(payload, payloadOffset, payloadLength, goodPayload);

	long currentOnBoardTime = millis();
	return new CcsdsFrame(spacecraftId, spacecraftId, goodPayload, payloadLength - payloadOffset, isNext,
			currentOnBoardTime);
}

} /* namespace model */

