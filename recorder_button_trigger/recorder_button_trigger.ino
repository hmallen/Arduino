#define outputPin A0

void setup() {
  Serial.begin(57600);
  
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, HIGH);

  delay(5000);

  Serial.println("Triggering...");
  digitalWrite(outputPin, LOW);
  delay(1000);
  digitalWrite(outputPin, HIGH);
}

void loop() {
  // STUFF & THINGS
}
