#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if (!bme.begin(0x76)) 
  {
    Serial.println("Sensor nicht gefunden.");
    while (1);
  }
  PrintValues();
  delay(500);
}

void PrintValues()
{
  Serial.printf("Temperatur = %i°C",bme.readTemperature());
  Serial.printf("Luftdruck = %ihPa",bme.readPressure()/100);
  Serial.printf("Seehöhe = %im", bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.printf("Luftfeuchtigkeit = %i%", bme.readHumidity());
}