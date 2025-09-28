#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

volatile unsigned char buttonNumber = 5;           // for buttons interrupt handler, 5 is when no button is being pressed
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
byte gameState; // 0 = before game starts, 1 = game in progress, 2 = after game is over

// score also works as a button press counter
int score;
byte ledOrder[500];
int totalInterrupts;

void setup()
{
  Serial.begin(9600);
  initButtonsAndButtonInterrupts();
  //init leds here
  //init display here
  initializeTimer();
}

// test kommenti

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

    // check button presses
    if (buttonNumber >= 0)
    {
      Serial.print("Pressed button: ");
      Serial.println(buttonNumber);

      // if any of the buttons were pressed, check if it was correct. if start button was pressed, end the game
      if (buttonNumber <= 3) {
        if (buttonNumber == ledOrder[score]) {
          score++;

          Serial.println("Correct button, +1 score");
          Serial.print("Score: ");
          Serial.println(score);
        } else {
          Serial.print("Incorrect button, ");
          Serial.print("correct button/led: ");
          Serial.println(ledOrder[score]);

          // disabled for now because no debounce yet in buttons
          //endTheGame();
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

void initializeTimer(void)
{
	cli();
  
  TCCR1A = 0; // B00000000
  TCCR1B = (1 << WGM12); // B00001000 (CTC mode)
  TCCR1B |= (1 << CS12) | (1 << CS10); // B00000100, prescaler is 1024, previously with only CS12 = 256. used when calculating timer speed
  // result is TCCR1B = B00001100;

  TIMSK1 = (1 << OCIE1A);
  // TIMSK1 = B00000010;

  // (16 000 000 / 1024 * 1) - 1 = 15624 
  OCR1A = 15624; // 1Hz, timer resets when it hits this value
  //Serial.println(OCR1A);

  sei();
}

ISR(TIMER1_COMPA_vect)
{
  newTimerInterrupt = true;

  // check if led has been lit 10 times by checking if totalInterrupts is divisible by 10
  if (totalInterrupts % 10 == 0) {
    int multiplier = totalInterrupts / 10;
    float timerSpeed = 1 + (0.1 * multiplier);
    // round float to int before assigning to OCR1A
    OCR1A = (16000000.0 / 1024.0 / timerSpeed) - 1;
    
    Serial.println(timerSpeed);
  }

  totalInterrupts += 1;
}

void checkGame(byte pushedButton)
{
  
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
  OCR1A = 15624; // reset timer speed to 1Hz just in case

  // fill array of leds to light up with random numbers from 0 to 3
  for (int i = 0; i < sizeof(ledOrder); i++) {
    ledOrder[i] = random(0,4);
  }
}

void endTheGame() {
  OCR1A = 15624;
  gameState = 2;
  Serial.print("Your score: ");
  Serial.println(score);
}

