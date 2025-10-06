#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile unsigned char buttonNumber;
extern volatile bool newTimerInterrupt;
extern volatile int totalInterrupts;
extern volatile int highscores[10];
extern byte gameState;

/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
void initializeGame(void);


/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startTheGame(void);

/*
  endTheGame() subroutine sets the game state to 2 and resets timer speed
*/
void endTheGame(void);

#endif