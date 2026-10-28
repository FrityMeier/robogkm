// faehrt ein Quadrat: 1 s geradeaus, dann mit dem BNO055 90 Grad nach rechts drehen
// BNO055 am I2C-Bus: SDA an A4, SCL an A5 (Arduino Nano), VIN 5 V, GND
//
// bnoTurn(w) wartet, bis sich der Roboter um w Grad gedreht hat (w > 0 rechts, w < 0 links).
// Die Motoren muss man vorher selbst einschalten und danach ausschalten.
// Anders als beim Gyro (gyroTurn) sind das echte Grad. Weil der Roboter nach dem Ausschalten
// noch etwas weiterdreht, nimmt man etwas weniger als 90 - ausprobieren.
#include "robogkmA.h"

const int RECHTS_90 = 80;    // dreht er zu weit, kleiner machen

void setup() {
  bno_begin();               // BNO055 starten
  delay(1000);               // stillhalten, damit sich der Gyro einpendelt
}

void loop() {
  repeat(4) {
    // geradeaus
    drive(100, 100);
    delay(1000);
    // rechts herum drehen, bis der BNO055 90 Grad meldet
    drive(100, -100);
    bnoTurn(RECHTS_90);
    drive(0, 0);
    delay(300);
  }
  delay(3000);               // Pause, dann noch ein Quadrat
}
