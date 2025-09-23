#include "display.h"

int resetPin = 12;    //kytketty SRCLR(shift register clear), käytetään resetti pinninä
int clockPin = 11;    //kytketty SRCLK(shift register clock), data siirtyy siirtorekisteriin kun signaali vaihtuu LOW -> HIGH
int latchPin = 10;    //kytketty RCLK(register clock/latch pin), data siirtyy siirtorekisteristä, kun signaali vaihtuu LOW -> HIGH
int enablePin = 9;    //kytketty OE(output enable), toimii kytkimenä outputeille. LOW asemassa rekisterin output pinnit auki, HIGH asemassa kiinni.
int dataPin = 8;      //kytketty SER(serial input), siirtää datan bitti kerrallaan siirtorekisterille.

byte segDigits[] = {
  //tähän taulukkoon mitä datapinni lähettää sarjarekisterille kun halutaan näyttää jokin luku
  //esim.
  // B00101010 = 8
  // B01000010 = 9
  // B10010011 = 10 jne.
}

void initializeDisplay(void)
{
  pinMode(resetPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);        //lähtöpinnit OUTPUT moodiin
  pinMode(enablePin, OUTPUT);
  pinmode(dataPin, OUTPUT);
  digitalWrite(resetPin, LOW);      //LOW resettaa sarjarekisterin kaikki bitit nolliksi
  digitalWrite(resetPin, HIGH);     //poistaa resetin
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

