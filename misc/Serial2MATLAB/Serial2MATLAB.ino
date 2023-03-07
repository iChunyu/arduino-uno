
const int T = 20;

// Sine wave
const double pi = 3.1415926535897932;           // http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
const double A = 1;                             // [V] Amplitude
const double b = 2;                             // [V] Bias
const double f = 0.5;                           // [Hz] Frequency

const int N = 1e3 / (f*T);
int idx = 0;
double x[N];

void setup() {
  Serial.begin(9600);
  idx = 0;
  for (int i = 0; i < N; i++) {
    x[i] = A * sin(2 * pi / N * i) + b;
  }
}

void loop() {
  /** Serial.print
  If you use `Serial.print(num, digits)` in Arduino and specify digits, you may use `read(device, count, 'char')` in MATLAB.
  Note that: 
    1. `count`(MATLAB) is the sum of digits of the Arduino output, while `digits`(Arduino) is the number of decimal places;
    2. Arduino always send data decoded by ASCII, so MATLAB should read data with `char` (or `string`) option.
  WARNING: negative value may fail because the ASCII data length changed (an extra '-' sign).
  **/
  Serial.print(x[idx], 16);         // MATLAB: s.read(18,'char')

  /** Serial.println
  If you use `Serial.println(num, digits)` in Arduino and specify digits, you may use `readline` in MATLAB.
  Since `\r\n` denotes the end of the line, and `readline`(MATLAB) deals with ASCII data, no extra process is needed.
  **/
  //  Serial.println(x[idx], 16);       // MATLAB: s.readline

  idx = idx < N - 1 ? ++idx : 0;
  delay(T);
}
