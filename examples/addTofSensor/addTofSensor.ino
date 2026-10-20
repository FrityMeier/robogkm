// ToF-Abstandssensor (VL53L0X) am I2C-Bus (A4 = SDA, A5 = SCL)
// nutzt die eingebaute LED an Pin 13 und gibt den Abstand auf dem seriellen Monitor aus
// Mehrere Sensoren: jeder bekommt einen XSHUT-Pin, z. B. addTofSensor('l', 4, 150);
#include "robogkmA.h"

void setup() {
  Serial.begin(9600);
  addTofSensor('v', 100);   // ein Sensor ohne XSHUT, Schwelle 100 mm
}

void loop() {
  Serial.println(readTof('v'));   // Abstand in mm, 9999 = nichts im Messbereich
  // wenn der ToF-Sensor ein Hindernis naeher als 100 mm sieht, ...
  if( isNear('v') ){
    // ... dann geht die eingebaute LED an ...
    writeHigh(13);
  }else{
    // ... ansonsten geht sie aus
    writeLow(13);
  }
  delay(50);
}
