#include "Arduino.h"
#include "timer.h"
#include "SpedenSpelit.h"

//volatile bool newTimerInterrupt = false;
//volatile int totalInterrupts;

void initializeTimer(void)
{
	cli();
  
  TCCR1A = 0; // B00000000
  TCCR1B = (1 << WGM12); // B00001000 (CTC mode)
  TCCR1B |= (1 << CS12) | (1 << CS10); // B00000100, prescaler is 1024, previously with only CS12 = 256. used when calculating timer speed
  // result is TCCR1B = B00001101;

  TIMSK1 = (1 << OCIE1A);
  // TIMSK1 = B00000010;

  // (16 000 000 / 1024 * 1) - 1 = 15624 
  OCR1A = defaultTimerSpeed - 1; // 1Hz, timer resets when it hits this value
  //Serial.println(OCR1A);

  sei();
}

ISR(TIMER1_COMPA_vect)
{
  newTimerInterrupt = true;

  if (gameState == 1) {
    // check if led has been lit 10 times by checking if totalInterrupts is divisible by 10
    if (totalInterrupts % 10 == 0) {
      // stop timer interrupts by resetting prescalers
      TCCR1B = (1 << WGM12);

      // multiplier is totalInterrupts divided by 10
      float timerSpeed = 1 + (0.1 * (totalInterrupts / 10));
      int value = round(defaultTimerSpeed / timerSpeed);

      OCR1A = value - 1;
      Serial.println(OCR1A);

      // set counter to 0 and set prescalers to enable timer
      TCNT1 = 0;
      TCCR1B |= (1 << CS12) | (1 << CS10); 
    }

    //totalInterrupts += 1;
  }
}

void resetTimerSpeed() {
  OCR1A = defaultTimerSpeed - 1;
}