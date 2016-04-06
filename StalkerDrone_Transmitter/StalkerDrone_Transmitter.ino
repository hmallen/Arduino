/*
 * RF24 Transmitter Unit
 * 
 * TO DO:
 * - Add tactile push button to trigger
 * - Test with battery pack
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9, 10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void) {
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
  printf("\n\rType 'S' to send...\n\r");

  boolean sendTrigger = false;
  while (sendTrigger == false) {
    while (!Serial.available()) {
      ;
    }
    while (Serial.available()) {
      char c = Serial.read();
      if (c == 'S') {
        sendTrigger = true;
        break;
      }
    }
  }

  radio.stopListening();

  // Take the time, and send it.  This will block until complete
  unsigned long message = 1;
  //char message[] = {"I <3 U!\0"};

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

  printf("Send complete.\n\r");
}
