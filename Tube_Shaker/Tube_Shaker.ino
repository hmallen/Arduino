/*
   Tube Shaker
*/

#define stp 7
#define dir 8
#define MS1 4
#define MS2 5
#define MS3 6
#define EN 3

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);
  digitalWrite(dir, LOW);
}

void loop() {
  digitalWrite(stp, HIGH);
  delay(1);
  digitalWrite(stp, LOW);
  delay(1);
}
