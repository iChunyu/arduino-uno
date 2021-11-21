#include <NewPing.h>

int trigPin = 7;
int echoPin = 8;
float maxDistance = 400.0;
float distance;

NewPing sonar(trigPin, echoPin, maxDistance);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = sonar.ping_cm();

  // Send results to Serial Monitor
  Serial.print("Distance = ");

  if (distance >= 400 || distance <= 2)
  {
    Serial.println("Out of range");
  }
  else
  {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(1000);
}
