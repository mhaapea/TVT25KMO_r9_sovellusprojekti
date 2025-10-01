#ifndef TIMER_H
#define TIMER_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const int defaultTimerSpeed = 15625;

void initializeTimer(void);

void resetTimerSpeed(void);

ISR(TIMER1_COMPA_vect);

#endif;