#include <Arduino.h>
#include <SPI.h>
char buf [100];
volatile byte pos;
volatile boolean status_;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
SPCR |= bit (SPE);
SPI.setBitOrder(MSBFIRST);
pos = 0;   // buffer empty
status_ = false;
SPI.attachInterrupt();
}

ISR (SPI_STC_vect)
{
  byte c = SPDR;
  if (pos < (sizeof(buf) -1))
  {buf [pos++]=c;}

}
void loop() {
  // put your main code here, to run repeatedly:
if (status_)
    {
    buf [pos] = 0;  
    Serial.println (buf);
    pos = 0;
    status_ = false;
    }  // end of flag set
}