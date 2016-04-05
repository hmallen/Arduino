#define outputPin 2

void setup() {
  pinMode(outputPin, OUTPUT);

  digitalWrite(outputPin, LOW);
}

void loop() {
  digitalWrite(outputPin, HIGH);
  delay(1000);
  digitalWrite(outputPin, LOW);
  delay(1000);
}
