#include "robogkmA.h"
// gelb    -> A5 oder SCL
// weiß    -> A4 oder SDA
// rot     -> +5V
// schwarz -> Gnd



void setup() {
  // setze den Cursor nach links oben
  lcdSetCursor(0,0);
  lcdPrint("Hello");
  delay(1000);
}

void loop() {
  // leere das lcd
	lcdClear();
	lcdSetCursor(1,0);
  // gib den Messwert an A0 auf dem LCD aus
	lcdPrint( analogRead(A0) );
	delay(1000);
}
