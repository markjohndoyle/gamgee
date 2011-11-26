/*
 * CcsdsFrameDecoder.h
 *
 *  Created on: Nov 19, 2011
 *      Author: mark
 */

#ifndef CCSDSFRAMEDECODER_H_
#define CCSDSFRAMEDECODER_H_

#include <WProgram.h>
#include <CcsdsFrame.h>
#include <VirtualChannel.h>
#include <ArrayUtils.h>

namespace transport {

class CcsdsFrameDecoder {
	public:
		static const String IS_NEXT_FRAME;

		static const String SPACECRAFT_ID;

		static const String VIRTUAL_CHANNEL_ID;

		const int frameLengthInOctets;

		CcsdsFrameDecoder(const int frameLength, const boolean ocfPresent = false, const boolean ecfPresent = false);
		virtual ~CcsdsFrameDecoder();

		const model::CcsdsFrame* decode(byte frame[], const int frameSize);

	private:
		/*
		 * Byte position at which the frame payload ends. This depends on whether OCF and/or ECF are present.
		 */
		int payloadEnd;

		/*
		 * Signifies whether the Operational Control Field (4 octets) is present
		 */
		const boolean OCF_PRESENT;

		static const int OCF_LENGTH = 4;

		int OCF_START;

		static const int ECF_LENGTH = 2;

		int ECF_START;


		/*
		 * Signifies whether the Error Control Field (2 octets) is present
		 */
		const boolean ECF_PRESENT;

		model::VirtualChannel virtualChannels[8];
};

}
#endif /* CCSDSFRAMEDECODER_H_ */
