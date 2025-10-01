#include "leds.h"

const byte ledPins[4] = {A2, A3, A4, A5};

void initializeLeds() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void setLed(byte ledNumber) {
  clearAllLeds();
  if (ledNumber < 4) {
    digitalWrite(ledPins[ledNumber], HIGH);
  }
}

void clearAllLeds() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void setAllLeds() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

void show1() {
  for (int i = 0; i < 16; i++) {
    for (int bit = 0; bit < 4; bit++) {
      digitalWrite(ledPins[bit], (i >> bit) & 1);
    }
    delay(500);
  }
  clearAllLeds();
}

void show2(int rounds) {
  int delayTime = 500;

  for (int i = 0; i < rounds; i++) {
    for (int led = 0; led < 4; led++) {
      clearAllLeds();
      digitalWrite(ledPins[led], HIGH);
      delay(delayTime);
    }
    if (delayTime > 100) {
      delayTime -= 20;
    }
  }
  clearAllLeds();
}

void loop() {
  byte led = random(0, 4);
  setLed(led);
  delay(300);
  clearAllLeds();
  delay(200);
}
