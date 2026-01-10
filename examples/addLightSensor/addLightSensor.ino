// schließe einen Licht-Sensor an Pin A0 an
//
// laesst den Roboter stoppen wenn der Lichtsensor "Dunkel" sieht
// und ansonsten fahren
//
// der Lichtsensor wird z.B. ueber den Buchstaben v (z.B. wie vorne) angesprochen
//
// an Pin 13 (rot) soll eine LED-Leiste angeschlossen sein
// 
// ein Schwelle von 100 ist eingestellt
#include "robogkmA.h"

void setup() {
	addLightSensor('v', A0, 100);
}

void loop() {
	if( isDark('v') ){
		drive(0,0);
	}else{
		drive(100, 100);
	}
}
