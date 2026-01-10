// ein Ultraschallsensor an Pin 12
// nutzt die eingebaute LED an Pin 13
#include "robogkmA.h"

void setup() {
	addUsSensor('v', 12, 100);
}

void loop() {
  // wenn der Ultraschallsensor ein Hindernis naeher als 100mm sieht, ...
  if( isNear('v') ){
    // ... dann geht die eingebaute LED an ...
    writeHigh(13);
  }else{
    // ... ansonsten geht sie aus
    writeLow(13);
  }
  delay(10);
}
