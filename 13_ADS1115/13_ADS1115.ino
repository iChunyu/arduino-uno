// Try ADS1115 16-bit ADC
// Use PCF8591 to write analog sine wave to be sampled by ADS1115
// Ref: https://github.com/adafruit/Adafruit_ADS1X15/blob/master/examples/singleended/singleended.ino
// XiaoCY 2022-03-17

// PCF8591
#include "Wire.h"
#define PCF8591 (0x90 >> 1)               // I2C bus address

// ADS1115
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;


double Vmax = 5;                          // [V] VCC
double T = 100;                           // [ms] Time unit (ADC sampling period)
double DACcale = pow(2, 8) / Vmax;       // Desired voltage to DAC(PCF8591) code
double ADCScale = Vmax / pow(2, 16);      // ADC (ADS1115) code to measured voltage

// Sine wave
const double pi = 3.14159265358979323846264338327;     // http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
double A = 2;                             // [V] Amplitude
double b = 2.5;                           // [V] Bias: b - A >= 0 && b + A <= Vmax
double f = 0.1;                           // [Hz] Frequency
double Omega = 2 * pi * f * T * 1e-3;     // Digital frequency

int n = 0;
double Vout;
double Vin;
int16_t ADSCode;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  ads.begin();
}

void loop() {
  Vout = A * sin(Omega * n) + b;
  Wire.beginTransmission(PCF8591);        // wake up PCF8591
  Wire.write(0x40);                       // control byte - turn on DAC (binary 1000000)
  Wire.write(int(Vout * DACcale));       // value to send to DAC
  Wire.endTransmission();                 // end tranmission

  ADSCode = ads.readADC_SingleEnded(0); 
  Vin = ADSCode * ADCScale;
  Serial.println(Vin , DEC);

  n += 1;
  delay(T);
}
