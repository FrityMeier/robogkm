#include "robogkmA.h"
// wenn der Arduino mit dem PC verbunden ist
// kann er Daten an den PC senden

int n = 0;

void setup() {
}

void loop() {
	serialPrint("hallo ");
	serialPrint(n);
	n++;
	serialNewLine();
	delay(1000);
}
