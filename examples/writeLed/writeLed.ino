// eine Led-Leiste an pin 13

#include "robogkmA.h"

void setup() {
}

void loop() {
	//schalte die 1. LED auf rot
	writeLed(13, 0, RED);
	delay(1000);
	//schalte die 3. LED auf grün
	writeLed(13, 2, GREEN);
	delay(1000);
	//schalte die 1. LED wieder aus
	writeLed(13, 0, 0);
	delay(1000);
	//schalte die 3. LED wieder aus
	writeLed(13, 2, 0);
	delay(1000);
}
