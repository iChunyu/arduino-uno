// Control steering engine
// XiaoCY 2021-11-13

int pinEngine = 11;               // PWM pin
float pulsePeriod = 20;           // period of reference pulse (ms)
int pulseMin = 500;               // (us)
int pulseMax = 2500;              // (us)
int pulseDel = 200;
int pulseWid = pulseMin;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinEngine, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for ( int k = 0; k < 50; k++) {
    // run 50 times to ensure finishing rotation
    // (each position holds 1s)
    digitalWrite(pinEngine, HIGH);
    delayMicroseconds(pulseWid);
    digitalWrite(pinEngine, LOW);
    delay(pulsePeriod-pulseWid/1000);
  }

  if ( (pulseWid >= pulseMax && pulseDel > 0) || (pulseWid <= pulseMin && pulseDel < 0) ) {
    pulseDel = -pulseDel;
  }
  pulseWid += pulseDel;
}
