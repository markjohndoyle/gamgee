/**
 * Gamgee - Hummingbird's faithful companion!
 *
 * Currently reads a byte stream off the serial port and splits it into frames based upon the CCSDS ASM
 * standard.
 *
 * @author Mark Doyle
 */
#include <WProgram.h>

#include <arduino.h>
#include <CcsdsStreamToPacketProcessor.h>
#include <ArrayUtils.h>


// the number of the LED pin
const int LED_PIN = 13;
// LED starts in the off state
int ledState = LOW;

//// Read in buffer size
//const int READ_BUFFER = 10;
//// Serial data stream buffer
//byte newData[READ_BUFFER];
//int newDataRead = 0;




int main(void) {
	init();

	setup();

	for (;;)
		loop();

	return 0;
}

void setup() {
//	util::ArrayUtils::clearByteArray(newData, READ_BUFFER);

	// initialize the serial communication:
	Serial.begin(115200);

	// set the LED_PIN as output:
	pinMode(LED_PIN, OUTPUT);

	// Clear the buffer
	Serial.flush();
}

static const int FRAME_SIZE = 30;
transport::CcsdsStreamToPacketProcessor proc(FRAME_SIZE);

void loop() {
	// Buffering removed for now.
	// While there are non-empty bytes on the stream read until newData of size READ_BUFFER is full...
	// Read in bytes
//	if (Serial.available() == READ_BUFFER) {
//		for (int i = 0; i < READ_BUFFER; i++) {
//			if ((newData[i] = Serial.read()) == -1) {
//				break;
//			}
//			else {
//				newDataRead++;
//			}
//		}
//	}


	if (Serial.available()) {
		byte inByte = Serial.read();
		if(inByte != -1) {
			proc.processByte(inByte);
		}
	}
}

