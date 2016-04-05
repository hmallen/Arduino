/*
   Awake/Behaving stage apparatus for multi-photon imaging
   - Stepper motor
   - Speed controller with LCD interface

   TO DO/FEATURES:
   - Backlight control
   - Accelerate/Deccelerate functions to initiate/halt rotation
*/

#include <LiquidCrystal.h>

#define stp 2
#define dir 3
#define MS1 A5
#define MS2 11
#define MS3 12
#define EN  13

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcdButtonPin = A0;
int lcdBacklightPin = 10;

int rpm[15] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75};
int rpmDelay[15] = {15000, 7500, 5000, 3750, 3000, 2500, 2143, 1875, 1667, 1500, 1364, 1250, 1154, 1071, 1000};  // Delay in microseconds for stepper motor steps
int rpmPosition = 0;

boolean runProgram = false;

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);

  pinMode(lcdBacklightPin, OUTPUT);

  resetPins();

  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Speed (RPM):");
  lcd.setCursor(0, 1);
  lcd.print(rpm[rpmPosition]);

  digitalWrite(lcdBacklightPin, HIGH);
  while (runProgram == false) {
    setSpeedRPM();
    delay(100);
  }
  digitalWrite(lcdBacklightPin, LOW);

  digitalWrite(EN, LOW); //Pull enable pin low to set FETs active and allow motor control
  digitalWrite(dir, LOW); //Pull direction pin LOW to move in "forward" direction
}

void loop() {
  if (runProgram == true) {
    //accelerateStep();
    while (runProgram == true) {
      forwardStepDefault();
      checkInput();
    }
  }

  //deccelerateStep();

  digitalWrite(lcdBacklightPin, HIGH);
  while (runProgram == false) {
    setSpeedRPM();
    delay(100);
  }
  digitalWrite(lcdBacklightPin, LOW);
}

void checkInput() {
  int buttonVal = readButton();
  String buttonValString = translateButton(buttonVal);
  if (buttonValString == "Select") {
    runProgram = false;
    while (readButton() != 0) {
      ;
    }
  }
}

void setSpeedRPM() {
  int buttonVal = readButton();
  String buttonValString = translateButton(buttonVal);
  boolean newDisplay = false;

  if (buttonValString == "Up" && rpmPosition < 14) {
    rpmPosition++;
    newDisplay = true;
  }
  else if (buttonValString == "Down" && rpmPosition > 0) {
    rpmPosition--;
    newDisplay = true;
  }
  else if (buttonValString == "Select") runProgram = true;

  while (readButton() != 0) {
    ;
  }

  if (newDisplay == true) {
    lcd.setCursor(0, 1);
    if (rpmPosition == 0) lcd.print(' ');
    lcd.print(rpm[rpmPosition]);
  }
}

void accelerateStep() {
  for (int x = 20000; x >= rpmDelay[rpmPosition]; x--) {
    digitalWrite(stp, HIGH);
    delayMicroseconds(x);
    digitalWrite(stp, LOW);
    delayMicroseconds(x);
  }
  Serial.println("Done");
}

void deccelerateStep() {
  for (int x = rpmDelay[rpmPosition]; x <= 20000; x++) {
    digitalWrite(stp, HIGH);
    delayMicroseconds(x);
    digitalWrite(stp, LOW);
    delayMicroseconds(x);
  }
  Serial.println("Done");
}

void forwardStepDefault() {
  digitalWrite(stp, HIGH);
  delayMicroseconds(rpmDelay[rpmPosition]);
  digitalWrite(stp, LOW);
  delayMicroseconds(rpmDelay[rpmPosition]);
}

int readButton() {
  int currentState = analogRead(lcdButtonPin);
  // Resting = 1023
  // Select = 610-611
  // Up = 930-931
  // Right = 814-815
  // Down = 903-904
  // Left = 855-856

  if (currentState < 809) return 5; // Select
  else if (currentState > 809 && currentState < 820) return 2; // Right
  else if (currentState > 850 && currentState < 861) return 4; // Left
  else if (currentState > 898 && currentState < 909) return 3; // Down
  else if (currentState > 925 && currentState < 936) return 1; // Up
  else if (currentState > 936) return 0;
}

String translateButton(int buttonInt) {
  switch (buttonInt) {
    case 0:
      return "Resting";
    case 1:
      return "Up";
    case 2:
      return "Right";
    case 3:
      return "Down";
    case 4:
      return "Left";
    case 5:
      return "Select";
    default:
      return "Unknown value";
  }
}

void resetPins() {
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  digitalWrite(EN, HIGH);
}
