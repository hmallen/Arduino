/*
   Mouse Trap
*/

#include <Servo.h>

#define ledPin 13
#define pirPin A0
#define servoPin 9

Servo servo;

void setup() {
  pinMode(ledPin, OUTPUT); digitalWrite(ledPin, LOW);

  Serial.begin(57600);

  Serial.println("Arming in 30 seconds...");
  for (int x = millis(); (millis() - x) < 15000; ) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  Serial.println("Arming in 15 seconds...");
  for (int x = millis(); (millis() - x) < 10000; ) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  Serial.println("Arming in 5 seconds...");
  for (int x = millis(); (millis() - x) < 5000; ) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  Serial.print("Checking stability...");

  unsigned long startTime = millis();
  while (true) {
    int pirVal = analogRead(pirPin);

    if (pirVal > 300) startTime = millis();

    unsigned long elapsedTime = millis() - startTime;

    if (elapsedTime > 10000) break;
  }

  Serial.println("complete.");
  Serial.println();

  digitalWrite(ledPin, HIGH);

  Serial.println("Armed!");
  Serial.println();
}

void loop() {
  while (true) {
    int pirVal = analogRead(pirPin);

    Serial.println(pirVal);

    if (pirVal > 300) break;

    delay(500);
  }

  servo.attach(servoPin);
  servo.write(80);
  delay(500);
  servo.detach();

  Serial.println();
  Serial.println("Caught!");
  Serial.println();

  while (true) {
    digitalWrite(ledPin, LOW);
    delay(100);
    digitalWrite(ledPin, HIGH);
    delay(100);
  }
}
