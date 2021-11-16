// Turn on external LEDs from digital output
// XiaoCY 2021-11-11

int pinBase = 7;
int pinNum = 3;
int turnLED = 0;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < pinNum; i++) {
    pinMode(pinBase + i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinBase + turnLED, HIGH);
  for (int i = 0; i < pinNum; i++) {
    if (i != turnLED) {
      digitalWrite(pinBase + i, LOW);
    }
  }
  
  turnLED += 1;
  if (turnLED >= pinNum) {
    turnLED = 0;
  }

  delay(200);
}
