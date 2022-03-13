
int DACPin = 11;
int ADCPin = A0;
const double pi = 3.14159265358979323846264338327;    // http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html

double T = 100;       // [ms] Time unit
double A = 2.5;     // [V] Amplitude
double b = 2.5;     // [V] Bias: b - A >= 0 && b + A <= Vmax
double f = 0.25;       // [Hz] Frequency
double Vmax = 5;    // [V] VCC
double Omega = 2 * pi * f * T * 1e-3; // Digital frequency

double Vout;
double Vin;
double DACScale = pow(2, 8) / Vmax;
double ADCScale = Vmax / pow(2, 10);

int n;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(DACPin, OUTPUT);
  n = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  Vout = A * sin(Omega * n) + b;
  analogWrite(DACPin, int(Vout * DACScale));
  Vin = double(analogRead(ADCPin));
  Serial.println(Vin * ADCScale, DEC);
  n = n + 1;
  delay(T);
}
