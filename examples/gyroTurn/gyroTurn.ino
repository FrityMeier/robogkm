// faehrt ein Quadrat: 1 s geradeaus, dann mit dem Gyro (MPU-6050) 90 Grad nach rechts drehen
// Gyro am I2C-Bus: SDA an A4, SCL an A5 (Arduino Nano), VCC 5 V, GND
//
// gyroTurn(w) wartet, bis sich der Roboter um w gedreht hat (w > 0 rechts, w < 0 links).
// Die Motoren muss man vorher selbst einschalten und danach ausschalten.
// 157 entspricht 90 Grad. Weil der Roboter nach dem Ausschalten noch etwas weiterdreht,
// nimmt man weniger - den passenden Wert fuer den eigenen Roboter findet das Beispiel gyroWinkel.
#include "robogkmA.h"

const int RECHTS_90 = 135;   // ausprobieren: dreht er zu weit, kleiner machen

void setup() {
  gyro_begin();              // Gyro starten (dauert einen Moment)
  delay(1000);
}

void loop() {
  repeat(4) {
    // geradeaus
    drive(100, 100);
    delay(1000);
    // rechts herum drehen, bis der Gyro 90 Grad meldet
    drive(100, -100);
    gyroTurn(RECHTS_90);
    drive(0, 0);
    delay(300);
  }
  delay(3000);               // Pause, dann noch ein Quadrat
}
