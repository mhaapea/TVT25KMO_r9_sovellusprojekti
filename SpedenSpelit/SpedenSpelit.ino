#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "timer.h"
#include "SpedenSpelit.h"
#include <EEPROM.h>

volatile unsigned char buttonNumber = 5;           // for buttons interrupt handler, 5 is when no button is being pressed
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
byte gameState; // 0 = before game starts, 1 = game in progress, 2 = after game is over

// score also works as a button press counter
int score;
byte ledOrder[500];
volatile int totalInterrupts;

void setup()
{
  Serial.begin(9600);
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();
  initializeTimer();
}

void loop()
{
  // Game state 0: We are in the "main menu"
  if (gameState == 0) {
    // timer interrupt used for scrolling through saved highscores/any led effects...
    if (newTimerInterrupt == true) {
      newTimerInterrupt = false;
    }

    // for now only checking when start button is pressed
    if (buttonNumber == 4) {
      buttonNumber = 5;
      startTheGame();
      Serial.println("Generated random leds and started game");
    }
  }

  // Game state 1: Game is in progress
  if (gameState == 1) {
    
    if (buttonNumber <= 4) {
      Serial.print("Pressed button: ");
      Serial.println(buttonNumber);

      // if any of the buttons were pressed, check if it was correct. if start button was pressed, end the game
      if (buttonNumber < 4) {

        if (buttonNumber == ledOrder[score]) {
          score++;
          showNumber(score);

          Serial.println("Correct button, +1 score");
          Serial.print("Score: ");
          Serial.println(score);
        } else {
          Serial.print("Incorrect button, ");
          Serial.print("correct button/led: ");
          Serial.println(ledOrder[score]);

          endTheGame();
        }
      } else {
        Serial.println("Pressed start button, ending game");
        endTheGame();
      }

      buttonNumber = 5;
    }

    if (newTimerInterrupt == true) {
      newTimerInterrupt = false;

      Serial.print("Lighting led: ");
      Serial.println(ledOrder[totalInterrupts]);
      setLed(ledOrder[totalInterrupts]);

      if (totalInterrupts >= 499) {
        Serial.println("Reached max interrupts, automatically ending game");
        endTheGame();
      }
    }
  }

  // Game state 2: Game is over
  if (gameState == 2) {
    if (newTimerInterrupt == true) {
      newTimerInterrupt = false;
      // might be used for something later
    }

    // game is over, save user score if it's better than any of the top 10 scores 
    // and move to state 0 after start button is pressed
    if (buttonNumber == 4) {
      buttonNumber = 5;
      gameState = 0;
    }
  } 
}

void initializeGame()
{
  gameState = 0;
  // get highscores from memory
}

void startTheGame()
{
  gameState = 1;
  totalInterrupts = 0;
  score = 0;
  resetTimerSpeed(); // reset timer speed to 1Hz just in case

  // fill array of leds to light up with random numbers from 0 to 3
  for (int i = 0; i < sizeof(ledOrder); i++) {
    ledOrder[i] = random(0,4);
  }

  showNumber(score);
}

void endTheGame() {
  OCR1A = 15624;
  gameState = 2;
  Serial.print("Your score: ");
  Serial.println(score);
  clearAllLeds();
}

