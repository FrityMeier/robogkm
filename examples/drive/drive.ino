// schaltet die Motoren / Laempchen am Motortreiber an und aus
// schliesse 2 Motoren an den Motortreiber an
#include "robogkmA.h"

void setup() {
}

void loop() {
  // linker Motor 1s an
  drive(100, 0);
  delay(1000);
  // rechter Motor 1s an
  drive(0, 100); 
  delay(1000);
  // beide Motoren aus
  drive(0,0);
  delay(1000);
  // beide Motoren rueckwaerts
  drive(-100,-100);
  delay(1000);
}
