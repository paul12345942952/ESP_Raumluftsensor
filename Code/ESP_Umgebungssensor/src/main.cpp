#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void PrintValues()
{
  Serial.printf("Temperatur = %i°C\n",bme.readTemperature());
  Serial.printf("Luftdruck = %ihPa\n",bme.readPressure()/100);
  Serial.printf("Seehöhe = %im\n", bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.printf("Luftfeuchtigkeit = %i%\n\n", bme.readHumidity());
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("START");
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

