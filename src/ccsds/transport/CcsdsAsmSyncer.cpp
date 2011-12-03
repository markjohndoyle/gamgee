/*
 * CcsdsAsmSyncer.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: mark
 */

#include "CcsdsAsmSyncer.h"

namespace transport {

const unsigned int CcsdsAsmSyncer::MAX_FRAME_SIZE;
const char CcsdsAsmSyncer::ASM_SIZE;

CcsdsAsmSyncer::CcsdsAsmSyncer() : asmByteMarker(0), receivedNumBytes(0) {
	asmMarker[0] = 0x1A & 0xFF;
	asmMarker[1] = 0xCF & 0xFF;
	asmMarker[2] = 0xFC & 0xFF;
	asmMarker[3] = 0x1D & 0xFF;
}

CcsdsAsmSyncer::~CcsdsAsmSyncer() {
	// TODO Auto-generated destructor stub
}

void CcsdsAsmSyncer::processByte(byte inByte) {
	// If the byte corresponds to the current ASM marker byte...
	Serial.print("byte = ");
	Serial.println(inByte, HEX);
	Serial.print("asm = ");
	Serial.println(asmMarker[asmByteMarker], HEX);

	if (inByte == asmMarker[asmByteMarker]) {
		// increment the ASM byte we are checking next
		asmByteMarker++;

		// if that was the final ASM byte then we have successfully parsed an ASM marker
		if (asmByteMarker == ASM_SIZE) {
			Serial.println("ASM marker detected, sending Framebuffer minus ASM size");
			// send received buffer
			frameClientListener->receiveCompleteFrame(receivedFrame, receivedNumBytes);

			// reset the asmByte and receivedFrameBuffer for the next iteration
			asmByteMarker = 0;
			receivedNumBytes = 0;
			util::ArrayUtils::clearByteArray(receivedFrame, MAX_FRAME_SIZE);
		}
	}
	else {
		Serial.println("byte not next asm byte");
		// Received byte not part of the ASM. Reset current asm byte "pointer" and continue processing the stream.
		receivedFrame[receivedNumBytes++] = inByte;
		asmByteMarker = 0;
	}

}

void CcsdsAsmSyncer::dumpFrameBufferToSerial(int numBytes) {
	String numBytesToSend = (String) numBytes;
	Serial.println("Sending " + numBytesToSend + " frame bytes");
	for (int i = 0; i < numBytes; i++) {
		Serial.println(receivedFrame[i]);
	}
}

void CcsdsAsmSyncer::regsiterForFrameOnCompletion(FrameListener* l) {
	frameClientListener = l;
}

} // end namespace transport
