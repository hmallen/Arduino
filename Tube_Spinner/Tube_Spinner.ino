/*
 * Tube Spinner
 */

#include <Servo.h>

#define servoPin 9
#define ledPin 13

Servo servo;

unsigned long spinTime = 1000 * 60 * 60;  // 1 hour in milliseconds

void setup() {
  pinMode(ledPin, OUTPUT); digitalWrite(ledPin, LOW);
  
  servo.attach(servoPin);
  
  delay(500);

  digitalWrite(ledPin, HIGH);
  servo.write(100);

  delay(spinTime);

  servo.write(90);
  servo.detach();
}

void loop() {
  while (true) {
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(ledPin, HIGH);
    delay(1000);
  }
}
