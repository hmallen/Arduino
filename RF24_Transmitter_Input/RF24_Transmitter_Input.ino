/*
   RF24 Transmitter Unit
*/

#include <SPI.h>
#include <RF24.h>
//#include "nRF24L01.h"
#include "printf.h"

#define sensorPin 2

RF24 radio(9, 10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void) {
  pinMode(sensorPin, INPUT);

  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/pingpair/\n\r");

  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15, 15);

  // optionally, reduce the payload size.  seems to
  // improve reliability
  radio.setPayloadSize(8);

  radio.openWritingPipe(pipes[0]);
  //radio.openReadingPipe(1, pipes[1]);

  radio.printDetails();
}

void loop(void) {
  unsigned long sensorInput = digitalRead(sensorPin);
  Serial.println(sensorInput);

  radio.stopListening();

  // Take the time, and send it.  This will block until complete
  unsigned long message = sensorInput;
  Serial.println(message);

  printf("Now sending...");
  bool ok = radio.write(&message, sizeof(message));

  if (ok) printf("ok...");
  else printf("failed.\n\r");

  // Now, continue listening
  radio.startListening();

  // Wait here until we get a response, or timeout (250ms)
  unsigned long started_waiting_at = millis();
  bool timeout = false;
  while ( ! radio.available() && ! timeout ) {
    if (millis() - started_waiting_at > 200 ) timeout = true;
  }

  delay(1000);
}
