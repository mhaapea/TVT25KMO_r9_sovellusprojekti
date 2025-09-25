#include "display.h"

char resetPin = 12;    //kytketty SRCLR(shift register clear), käytetään resetti pinninä
char clockPin = 11;    //kytketty SRCLK(shift register clock), data siirtyy siirtorekisteriin kun signaali vaihtuu LOW -> HIGH
char latchPin = 10;    //kytketty RCLK(register clock/latch pin), data siirtyy siirtorekisteristä, kun signaali vaihtuu LOW -> HIGH
char enablePin = 9;    //kytketty OE(output enable), toimii kytkimenä outputeille. LOW asemassa rekisterin output pinnit auki, HIGH asemassa kiinni.
char dataPin = 8;      //kytketty SER(serial input), siirtää datan bitti kerrallaan siirtorekisterille.

byte segLuku[] = {
  // tähän taulukkoon mitä datapinni lähettää sarjarekisterille kun halutaan näyttää
  // jokin tietty luku
  // esim.
  // B00101010, // 1
  // B01000010, // 2
  // B10010011, // 3 jne., nämä ei ole vielä oikein
}

void initializeDisplay(void)
{
  cli();

  pinMode(resetPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);        //lähtöpinnit OUTPUT moodiin
  pinMode(enablePin, OUTPUT);
  pinmode(dataPin, OUTPUT);
  digitalWrite(resetPin, LOW);      //LOW resettaa sarjarekisterin kaikki bitit nolliksi
  digitalWrite(resetPin, HIGH);     //poistaa resetin

  sei();
}


void writeByte(uint8_t bits,bool last)
{
  pinMode(latchPin, LOW);   //valmistellaan datan siirto
  //tähän jotain
  pinMode(latchPin, HIGH);  //data siirtyy siirtorekisteristä  
}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{

}

void showResult(byte number)
{

}

