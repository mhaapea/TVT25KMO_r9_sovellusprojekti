#include "Arduino.h"
#include "highscores.h"
#include "SpedenSpelit.h"
#include <EEPROM.h>

void retrieveHighscores() {
  // get highscores and save to highscores list in SpedenSpelit.ino
  for (int i = highscoreAddressStart; i < savedScoreAmount; i++) {
    EEPROM.get(i*2, highscores[i]);
  }
}

void saveHighscore(byte place, int score) {
  // can use eeprom.put since it can save int instead of byte into memory
  // check if value in the address is different from the value being saved to save on write cycles
}

void resetHighscores() {

}