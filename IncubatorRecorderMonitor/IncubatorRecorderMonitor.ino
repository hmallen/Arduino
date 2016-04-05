#define upperIncubator
#define lowerIncubator

const int upperCO2Pin = A0;
const int upperRHPin = A1;
const int upperTempPin = A2;
const int lowerCO2Pin = A3;
const int lowerRHPin = A4;
const int lowerTempPin = A5;

float upperCO2, upperRH, upperTempC, upperTempF;
float lowerCO2, lowerRH, lowerTempC, lowerTempF;

void setup() {
  Serial.begin(19200);

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
  }
}

void loop() {
  getRecorderData();

  // CO2
  Serial.println(F("       Upper   Lower"));
  Serial.print(F("CO2:   "));
  Serial.print(upperCO2);
  Serial.print(F("   "));
  Serial.println(lowerCO2);
  // Relative Humidity
  Serial.print(F("RH:    "));
  Serial.print(upperRH);
  Serial.print(F("   "));
  Serial.println(lowerRH);
  // Temperature Celsius
  Serial.print(F("TempC: "));
  Serial.print(upperTempC);
  Serial.print(F("   "));
  Serial.println(lowerTempC);
  // Temperature Fahrenheit
  Serial.print(F("TempF: "));
  Serial.print(upperTempF);
  Serial.print(F("   "));
  Serial.println(lowerTempF);

  delay(2500);
}

// Acquire and map data from external recorder outputs on back of incubators (Upper & Lower)
void getRecorderData() {
  if (upperIncubator) {
    int upperCO2Raw = analogRead(upperCO2Pin);
    upperCO2 = ((float)upperCO2Raw / 929.07) * 100.0;
    int upperRHRaw = analogRead(upperRHPin);
    upperRH = ((float)upperRHRaw / 929.07) * 100.0;
    int upperTempRaw = analogRead(upperTempPin);
    upperTempC = 45.0 - ((929.07 - (float)analogRead(upperTempPin)) * 0.1);
    upperTempF = (upperTempC * 1.8) + 32.0;
  }
  if (lowerIncubator) {
    int lowerCO2Raw = analogRead(lowerCO2Pin);
    lowerCO2 = ((float)lowerCO2Raw / 929.07) * 100.0;
    int lowerRHRaw = analogRead(lowerRHPin);
    lowerRH = ((float)lowerRHRaw / 929.07) * 100.0;
    int lowerTempRaw = analogRead(lowerTempPin);
    lowerTempC = 45.0 - ((929.07 - (float)analogRead(lowerTempPin)) * 0.1);
    lowerTempF = (lowerTempC * 1.8) + 32.0;
  }
}
