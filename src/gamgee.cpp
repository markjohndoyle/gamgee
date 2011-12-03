/**
 * Gamgee - Hummingbird's faithful companion!
 *
 *
 * @author Mark Doyle
 */
#include <WProgram.h>
#include <stdlib.h>
#include <arduino.h>

#include <CcsdsStreamToPacketProcessor.h>
#include <ArrayUtils.h>

//#include <ArrayUtilsTest.h>

// the number of the LED pin
const int LED_PIN = 13;
// LED starts in the off state
int ledState = LOW;

const int FRAME_SIZE = 13;
transport::CcsdsStreamToPacketProcessor* processor;

//int main(void) {
//	init();
//
//	setup();
//
//	for (;;)
//		loop();
//
//	Serial.println("Event loop end.");
//
//	return 0;
//}

void setup() {
	// initialize the serial communication:
	Serial.begin(9600);

	// set the LED_PIN as output:
	pinMode(LED_PIN, OUTPUT);

	processor = new transport::CcsdsStreamToPacketProcessor(FRAME_SIZE);

	// Clear the buffer
	Serial.flush();
}

void loop() {
	if (!processor->isDecoding()) {
		if (Serial.available() > 0) {
			byte inByte = Serial.read();
			Serial.println(inByte, BYTE);
			if (inByte != -1) {
				// Ignore any serial msg header bytes
				if (inByte != 0xF0) {
					processor->processByte(inByte);
				}
			}
		}
	}

	delayMicroseconds(100);
}

