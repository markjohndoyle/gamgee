/*
 * CcsdsPacketDecoder.h
 *
 *  Created on: Nov 17, 2011
 *      Author: mark
 */

#ifndef CCSDSPACKETDECODER_H_
#define CCSDSPACKETDECODER_H_

#include <WProgram.h>

namespace transport {

class CcsdsPacketDecoder {
public:
	CcsdsPacketDecoder();
	virtual ~CcsdsPacketDecoder();

	const String sayHi() const {
		return "Hi!";
	}
};

}
#endif /* CCSDSPACKETDECODER_H_ */
