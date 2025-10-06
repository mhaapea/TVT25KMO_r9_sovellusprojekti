#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// specifies how many scores are saved to the EEPROM
const byte savedScoreAmount = 10;
const byte highscoreAddressStart = 0; // address 0-1023 where highscores start at in the eeprom

void retrieveHighscores(void);

void saveHighscore(byte place, int score);

void resetHighscores(void);

#endif;