#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
//#include "printf.h"

RF24 radio(9, 10);

// TRIGGER PIN

const uint64_t pipe = 0xE8E8F0F0E1LL;

const uint8_t ledPins[] = {4};
const uint8_t ledPinLength = sizeof(ledPins);

uint8_t ledStates[ledPinLength];

void setup() {
  Serial.begin(57600);
  //printf_begin();

  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();

  radio.printDetails();

  int i = ledPinLength;
  while (i--) {
    pinMode(ledPins[i], OUTPUT);
    ledStates[i] = LOW;
    digitalWrite(ledPins[i], ledStates[i]);
  }
}

void loop() {
  Serial.println("Listening...");

  if (radio.available()) {
    boolean readDone = false;
    while (!readDone) {
      readDone = radio.read(ledStates, ledPinLength);

      int i = ledPinLength;
      while (i--) {
        if (ledStates[i]) {
          ledStates[i] ^= HIGH;
          digitalWrite(ledPins[i], ledStates[i]);
        }
      }
    }
  }
  
  while (true) {
    delay(10000);
  }
}

