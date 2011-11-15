/**
 * Gamgee - Hummingbirds faithful companion!
 *
 * Currently reads a byte stream off the serial port and splits it into frames based upon the CCSDS ASM
 * standard.
 *
 * @author Mark Doyle
 */
#include <WProgram.h>
#include <arduino.h>

// ASM marker byte array
const byte ASM_MARKER[] = { 0x1A & 0xFF, 0xCF & 0xFF, 0xFC & 0xFF, 0x1D & 0xFF };
// Length of the ASM marker
const char ASM_SIZE = 3;
// Current ASM byte marker position
int asmByteMarker = 0;

// the number of the LED pin
const int LED_PIN = 13;
// LED starts in the off state
int ledState = LOW;

// Read in buffer size
const int READ_BUFFER = 10;
// Serial data stream buffer
byte newData[READ_BUFFER];
int newDataRead = 0;

// Max frame size is 1014
const unsigned int MAX_FRAME = 1024;
byte receivedFrame[MAX_FRAME];
int receivedNumBytes = 0;

int main(void) {
	init();

	setup();

	for (;;)
		loop();

	return 0;
}

void dumpNewData() {
	Serial.println("New data dump:");
	for (int i = 0; i < newDataRead; i++) {
		Serial.print(newData[i]);
	}
	Serial.println();
}

void sendFrameBuffer(int numBytes) {
	String numBytesToSend = (String) numBytes;
	Serial.println("Sending " + numBytesToSend + " frame bytes");
	for (int i = 0; i < numBytes; i++) {
		Serial.println(receivedFrame[i]);
	}
}

/**
 * Blink led x number of times starting from an off state.
 */
void blinkLed(int count) {
	ledState = LOW;
	// if the LED is off turn it on and vice-versa:
	for (int i = 0; i < count; i++) {
		if (ledState == LOW) {
			ledState = HIGH;
		} else {
			ledState = LOW;
		}
		// set the LED with the ledState of the variable:
		digitalWrite(LED_PIN, ledState);
	}
}

void switchLed(boolean on) {
	if (on) {
		ledState = LOW;
	} else {
		ledState = HIGH;
	}
	// set the LED with the ledState of the variable:
	digitalWrite(LED_PIN, ledState);
}

void clearByteArray(byte byteArray[], int arraySize) {
	// clear the received array
	for (int i = 0; i < arraySize; i++) {
		byteArray[i] = 0;
	}
}

void setup() {
	clearByteArray(receivedFrame, MAX_FRAME);
	clearByteArray(newData, READ_BUFFER);

// initialize the serial communication:
	Serial.begin(115200);

	// set the LED_PIN as output:
	pinMode(LED_PIN, OUTPUT);

	// Clear the buffer
	Serial.flush();
}

void loop() {
	// While there are non-empty bytes on the stream read until newData of size READ_BUFFER is full...
	// Read in bytes
	if (Serial.available() == READ_BUFFER) {
		for (int i = 0; i < READ_BUFFER; i++) {
			if ((newData[i] = Serial.read()) == -1) {
				break;
			} else {
				newDataRead++;
			}
		}
	}

	if (newDataRead == READ_BUFFER) {
		Serial.println("Buffer full, syncing using ASM...");
		for (int i = 0; i < newDataRead; i++) {
			blinkLed(2);
			// If the byte corresponds to the current ASM marker byte...
			if (newData[i] == ASM_MARKER[asmByteMarker]) {
				// increment the ASM byte we are checking next
				asmByteMarker++;
				switchLed(true);

				// if that was the final ASM byte then we have successfully parsed an ASM marker
				if (asmByteMarker == ASM_SIZE) {
					Serial.println(
							"ASM marker detected, sending Framebuffer minus ASM size");
					// send received buffer
					sendFrameBuffer(receivedNumBytes - ASM_SIZE);

					// reset the asmByte and receivedFrameBuffer for the next iteration
					asmByteMarker = 0;
					receivedNumBytes = 0;
					clearByteArray(receivedFrame, MAX_FRAME);
				}
			} else {
				// Received byte not part of the ASM. Reset current asm byte "pointer" and continue processing the stream.
				receivedFrame[receivedNumBytes++] = newData[i];
				asmByteMarker = 0;
				switchLed(false);
			}
		}
		switchLed(false);
		clearByteArray(newData, READ_BUFFER);
		newDataRead = 0;
	}
}

