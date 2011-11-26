/*
 * ArrayUtilsTest.cpp
 *
 *  Created on: Nov 22, 2011
 *      Author: Mark Doyle
 */

#include "ArrayUtilsTest.h"

namespace test {

ArrayUtilsTest::~ArrayUtilsTest() {
	// TODO Auto-generated destructor stub
}

ArrayUtilsTest::ArrayUtilsTest() {
	// TODO Auto-generated constructor stub

}

void ArrayUtilsTest::testNewByteArray() {
	const int ARRAY_SIZE = 6;
	byte sourceArray[ARRAY_SIZE] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
	byte targetArray[ARRAY_SIZE];

	util::ArrayUtils::newByteArray(sourceArray, 0, ARRAY_SIZE, targetArray);
}


int main(int argc, char **argv) {
	ArrayUtilsTest::testNewByteArray();

	return 0;
}


} /* namespace test */
