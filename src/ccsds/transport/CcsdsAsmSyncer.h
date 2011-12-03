/*
 * CcsdsAsmSyncer.h
 *
 *  Created on: Nov 19, 2011
 *      Author: mark
 */

#ifndef CCSDSASMSYNCER_H_
#define CCSDSASMSYNCER_H_

#include <WProgram.h>
#include <FrameListener.h>
#include <ArrayUtils.h>

namespace transport {

class CcsdsAsmSyncer {

public:
	CcsdsAsmSyncer();
	virtual ~CcsdsAsmSyncer();

	void processByte(byte inbyte);

	void regsiterForFrameOnCompletion(FrameListener* l);

private:
	// The listener that is called back when a frame is discovered.
	FrameListener* frameClientListener;

	// Length of the ASM marker
	static const char ASM_SIZE = 4;

	// ASM marker byte array
	byte asmMarker[ASM_SIZE];


	// Current ASM byte marker position
	int asmByteMarker;

	// Max frame size is 1014
	static const unsigned int MAX_FRAME_SIZE = 64;

	// The syncer will populate this frame until it discovers a marker and returns the frame.
	byte receivedFrame[MAX_FRAME_SIZE];

	int receivedNumBytes;

	void dumpFrameBufferToSerial(int numBytes);

};

}

#endif /* CCSDSASMSYNCER_H_ */
