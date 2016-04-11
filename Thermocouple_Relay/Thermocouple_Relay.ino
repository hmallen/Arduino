/*
   -- Thermocouple Controlled Relay --

   Opens and closes 120V/10A relay based on
   temperature readings from thermocouple with
   MAX6675 thermocouple amplifier

*/

#include <max6675.h>

#define thermGND 2
#define thermVCC 3
#define thermSO 4
#define thermCS 5
#define thermSCK 6

#define relayPin A0

MAX6675 thermocouple(thermSCK, thermCS, thermSO);

float relayTriggerF = 212.0;
boolean relayState = false;
boolean relayStateLast = relayState;

void setup() {
  Serial.begin(57600);

  pinMode(thermGND, OUTPUT); digitalWrite(thermVCC, HIGH);
  pinMode(thermVCC, OUTPUT); digitalWrite(thermGND, LOW);
  pinMode(relayPin, OUTPUT); digitalWrite(relayPin, HIGH);

  Serial.println();
  Serial.println();
  Serial.println("Beginning thermocouple reading.");
  Serial.println();
  Serial.print("Set Temp: ");
  Serial.println(relayTriggerF);
  Serial.println();
  delay(500);
}

void loop() {
  //float tempC = thermocouple.readCelsius();
  float calibVal = -16.0;
  float tempFUncalibrated = thermocouple.readFahrenheit();
  float tempF = tempFUncalibrated + calibVal;

  if (Serial.available()) {
    while (Serial.available()) {
      char c = Serial.read();
      int charPos = 0;

      if (c == 'i') {
        String tempInput;
        while (!Serial.available()) {
          ;
        }
        while (Serial.available()) {
          c = Serial.read();
          tempInput += c;
          delay(10);
        }

        relayTriggerF = tempInput.toFloat();
        Serial.println();
        Serial.print("New Set Temp: ");
        Serial.println(String(relayTriggerF));
        Serial.println();
      }
    }
  }

  //Serial.print("C = ");
  //Serial.print(tempC);
  //Serial.print(" / F = ");
  Serial.print("Temperature (F): ");
  Serial.println(tempF);

  if (tempF >= relayTriggerF) {
    digitalWrite(relayPin, HIGH);
    relayState = false;
  }
  else {
    digitalWrite(relayPin, LOW);
    relayState = true;
  }

  if (relayState != relayStateLast) {
    Serial.println();
    Serial.print("Relay ");
    if (relayState == false) Serial.println("OFF");
    else Serial.println("ON");
    Serial.println();
  }

  relayStateLast = relayState;

  delay(1000);
}
