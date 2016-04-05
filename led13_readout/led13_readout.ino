/*
 * Arduino relay pin tester
 */

#define inputPin 12
#define ledPin 13

void setup() {
  pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);
}

void loop() {
  if (digitalRead(inputPin) == HIGH) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);

  delay(10);
}
