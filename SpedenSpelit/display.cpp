#include "display.h"

char resetPin = 12;    // kytketty SRCLR(shift register clear), käytetään resetti pinninä
char clockPin = 11;    // kytketty SRCLK(shift register clock), data siirtyy siirtorekisteriin kun signaali vaihtuu LOW -> HIGH
char latchPin = 10;    // kytketty RCLK(register clock/latch pin), data siirtyy siirtorekisteristä, kun signaali vaihtuu LOW -> HIGH
char enablePin = 9;    // kytketty OE(output enable), toimii kytkimenä outputeille. LOW asemassa rekisterin output pinnit auki, HIGH asemassa kiinni.
char dataPin = 8;      // kytketty SER(serial input), siirtää datan bitti kerrallaan siirtorekisterille.

byte segLuku[] = {
  B00111111, 	// 0
  B00001001, 	// 1
  B01011110, 	// 2
  B01011011,	// 3
  B01101001,	// 4
  B01110011,	// 5
  B01110111,	// 6
  B00011001,	// 7
  B01111111,	// 8
  B01111001 	// 9
}

void initializeDisplay(void)
{
  cli();

  pinMode(resetPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);        // lähtöpinnit OUTPUT moodiin
  pinMode(enablePin, OUTPUT);
  pinmode(dataPin, OUTPUT);
  digitalWrite(resetPin, LOW);      // LOW resettaa sarjarekisterin kaikki bitit nolliksi
  digitalWrite(resetPin, HIGH);     // poistaa resetin
  digitalWrite(enablePin, LOW);     // pidetään output pinnit auki

  sei();
}

void writeDisplay(uint8_t hundreds, uint8_t firstNumber, uint8_t secondNumber) {
  digitalWrite(latchPin, LOW);   //valmistellaan datan siirto
  
  byte dot = B10000000;
  byte tens = segLuku[firstNumber];
  byte ones = segLuku[secondNumber];
  
  // koska käytössä on vain kaksi näyttöä, pitää sytyttää näyttöjen pisteet että saadaan ns. isompia lukuja
  // näillä if-lauseilla näyttöjen pisteitä voi käyttää binäärilukuina
  // esim. jos luku on 100, syttyy vain toisen näytön piste.
  // jos luku on 200, syttyy vain ensimmäisen näytön piste
  // jos luku on 300, syttyy molemmat pisteet, tällä isoin numero mitä voi näyttää on 399
  if (hundreds == 1 || hundreds == 3) {
    // OR operaatio eli |-merkki muuttaa byten ensimmäisen bitin 1:ksi eli sytyttää pisteen
    ones |= dot;
  }
  if (hundreds == 2 || hundreds == 3) {
    tens |= dot;   // add dot to firstNumber
  }
  
  shiftOut(dataPin, clockPin, LSBFIRST, ones);	//Siirretään ensimmäiset bitit rekisterille
  shiftOut(dataPin, clockPin, LSBFIRST, tens);  // kun toiset bitit siirretään, edelliset bitit siirtyy toiselle rekisterille
  digitalWrite(latchPin, HIGH);  //data siirtyy siirtorekisteriltä ulostuloihin
}

void showNumber(int numberToDisplay) {
  byte hundreds = numberToDisplay / 100;
  numberToDisplay -= hundreds * 100;
  
  byte tens = numberToDisplay / 10;
  numberToDisplay -= tens * 10;
  
  byte ones = numberToDisplay;
  
  writeDisplay(hundreds, tens, ones);
}


void writeByte(uint8_t bits,bool last)
{
  // ei varmaan tarvi


  // bool last on sitä varten jos rekisterit on kytketty toisiinsa
  // jos käytetään pin 13 toisen rekisterin dataPinninä niin sitä ei varmaan tarvi
  digitalWrite(latchPin, LOW);   //valmistellaan datan siirto
  shiftOut(dataPin, clockPin, LSBFIRST, bits);	//Siirretään bitit rekisterille
  digitalWrite(latchPin, HIGH);  //data siirtyy siirtorekisteriltä ulostuloihin
}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
  // ei varmaan tarvi
}

void showResult(byte number)
{
  // ei varmaan tarvi
}

