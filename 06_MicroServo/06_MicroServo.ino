// Control steering engine
// XiaoCY 2021-11-13

int pinEngine = 11;               // PWM pin
int pulseDel = 100;               // PWM width increment

// basical properties, don't modify
float pulsePeriod = 20;           // period of reference pulse [ms]
int pulseMin = 500;               // [us]
int pulseMax = 2500;              // [us]

int pulseWid;                     // PWM width for the corresponding position
int Nrepeat = 1;                  // repeat PWM several times to ensure the servo reaches the postion

void setup() {
  // put your setup code here, to run once:
  pinMode(pinEngine, OUTPUT);
  pulseWid = pulseMin;
}

void loop() {
  // put your main code here, to run repeatedly:
  for ( int k = 0; k < Nrepeat; k++) {
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
