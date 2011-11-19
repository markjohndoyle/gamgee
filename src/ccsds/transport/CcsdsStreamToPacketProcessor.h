/*
 * CcsdsStreamToPacketProcessor.h
 *
 *  Created on: Nov 19, 2011
 *      Author: mark
 */

#ifndef CCSDSSTREAMTOPACKETPROCESSOR_H_
#define CCSDSSTREAMTOPACKETPROCESSOR_H_

#include "CcsdsAsmSyncer.h"
#include "CcsdsFrameDecoder.h"

namespace transport {


class CcsdsStreamToPacketProcessor : public FrameListener {

public:
	CcsdsStreamToPacketProcessor();
	virtual ~CcsdsStreamToPacketProcessor();

	void processByte(byte b);
	virtual void receiveCompleteFrame(byte frame[], int sizeOfFrame);

private:
	CcsdsAsmSyncer syncer;
	CcsdsFrameDecoder frameDecoder;

};

}
#endif /* CCSDSSTREAMTOPACKETPROCESSOR_H_ */
