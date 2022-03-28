
const int T = 20;

// Sine wave
const double pi = 3.1415926535897932;     // http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
const double A = 3;                             // [V] Amplitude
const double b = 2;                             // [V] Bias: b - A >= 0 && b + A <= Vmax
const double f = 2;                           // [Hz] Frequency

const int N = 1e3 / (f*T);
int idx = 0;
double x[N];
double xn;


void setup() {
  Serial.begin(9600);
  idx = 0;
  for (int i = 0; i < N; i++) {
    x[i] = A * sin(2 * pi / N * i);
  }
}

void loop() {
  xn = random(65535) / 65535.0;
  Serial.println(x[idx] + xn, 16);

  idx = idx < N - 1 ? ++idx : 0;
  delay(T);
}
