/*
   TO DO:
   - User input of max speed
   -- Set variables accordingly
   - Accelerate/Deccelerate functions to initiate/halt rotation
*/

//Declare pin functions on Arduino
#define stp 2
#define dir 3
#define MS1 10
#define MS2 11
#define MS3 12
#define EN  13

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);

  resetPins(); //Set step, direction, microstep and enable pins to default states

  Serial.begin(9600); //Open Serial connection for debugging

  Serial.println();
  Serial.println("Please enter maximum speed (1-100):");
  while (!Serial.available()) {
    delay(1);
  }
  int x;
  while (Serial.available()) {
    x = Serial.read();
  }
  Serial.print("Max speed: ");
  Serial.println(x);

  Serial.println();
  Serial.println("1 - Forward");
  Serial.println("2 - Reverse");
  Serial.println("Please make a selection.");
  Serial.println("Input '0' to halt rotation.");
  Serial.println();
}

//Main loop
void loop() {
  while (Serial.available()) {
    int user_input = Serial.read(); //Read user input and trigger appropriate function

    if (user_input == '1') forwardStepDefault();
    else if (user_input == '2') reverseStepDefault();
    else Serial.println("Invalid option entered.");

    resetPins();
  }
}

void accelerateStep() {

}

void deccelerateStep() {

}

// Forward default microstep mode function
void forwardStepDefault() {
  digitalWrite(EN, LOW); //Pull enable pin low to set FETs active and allow motor control

  digitalWrite(dir, LOW); //Pull direction pin high to move in "reverse"

  while (true) {
    digitalWrite(stp, HIGH);
    delay(1);
    digitalWrite(stp, LOW);
    delay(1);

    if (Serial.available()) {
      int x = Serial.read();
      if (x == '0') break;
    }
  }
}

// Reverse default microstep mode function
void reverseStepDefault() {
  digitalWrite(EN, LOW); //Pull enable pin low to set FETs active and allow motor control

  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"

  while (true) {
    digitalWrite(stp, HIGH);
    delay(1);
    digitalWrite(stp, LOW);
    delay(1);

    if (Serial.available()) {
      int x = Serial.read();
      if (x == '0') break;
    }
  }
}

//Reset pins to default states
void resetPins() {
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  digitalWrite(EN, HIGH);
}
