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
		CcsdsFrame(const int spacecraftId, const int virtualChannelId, const byte payload[], const int payloadSize, const boolean isNextFrame, const long timeStamp);
		virtual ~CcsdsFrame();

		int spacecraftId;
		int virtualChannelId;
		byte payload[];
		boolean isNextFrame;
		long timeStamp;
};

} /* namespace model */
#endif /* CCSDSFRAME_H_ */
