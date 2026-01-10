#include "robogkmA.h"
// gelb    -> A5 oder SCL
// weiß    -> A4 oder SDA
// rot     -> +5V
// schwarz -> Gnd

// legt eine Variable an
float temp;

void setup() {
	Serial.begin(9600);
}

void loop() {
	// liest die Temperatur aus und
	// speichert sie in einer Variablen
	temp = readTemp();
	// gibt die Variable über die serielle Schnittstelle aus
	Serial.println(temp);
	delay(1000);
}
