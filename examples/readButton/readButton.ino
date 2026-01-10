// Ein Taster wird an Pin A1 angeschlossen
// damit wird die eingebaute LED an Pin 13 an und ausgeschaltet
#include "robogkm4.h"

void setup() {
}

void loop() {
  if( readButton(A1) == HIGH ){
    writeHigh(13);
  }else{
    writeLow(13);	
  }
}
