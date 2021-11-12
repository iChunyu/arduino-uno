// Show breathing LED using PWM techonology
// XiaoCY 2021-11-12

int pinPWM = 11;      //  avaliable for UNO: 3, 5, 6, 9, 10, 11
int valPWM = 0;
int delPWM = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinPWM, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( (valPWM >= 255 && delPWM > 0) || (valPWM <= 0 && delPWM < 0) ) {
    delPWM = -delPWM;
  }
  valPWM += delPWM;
  analogWrite(pinPWM, valPWM);
  delay(30);
}
