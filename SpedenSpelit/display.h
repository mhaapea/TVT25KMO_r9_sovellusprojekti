#ifndef DISPLAY_H
#define DISPLAY_H
#include <arduino.h>


/*
  initializeDisplay subroutine initializes 5 pins needed for controlling 7-segment
  displays in a cascade as follows:
  Arduino pin 12 = serial to parallel component reset
  Arduino pin 11 = serial to parallel component shiftClock
  Arduino pin 10 = serial to parallel component latchClock
  Arduino pin 9  = serial to parallel component outEnable
  Arduino pin 8  = serial to parallel component serialInput
  

*/
void initializeDisplay(void);

/*
  writeDisplay writes a number to the displays using hundreds, tens and ones
  7-segment display's dot segments are used as binary to represents numbers up to 399
*/
void writeDisplay(uint8_t hundreds, uint8_t firstNumber, uint8_t secondNumber);

/*
  showNumber separates hundreds, tens and ones from a number and 
  calls writeDisplay to show the number on the 7-segment display
*/
void showNumber(int numberToDisplay);

#endif
