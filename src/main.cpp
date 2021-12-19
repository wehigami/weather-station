#include <Arduino.h>
#include <Adafruit_LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C
#define rw 11

Adafruit_LiquidCrystal lcd(12, 10, 5, 4, 3, 2);

void setup()
{
  pinMode(rw, OUTPUT);
  digitalWrite(rw, LOW);
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));

  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp = ? *C");
  lcd.setCursor(0, 1);
  lcd.print("Ciśn = ? hPA");


  if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID))
  //if (!bmp.begin()) {
  {

    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    while (1)
    delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop()
{ 
  float temp = bmp.readTemperature();
  float pres = bmp.readPressure();


  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  lcd.print(temp);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("PAA = ");
  lcd.print(pres/100);
  lcd.print(" hPA");

  Serial.println();
  delay(2000);
}