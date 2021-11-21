#include <NewPing.h>

int trigPin = 7;
int echoPin = 8;

int L1 = 5;
int L2 = 6;
int R1 = 10;
int R2 = 11;

float maxDistance = 400.0;
float distance;
float target = 10;
float tol = 1;

int leftPin = 3;
int rightPin = 2;
bool leftFree;
bool rightFree;

NewPing sonar(trigPin, echoPin, maxDistance);

void setup() {
  // put your setup code here, to run once:
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = sonar.ping_cm();
  leftFree = digitalRead(leftPin);
  rightFree = digitalRead(rightPin);

  Serial.print(leftFree);
  Serial.println(rightFree);
  if (distance > target + tol) {
    if (leftFree && !rightFree) {
      analogWrite(L1, 250);
      analogWrite(L2, 0);
      analogWrite(R1, 150);
      analogWrite(R2, 0);
    }
    else if  (!leftFree && rightFree) {
      analogWrite(L1, 150);
      analogWrite(L2, 0);
      analogWrite(R1, 250);
      analogWrite(R2, 0);
    }
    else {
      analogWrite(L1, 200);
      analogWrite(L2, 0);
      analogWrite(R1, 200);
      analogWrite(R2, 0);
    }
  }
  else if (distance < target - tol) {
    if (leftFree && !rightFree) {
      analogWrite(L1, 0);
      analogWrite(L2, 150);
      analogWrite(R1, 0);
      analogWrite(R2, 250);
    }
    else if  (!leftFree && rightFree) {
      analogWrite(L1, 0);
      analogWrite(L2, 250);
      analogWrite(R1, 0);
      analogWrite(R2, 150);
    }
    else {
      analogWrite(L1, 0);
      analogWrite(L2, 200);
      analogWrite(R1, 0);
      analogWrite(R2, 200);
    }
  }
  else {
    analogWrite(L1, 0);
    analogWrite(L2, 0);
    analogWrite(R1, 0);
    analogWrite(R2, 0);
  }

  delay(10);
}
