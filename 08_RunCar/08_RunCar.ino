int l1 = 8;
int r1 = 9;
int l2 = 10;
int r2 = 11;

bool ledx = LOW;
char cmd;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(l1, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(LED_BUILTIN, ledx);
}

void loop() {
  // put your main code here, to run repeatedly:
  cmd = Serial.read();
  if (cmd == 'g') {
    digitalWrite(l1, HIGH);
    digitalWrite(r1, HIGH);
    digitalWrite(l2, LOW);
    digitalWrite(r2, LOW);
    delay(500);
  }
  else if (cmd == 'b') {
    digitalWrite(l1, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(l2, HIGH);
    digitalWrite(r2, HIGH);
    delay(500);
  }
  else if (cmd == 'l') {
    digitalWrite(l1, LOW);
    digitalWrite(r1, HIGH);
    digitalWrite(l2, HIGH);
    digitalWrite(r2, LOW);
    delay(200);
  }
  else if (cmd == 'r') {
    digitalWrite(l1, HIGH);
    digitalWrite(r1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(r2, HIGH);
    delay(200);
  }
  else if (cmd == 'x') {
    digitalWrite(l1, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(r2, LOW);

    ledx = !ledx;
    digitalWrite(LED_BUILTIN, ledx);
  }

  cmd = 'n';
  digitalWrite(l1, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(r2, LOW);
}
