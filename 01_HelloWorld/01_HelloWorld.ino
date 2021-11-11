// Send messages from UART.
// XiaoCY 2021-11-11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Greetings from Arduino UNO: ");
  Serial.println("Hello World!");
  // Serial.print("Hello World!\r\n");         // This does the same as above.
  delay(2000);
}
