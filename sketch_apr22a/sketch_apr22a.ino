/*
 * RF24 Receiver Unit
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9, 10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

void setup(void) {
  Serial.begin(57600);
  printf_begin();
  //printf("\n\rRF24/examples/pingpair/\n\r");
  Serial.println();

  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15, 15);

  // optionally, reduce the payload size.  seems to
  // improve reliability
  radio.setPayloadSize(8);

  //radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();

  radio.printDetails();
  Serial.println();

  delay(500);
}

void loop(void) {
  if (radio.available()) {
    //char message[12];
    unsigned long message;
    char done[8];
    for (int x = 0; x < 8; x++) {
      done[x] = radio.read(&message, sizeof(unsigned long));
    }
    /*while (radio.available()) {
      done(radio.read(&message, sizeof(unsigned long)));
    }*/
    Serial.println(done);

    if (message == 1) digitalWrite(outputPin, HIGH);
    else digitalWrite(outputPin, LOW);
  }
}
