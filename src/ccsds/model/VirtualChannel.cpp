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

const CcsdsFrame VirtualChannel::processPayload(const int _spacecraftId, const byte _payload[], const int _payloadLength,
		const int _frameCount, const int _firstHeaderPointer) {

	int payloadOffset = 0;
	bool isNext;

	if (VirtualChannel::isNextFrame(lastFrameCount, _frameCount)) {
		isNext = true;
	}
	else {
		// we received frames out of order; payload before firstHeaderPointer must be thrown away.
		payloadOffset = _firstHeaderPointer;
		isNext = false;
	}

	lastFrameCount = _frameCount;

	byte goodPayload[_payloadLength - payloadOffset];
	util::ArrayUtils::newByteArray(_payload, payloadOffset, _payloadLength, goodPayload);

	long currentOnBoardTime = millis();
	return CcsdsFrame(_spacecraftId, _spacecraftId, goodPayload, _payloadLength - payloadOffset, isNext,
			currentOnBoardTime);
}

} /* namespace model */

