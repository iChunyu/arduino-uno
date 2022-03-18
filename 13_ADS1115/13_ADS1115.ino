// Try ADS1115 16-bit ADC, detect 3.3 V source voltage
// Ref: [1] http://arduinolearning.com/code/ads1115-analog-to-digital-converter-and-arduino.php
//      [2] https://github.com/adafruit/Adafruit_ADS1X15/blob/master/examples/singleended/singleended.ino
// XiaoCY 2022-03-17

// ADS1115
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;

double Vmax = 5;                          // [V] VCC
double T = 100;                           // [ms] Time unit (ADC sampling period)

double Vin;
int16_t ADSCode;

void setup() {
  Serial.begin(9600);
  ads.begin();
}

void loop() {
  ADSCode = ads.readADC_SingleEnded(0);
  Vin = ads.computeVolts(ADSCode);
  Serial.println(Vin , DEC);
  delay(T);
}
