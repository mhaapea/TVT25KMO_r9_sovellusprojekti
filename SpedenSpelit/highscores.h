#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <EEPROM.h>

// specifies how many scores are saved to the EEPROM
const byte savedScoreAmount = 10;

void retrieveHighscores(void);

#endif;