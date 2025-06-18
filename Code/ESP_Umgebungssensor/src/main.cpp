#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <U8g2lib.h>

#define SEA_LEVEL_PRESSURE_HPA 1013.25
#define STATUS_LED 8

// Sensor
Adafruit_BME280 bme;

// Display
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("HAllo");
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setFontMode(1); // Enable font mode for text rendering
  u8g2.sendBuffer();
}

void loop()
{
  static bool bmeConnected = false;

  delay(100);

  if (!bmeConnected)
  {
    bmeConnected = bme.begin(0x76);
    delay(50);
    Serial.println("SENSOR VERBINDEN....");
    return;
  }

  const float temperature = bme.readTemperature();
  const float pressure = bme.readPressure();
  const float humidity = bme.readHumidity();
  const float altitude = bme.readAltitude(SEA_LEVEL_PRESSURE_HPA);

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Pressure = ");
  Serial.print(pressure / 100.0F);
  Serial.println(" hPa");
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");

  
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(0, 14, "Raumluft");

  u8g2.drawHLine(0, 16, 128);

  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.setCursor(0, 30);
  u8g2.printf("Temp: %.1f C", temperature);
  u8g2.setCursor(0, 40);
  u8g2.printf("Druck: %.1f hPa", pressure / 100.0F);
  u8g2.setCursor(0, 50);
  u8g2.printf("Luftfeuchte: %.1f %%", humidity);
  u8g2.setCursor(0, 60);
  u8g2.printf("Hoehe: %.1f m", altitude);

  u8g2.sendBuffer();
}