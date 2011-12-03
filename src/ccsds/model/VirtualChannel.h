/*
 * VirtualChannel.h
 *
 *  Created on: Nov 19, 2011
 *      Author: mark
 */

#ifndef VIRTUALCHANNEL_H_
#define VIRTUALCHANNEL_H_

#include <WProgram.h>
//#include <CcsdsFrameDecoder.h>
#include <ArrayUtils.h>
#include <CcsdsFrame.h>

namespace model {

class VirtualChannel {
	public:
		VirtualChannel() : channelId(0), lastFrameCount(-1) {
			// Required default constructor in C++ if objects are used in an array.
		}

		VirtualChannel(int id) :
				channelId(id), lastFrameCount(-1) {
		}

		virtual ~VirtualChannel();

		const CcsdsFrame processPayload(const int _spacecraftId, const byte _payload[], const int _payloadLength,
				const int _frameCount, const int _firstHeaderPointer);

		/**
		 * channelId getter
		 */
		int getChannelId() const {
			return channelId;
		}

		static bool isNextFrame(const int lastFrameCount, const int frameCount) {
			// TODO get rid of the magic numbers
			return (((frameCount - lastFrameCount + 256) % 256) == 1);
		}

	private:
		int channelId;
		int lastFrameCount;
};

} /* namespace model */
#endif /* VIRTUALCHANNEL_H_ */
