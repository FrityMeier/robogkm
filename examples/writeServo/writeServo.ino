// ein Servo an pin 10. Schwarzes Kabel nach aussen.

#include "robogkmA.h"

void setup() {
}

void loop() {
  // fahre Servo an pin 10 auf Position 60°
  writeServo(10, 60);
  delay(1000);
  // fahre Servo an pin 10 auf Position 120°
  writeServo(10, 120);
  delay(1000);
}
