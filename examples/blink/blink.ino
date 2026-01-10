// laesst die eingebaute LED an pin 13 blinken
#include "robogkmA.h"

void setup() {
}

void loop() {
  writeHigh(13);
  delay(1000);
  writeLow(13);
  delay(1000);
}
