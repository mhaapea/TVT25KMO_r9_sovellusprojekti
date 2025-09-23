#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile int buttonNumber;

/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
  
*/
void initializeTimer(void);
// Intoduce TIMER1_COMPA_vect Interrupt SeRvice (ISR) function for timer.
ISR(TIMER1_COMPA_vect);

// Increases timer speed by 10%
void increaseTimerSpeed(void);

/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
void initializeGame(void);

/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/
void checkGame(byte);


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