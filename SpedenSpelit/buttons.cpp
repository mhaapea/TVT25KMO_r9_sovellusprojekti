#include "Arduino.h"
#include "buttons.h"
#include "SpedenSpelit.h"

volatile byte lastState;
//volatile unsigned char buttonNumber = 5;   // last valid button press
volatile unsigned long lastDebounceTime[8]; // one timestamp per pin (up to D7)
const unsigned long debounceDelay = 100;     // debounce time in ms

void initButtonsAndButtonInterrupts(void)
{
  cli();

  // See requirements for this function from buttons.h
  for (int pin = firstPin; pin <= lastPin; pin++){
    pinMode(pin, INPUT_PULLUP);
    lastDebounceTime[pin] = 0;
  }
  lastState = PIND;
  PCICR |= (1 << PCIE2);     // Salli PCINT2 keskeytysryhmä
  PCMSK2 |= 0b01111100;      // Maski: valitaan D2..D6 (bitit 2–6)

  sei();
}

ISR(PCINT2_vect) {
  byte currentState = PIND;
  byte changed = currentState ^ lastState;
  lastState = currentState;

  unsigned long now = millis();

  for (int pin = firstPin; pin <= lastPin; pin++) {
    if (changed & (1 << pin)) {
      if (!(currentState & (1 << pin))) {
        // Falling (HIGH -> LOW)
        if (now - lastDebounceTime[pin] > debounceDelay) {
          buttonNumber = pin - 2;
          lastDebounceTime[pin] = now;
        }
      }
    }
  }
}