// eine Led-Leiste an pin 13

#include "robogkmA.h"

void setup() {
}

void loop() {
  // Schalte alle LEDs auf "rot"
  writeLeds(13, RED, RED, RED, RED, RED);
  delay(1000);
  // Schalte alle LEDs auf "gruen"
  writeLeds(13, GREEN, BLUE, GREEN, BLUE, GREEN);
  delay(1000);
  // Schalte alle LEDs aus
  writeLeds(13, BLACK, BLACK, YELLOW, BLACK, BLACK);
  delay(1000);
}
