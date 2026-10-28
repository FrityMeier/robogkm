// zeigt auf dem seriellen Monitor (9600 Baud) die Lage vom BNO055: Kurs, Neigung, Rollen in Grad
// BNO055 am I2C-Bus: SDA an A4, SCL an A5 (Arduino Nano), VIN 5 V, GND
//
// Den Roboter mit der Hand drehen: rechts herum wird der Kurs groesser (0..359).
// Vorn anheben (wie auf einer Rampe): die Neigung aendert sich.
// "Kalibrierung" 0..3: nach dem Einschalten ein paar Sekunden stillhalten, dann steht sie auf 3.
#include "robogkmA.h"

void setup() {
  Serial.begin(9600);
  if( bno_begin() ) Serial.println("BNO055 gefunden");
}

void loop() {
  Serial.print("Kurs ");
  Serial.print(readHeading());
  Serial.print("   Neigung ");
  Serial.print(readPitch());
  Serial.print("   Rollen ");
  Serial.print(readRoll());
  Serial.print("   Kalibrierung ");
  Serial.println(readBnoCalib());
  delay(200);
}
