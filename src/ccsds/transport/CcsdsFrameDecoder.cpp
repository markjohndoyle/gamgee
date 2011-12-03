/*
 * CcsdsFrameDecoder.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: Mark Doyle
 *
 *  Standards taken from:
 *  "TM SPACE DATA LINK PROTOCOL CCSDS - 132.0-B-1"
 *	http://public.ccsds.org/publications/archive/132x0b1.pdf
 */

#include "CcsdsFrameDecoder.h"

namespace transport {

const String CcsdsFrameDecoder::IS_NEXT_FRAME = "IsNextFrame";
const String CcsdsFrameDecoder::SPACECRAFT_ID = "SpacecraftId";
const String CcsdsFrameDecoder::VIRTUAL_CHANNEL_ID = "VirtualChannelId";

using namespace model;

CcsdsFrameDecoder::CcsdsFrameDecoder(const int _frameLength, const boolean _ocfPresent, const boolean _ecfPresent) :
		frameLengthInOctets(_frameLength), name("CcsdsFrameDecoder"), payloadEnd(_frameLength), OCF_PRESENT(_ocfPresent), ECF_PRESENT(_ecfPresent) {

	if (ECF_PRESENT) {
		payloadEnd = payloadEnd - ECF_LENGTH;
		ECF_START = payloadEnd;
	}

	if (OCF_PRESENT) {
		payloadEnd = payloadEnd - OCF_LENGTH;
		OCF_START = payloadEnd;
	}

	// Create 8 VirtualChannels, accessed using their array index.
	for (int i = 0; i < 8; i++) {
		virtualChannels[i] = VirtualChannel(i);
	}

	Serial.println("Constructed CcsdsFrameDecoder");
}

CcsdsFrameDecoder::~CcsdsFrameDecoder() {
	// TODO Auto-generated destructor stub
}

const model::CcsdsFrame CcsdsFrameDecoder::decode(const byte frame[], const int frameSize) {
	// Check for Frame Length
	if (frameSize != frameLengthInOctets) {
		String sizeStr = (String)frameSize;
		Serial.println("Frame size = " + sizeStr);
		Serial.println("[ERROR] - Corrupt frame - Length not correct.");
		return model::CcsdsFrame();
	}
	else {
		Serial.println("Frame size valid");
	}

	// FIXME Handle OCF and ECF
	if (OCF_PRESENT) {
		Serial.println("OCF present");
		byte operationalControlField[OCF_LENGTH];
		util::ArrayUtils::newByteArray(frame, OCF_START, OCF_START + OCF_LENGTH, operationalControlField);
	}

	if (ECF_PRESENT) {
		Serial.println("ECF present");
		byte errorControlField[ECF_LENGTH];
		util::ArrayUtils::newByteArray(frame, ECF_START, ECF_START + ECF_LENGTH, errorControlField);

		// TODO Check for CRC errors
		// if (!crcValid(frame)) {
		// }
	}

	// Standards taken from "TM SPACE DATA LINK PROTOCOL CCSDS - 132.0-B-1"
	// http://public.ccsds.org/publications/archive/132x0b1.pdf
	// Transfer Frame Primary Header = 6 octets (mandatory) Transfer Frame Data Field Status = 2 octets (mandatory)
	// Transfer Frame Secondary Header = 1 - 64 octets (optional)
	// Transfer Frame Data Field = 2 octets
	// Operational Control Field = 4 octets (optional) Frame Error Control Field = 2 octets (optional)
	byte primaryHeader[6];
	byte dataFieldStatus[2];

	util::ArrayUtils::newByteArray(frame, 0, 6, primaryHeader);

//	util::ArrayUtils::dumpArray(primaryHeader, 0, 6, util::ArrayUtils::BASE_HEX);

	int spacecraftIdHighByte = (0x3F & primaryHeader[0]) << 4;
	int spacecraftIdLowByte = (0xF0 & primaryHeader[1]) >> 4;
	int spacecraftId = spacecraftIdHighByte + spacecraftIdLowByte;

	String scId = (String) spacecraftId;
	Serial.println("Spacecraft ID: " + scId);

	int virtualChannelId = (0x0E & primaryHeader[1]) >> 1;
	if (virtualChannelId < 0 || virtualChannelId > 7) {
		Serial.println("[ERROR] - Corrupt frame - invalid virtual channel id");
		return NULL;
	}

	String vcId = (String) virtualChannelId;
	Serial.println("Virtual Channel Id: " + vcId);

	util::ArrayUtils::newByteArray(frame, 4, 6, dataFieldStatus);

	int firstHeaderPointerHighByte = (0x03 & dataFieldStatus[0]) << 8;
	int firstHeaderPointerLowByte = 0xFF & dataFieldStatus[1];

	int firstHeaderPointer = firstHeaderPointerHighByte + firstHeaderPointerLowByte;
	String fhp = (String) firstHeaderPointer;
	Serial.println("First Header Pointer:" + fhp);

	int masterChannelFrameCount = primaryHeader[2] & 0xFF;
	int virtualChannelFrameCount = primaryHeader[3] & 0xFF;

	String mcfc = (String) masterChannelFrameCount;
	String vcfc = (String) virtualChannelFrameCount;
	Serial.println("Master Channel Frame Count: " + mcfc);
	Serial.println("Virtual Channel Frame Count: " + vcfc);

	int payloadOffset = 6;

	// check for secondary header flag (1st bit in dataFieldStatus
	if ((0x80 & dataFieldStatus[0]) == 0x80) {
		// secondary header present
		Serial.println("This frame has a secondary header");

		byte secondaryHeaderStatus = frame[8];

		/*
		 * Secondary Header Version Number (first two bits of sec hdr status) is UNUSED.
		 */

		/*
		 * actual header length is one less than that. Since ArrayUtils uses
		 */
		int secondaryHeaderLength = (0x3F & secondaryHeaderStatus) - 1;
		String shl = (String) secondaryHeaderLength;
		Serial.println("Secondary Header Length: " + shl);

		byte secondaryHeader[secondaryHeaderLength];
		util::ArrayUtils::newByteArray(frame, payloadOffset, payloadOffset + secondaryHeaderLength, secondaryHeader);

		payloadOffset = payloadOffset + secondaryHeaderLength;

	}

	byte payload[payloadEnd - payloadOffset];
	util::ArrayUtils::newByteArray(frame, payloadOffset, payloadEnd, payload);

	return virtualChannels[virtualChannelId].processPayload(spacecraftId, payload, payloadEnd - payloadOffset,
			virtualChannelFrameCount, firstHeaderPointer);

}

}
