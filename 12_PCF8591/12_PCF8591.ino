// Try PCF8591 DAC output
// Ref: https://www.instructables.com/Arduino-and-PCF8591-ADC-DAC-IC/
// XiaoCY 2022-03-16

#include "Wire.h"
#define PCF8591 (0x90 >> 1)               // I2C bus address

int ADCPin = A0;
double Vmax = 5;                          // [V] VCC
double T = 100;                           // [ms] Time unit (ADC sampling period)
double DACScale = pow(2, 8) / Vmax;       // Desired voltage to DAC(PCF8591) code
double ADCScale = Vmax / pow(2, 10);      // ADC (built-in) code to measured voltage

// Sine wave
const double pi = 3.14159265358979323846264338327;     // http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
double A = 2;                             // [V] Amplitude
double b = 2.5;                           // [V] Bias: b - A >= 0 && b + A <= Vmax
double f = 0.2;                           // [Hz] Frequency
double Omega = 2 * pi * f * T * 1e-3;     // Digital frequency

int n = 0;
double Vout;
double Vin;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Vout = A * sin(Omega * n) + b;
  Wire.beginTransmission(PCF8591);        // wake up PCF8591
  Wire.write(0x40);                       // control byte - turn on DAC (binary 1000000)
  Wire.write(int(Vout * DACScale));       // value to send to DAC
  Wire.endTransmission();                 // end tranmission

  Vin = double(analogRead(ADCPin)) * ADCScale;
  Serial.println(Vin , DEC);

  n += 1;
  delay(T);
}
