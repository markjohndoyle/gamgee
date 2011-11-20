/*
 * ArrayUtils.h
 *
 *  Created on: Nov 19, 2011
 *      Author: mark
 */

#ifndef ARRAYUTILS_H_
#define ARRAYUTILS_H_

#include <WProgram.h>

namespace util {

class ArrayUtils {

	private:
		ArrayUtils();
		virtual ~ArrayUtils();

	public:
		static void clearByteArray(byte byteArray[], int arraySize);
		static void newByteArray(const byte payload[], const int payloadOffset, const int payloadLength, byte target[]);
};

} /* namespace util */
#endif /* ARRAYUTILS_H_ */
