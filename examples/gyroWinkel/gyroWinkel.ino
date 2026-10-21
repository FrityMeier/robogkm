// zeigt auf dem seriellen Monitor (9600 Baud), wie weit sich der Roboter gedreht hat
// den Roboter mit der Hand drehen - links herum wird es mehr, rechts herum weniger
// Gyro am I2C-Bus: SDA an A4, SCL an A5 (Arduino Nano), VCC 5 V, GND
//
// "Summe" ist das, was gyroTurn() zaehlt: alle 10 ms die Drehrate (rad/s) dazu.
// 157 entspricht 90 Grad. So findet man den Wert fuer gyroTurn(): Roboter mit drive() drehen,
// bei gyroTurn(w) anhalten und hier ablesen, wie weit er wirklich gedreht hat.
// Steht er still und die Zahl laeuft trotzdem langsam weg, ist das die Drift des Gyros.
#include "robogkmA.h"

double summe = 0;

void setup() {
  Serial.begin(9600);
  gyro_begin();
  delay(1000);
}

void loop() {
  repeat(10) {               // 10 x 10 ms aufsummieren, dann einmal ausgeben
    summe += imu.gz();
    delay(10);
  }
  Serial.print("Summe ");
  Serial.print(summe);
  Serial.print("   Winkel ");
  Serial.print(summe * 90.0 / 157.0);
  Serial.println(" Grad");
}
