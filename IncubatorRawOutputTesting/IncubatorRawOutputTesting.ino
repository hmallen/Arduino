#include <SPI.h>
#include <SD.h>

#define upperIncubator
#define lowerIncubator

const boolean SERIALPRINTDATA = true;
const boolean SDLOGDATA = false;

const int sdSlaveSelect = 10;

const int upperCO2Pin = A0;
const int upperRHPin = A1;
const int upperTempPin = A2;
const int lowerCO2Pin = A3;
const int lowerRHPin = A4;
const int lowerTempPin = A5;

File logFile = SD.open("incubatorlog.txt", FILE_WRITE);

int upperCO2Raw, upperRHRaw, upperTempRaw;
int lowerCO2Raw, lowerRHRaw, lowerTempRaw;

void setup() {
  Serial.begin(19200);
  pinMode(sdSlaveSelect, OUTPUT);

  for (int x = 0; x < 10; x++) {
    if (upperIncubator) {
      int analogStabilization0 = analogRead(upperCO2Pin);
      delay(100);
      int analogStabilization1 = analogRead(upperRHPin);
      delay(100);
      int analogStabilization2 = analogRead(upperTempPin);
      delay(100);
    }
    if (lowerIncubator) {
      int analogStabilization3 = analogRead(lowerCO2Pin);
      delay(100);
      int analogStabilization4 = analogRead(lowerRHPin);
      delay(100);
      int analogStabilization5 = analogRead(lowerTempPin);
      delay(100);
    }

    if (!SD
  }
}

void loop() {
  getRecorderData();

  if (SERIALPRINTDATA) {
    // Upper
    Serial.print(upperCO2Raw);
    Serial.print(F(", "));
    Serial.print(upperRHRaw);
    Serial.print(F(", "));
    Serial.println(upperTempRaw);
    // Lower
    Serial.print(lowerCO2Raw);
    Serial.print(F(", "));
    Serial.print(lowerRHRaw);
    Serial.print(F(", "));
    Serial.println(lowerTempRaw);
  }

  if (SDLOGDATA) sdLogData();

  delay(2500);
}

// Acquire and map data from external recorder outputs on back of incubators (Upper & Lower)
void getRecorderData() {
  if (upperIncubator) {
    upperCO2Raw = analogRead(upperCO2Pin);
    upperRHRaw = analogRead(upperRHPin);
    upperTempRaw = analogRead(upperTempPin);
  }
  if (lowerIncubator) {
    lowerCO2Raw = analogRead(lowerCO2Pin);
    lowerRHRaw = analogRead(lowerRHPin);
    lowerTempRaw = analogRead(lowerTempPin);
  }
}

void sdLogData() {
  String upperIncubatorData = String(upperCO2Raw) + ", " + String(upperRHRaw) + ", " + String(upperTempRaw);
  String lowerIncubatorData = String(lowerCO2Raw) + ", " + String(lowerRHRaw) + ", " + String(lowerTempRaw);
  if (logFile) {
    logFile.println(upperIncubatorData);
    logFile.println(lowerIncubatorData);
    logFile.println();
    logFile.close();
  }
}
