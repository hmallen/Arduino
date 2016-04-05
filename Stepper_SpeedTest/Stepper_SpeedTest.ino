#include <Stepper.h>

/*
 * Pins:
 * 2 --> Step   -- LOW-to-HIGH moves motor 1 step
 * 3 --> Dir    -- LOW = Forward / HIGH = Reverse
 * 4 --> MS1    -- 
 * 5 --> MS2    -- 
 * 6 --> MS3    -- 
 * 7 --> Enable -- HIGH = FETs Disabled / LOW = FETs Enabled
 */

const int stepsPerRevolution = 400;  // change this to fit the number of steps per revolution for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int stepCount = 0;  // number of steps the motor has taken

void setup() {
  // nothing to do inside the setup
}

void loop() {
  // read the sensor value:
  int sensorReading = analogRead(A0);
  // map it to a range from 0 to 100:
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
  // set the motor speed:
  if (motorSpeed > 0) {
    myStepper.setSpeed(motorSpeed);
    // step 1/100 of a revolution:
    myStepper.step(stepsPerRevolution / 100);
  }
}


