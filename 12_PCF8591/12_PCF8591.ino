// Try PCF8591 DAC output
// Ref: https://www.instructables.com/Arduino-and-PCF8591-ADC-DAC-IC/
// XiaoCY 2022-03-16

#include "Wire.h"

// I2C bus address (see P13, Tab5)
#define PCF8591 (0x90 >> 1)               // [1001 0000] 

// DAC control bit (see P6, Fig4)
#define DAC 0x40                          // [0100 0000] 
// ADC control bit (see P6, Fig4) --> (0x4*: use DAC at the same time, else: 0x0*)
#define ADC0 0x40                         // [0100 0000]
#define ADC1 0x41                         // [0100 0001]
#define ADC2 0x42                         // [0100 0010]
#define ADC3 0x43                         // [0100 0011]

double Vmax = 5;                          // [V] VCC
double T = 100;                           // [ms] Time unit (ADC sampling period)
double DACScale = pow(2, 8) / Vmax;       // Desired voltage to DAC(PCF8591) code
double ADCScale = Vmax / pow(2, 8);       // ADC (PCF8591) code to measured voltage

// Sine wave
const double pi = 3.1415926535897932;     // http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
double A = 1;                             // [V] Amplitude
double b = 3;                             // [V] Bias: b - A >= 0 && b + A <= Vmax
double f = 0.2;                           // [Hz] Frequency
double Omega = 2 * pi * f * T * 1e-3;     // Digital frequency

int n;
double Vout;
double Vin;
int Vint;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  n = 0;
}

void loop() {
  Vout = A * sin(Omega * n) + b;
  Wire.beginTransmission(PCF8591);        // wake up PCF8591
  Wire.write(DAC);                        // turn on DAC
  Wire.write(int(Vout * DACScale));       // value to send to DAC
  Wire.endTransmission();                 // end tranmission

  Wire.beginTransmission(PCF8591);        // wake up PCF8591
  Wire.write(ADC1);                       // turn on ADC1
  Wire.endTransmission();                 // end tranmission
  Wire.requestFrom(PCF8591, 2);
  Vint = Wire.read();                     // previous data (see P8, Fig8)
  Vint = Wire.read();                     // current data
  
  Vin = double(Vint) * ADCScale;
  Serial.println(Vin , DEC);

  n += 1;
  delay(T);
}
