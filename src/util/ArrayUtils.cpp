/*
 * ArrayUtils.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: Mark Doyle
 */

#include "ArrayUtils.h"

namespace util {

ArrayUtils::ArrayUtils() {
	// private; cannot instantiate utility class.
}

ArrayUtils::~ArrayUtils() {
	// private; cannot instantiate therefore cannot destroy utility class.
}

 void ArrayUtils::clearByteArray(byte byteArray[], int arraySize) {
	 // clear the received array
	 for (int i = 0; i < arraySize; i++) {
	 	byteArray[i] = 0;
	 }
}

} /* namespace util */
