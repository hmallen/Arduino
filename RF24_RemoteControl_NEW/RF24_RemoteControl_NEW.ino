#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9, 10);

// TRIGGER PIN

const uint64_t pipe = 0xE8E8F0F0E1LL;

const uint8_t message[] = {1};

const uint8_t messageLength = sizeof(message);

void setup() {
  Serial.begin(57600);
  printf_begin();

  radio.begin();

  radio.openWritingPipe(pipe);

  radio.printDetails();

  while (true) {
    Serial.println("Type 'S' to send trigger.");
    while (!Serial.available()) {
      ;
    }
    char c;
    while (Serial.available()) {
      c = Serial.read();
      delay(10);
    }
    if (c == 'S') break;
    else Serial.println("Invalid input. Please try again.");
  }
}

void loop() {
  Serial.println("Sending...");

  unsigned long time = millis();

  boolean sent = radio.write(&time, sizeof(unsigned long));
  Serial.println(sent);

  if (sent) Serial.println("OK");
  else Serial.println("FAILED");

  delay(1000);
}

