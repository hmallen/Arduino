/*
  Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.
*/

/**
   Example RF Radio Ping Pair

   This is an example of how to use the RF24 class.  Write this sketch to two different nodes,
   connect the role_pin to ground on one.  The ping node sends the current time to the pong node,
   which responds by sending the value back.  The ping node can then see how long the whole cycle
   took.
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <Servo.h>

#define outputPin A0
#define servoPin 5

Servo servo;

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

RF24 radio(9, 10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  The hardware itself specifies
// which node it is.

void setup(void) {
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, HIGH);

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

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)

  //radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();

  radio.printDetails();
  //Serial.println("Hey Gillian, guess what??");
  Serial.println();

  servo.attach(servoPin);
  servo.write(90);
  delay(500);
}

void loop(void) {
  if (radio.available()) {
    //char message[12];
    unsigned long message;
    bool done = false;
    while (!done) {
      done = radio.read(&message, sizeof(unsigned long));
    }
    Serial.println(message);

    if (message == 1) {
      servo.write(80);
      delay(150);
      servo.write(90);
      delay(150);
    }
  }
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
