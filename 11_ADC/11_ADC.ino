// Sampling data with built-in ADC
// PWM sine wave are filtered by external first order filter with R = 10 kOhm and C = 10e4 pF.
// XiaoCY 2022-03-13

// PWM frequency:
//   PIN 5,6: 16 MHz / 64 / 256 = 976.56 Hz
//   PIN (others): 16 MHz / 64 / 510 = 490.20 Hz
//   Ref: https://www.etechnophiles.com/change-frequency-pwm-pins-arduino-uno/

int PWMPin = 5;
int ADCPin = A0;
double Vmax = 5;                            // [V] VCC
double T = 100;                             // [ms] Time unit (ADC sampling period)
double PWMScale = pow(2, 8) / Vmax;         // Desired voltage to DAC(PWM) code
double ADCScale = Vmax / pow(2, 10);        // ADC code to measured voltage

// Sine wave
const double pi = 3.14159265358979323846264338327;            // http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
double A = 2;                               // [V] Amplitude
double b = 2.5;                             // [V] Bias: b - A >= 0 && b + A <= Vmax
double f = 0.1;                             // [Hz] Frequency
double Omega = 2 * pi * f * T * 1e-3;       // Digital frequency

int n = 0;
double Vref;
double Vout;
double Vin;
double Verr;

bool isOpen = true;                         // chose 'DAC(PWM)' works in open-loop or closed-loop (noise shaping)
double Kp = 0.3;
double Ki = 0.6;
double xc = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PWMPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Vref = A * sin(Omega * n) + b;
  Vin = double(analogRead(ADCPin)) * ADCScale;
  Serial.println(Vin , DEC);

  if (isOpen) {
    Vout = Vref;
  }
  else {
    Verr = Vref - Vin;
    xc += Verr;
    Vout = Kp * Verr + Ki * xc;
  }

  analogWrite(PWMPin, int(Vout * PWMScale));
  n = n + 1;
  delay(T);
}
