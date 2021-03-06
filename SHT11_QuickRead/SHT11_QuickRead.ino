/*
 * ReadSHT1xValues
 *
 * Read temperature and humidity values from an SHT1x-series (SHT10,
 * SHT11, SHT15) sensor.
 *
 * Copyright 2009 Jonathan Oxer <jon@oxer.com.au>
 * www.practicalarduino.com
 */

#include <SHT1x.h>

// Specify data and clock connections and instantiate SHT1x object
#define sdaPin  20
#define sclPin 21
SHT1x sht1x(sdaPin, sclPin);

void setup() {
  Serial.begin(19200); // Open serial connection to report values to host

  sht1x.readTemperatureC();
  sht1x.readTemperatureF();
  sht1x.readHumidity();

  delay(5000);
  Serial.println(F("Ready."));
}

void loop() {
  float temp_c;
  float temp_f;
  float humidity;

  // Read values from the sensor
  temp_c = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();

  // Print the values to the serial port
  Serial.print(temp_c, 2);
  Serial.print("C / ");
  Serial.print(temp_f, 2);
  Serial.print("F / ");
  Serial.print(humidity, 2);
  Serial.println("%");

  delay(5000);  // Must allow ~5sec b/w reads to prevent self-heating
}
