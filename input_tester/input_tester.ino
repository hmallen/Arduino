#define inputPin 4
#define outputPin A0

void setup() {
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);

  digitalWrite(outputPin, LOW);
}

void loop() {
  if (inputPin == HIGH) digitalWrite(outputPin, HIGH);
  else digitalWrite(outputPin, LOW);

  delay(10);
}
