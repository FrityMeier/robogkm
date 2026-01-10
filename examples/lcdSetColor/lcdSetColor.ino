#include "robogkm4.h"

void setup() {
  lcdPrint("Farbwechsel");
  delay(1000);
}

void loop() {
  lcdClear();
  lcdPrint("gruen");
  lcdSetColor(GREEN);
  delay(1000);
  
  lcdClear();
  lcdPrint("rot");
  lcdSetColor(RED);
  delay(1000);
  
}
