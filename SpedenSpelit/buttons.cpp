#include "Arduino.h"
#include "buttons.h"
#include "SpedenSpelit.h"
volatile byte lastState;
void initButtonsAndButtonInterrupts(void)
{
  // See requirements for this function from buttons.h
  for (int pin = firstPin; pin <= lastPin; pin++){
    pinMode(pin, INPUT_PULLUP);
  }
  lastState = PIND;
  PCICR |= (1 << PCIE2);     // Salli PCINT2 keskeytysryhmä
  PCMSK2 |= 0b01111100;      // Maski: valitaan D2..D6 (bitit 2–6)
}

ISR(PCINT2_vect) {
  byte currentState = PIND;
  byte changed = currentState ^ lastState;
  lastState = currentState;

  for (int pin = firstPin; pin <= lastPin; pin++) {
    if (changed & (1 << pin)) {
      if (!(currentState & (1 << pin))) {
        // Falling (HIGH -> LOW)
        buttonNumber = pin - 2;
      }
    }
  }
}