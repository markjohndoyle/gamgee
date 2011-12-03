/*
 * CcsdsFrame.h
 *
 *  Created on: Nov 19, 2011
 *      Author: Mark Doyle
 */

#ifndef CCSDSFRAME_H_
#define CCSDSFRAME_H_

#include <WProgram.h>

namespace model {

class CcsdsFrame {
	public:
		const int spacecraftId;
		const int virtualChannelId;
		byte packet[];
		boolean isNextFrame;
		long timeStamp;
		const int frameSize;

		CcsdsFrame(const int spacecraftIdIn = -1 , const int virtualChannelIdIn = 0, const byte payloadIn[] = 0, const int payloadSizeIn = 0, const boolean isNextFrameIn = false, const long timeStampIn = 0);
		virtual ~CcsdsFrame();
};

} /* namespace model */
#endif /* CCSDSFRAME_H_ */
