// Read command from UART to on/off LEDs
// XiaoCY 2021-11-12

int pinLED[] = {7, 8, 9};
bool statusLED[] = {LOW, LOW, LOW};
int numLED = sizeof(pinLED)/sizeof(pinLED[0]);
char cmd;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < numLED; i++) {
    pinMode(pinLED[i], OUTPUT);
    digitalWrite(pinLED[i], statusLED[i]);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  cmd = Serial.read();
  if (cmd == 'Y' || cmd == 'y') {
    statusLED[0] = !statusLED[0];
  }
  else if (cmd == 'G' || cmd == 'g') {
    statusLED[1] = !statusLED[1];
  }
  else if (cmd == 'R' || cmd == 'r') {
    statusLED[2] = !statusLED[2];
  }

  for (int i = 0; i < numLED; i++) {
    digitalWrite(pinLED[i], statusLED[i]);
  }
}
