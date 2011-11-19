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
};

} /* namespace util */
#endif /* ARRAYUTILS_H_ */
