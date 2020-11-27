#include "Potentiometer.h"
#include "Arduino.h"

#define MAXFREQ 1
#define MINFREQ 50

/*
 * Il potenziometro 10K rileva valore da 1 a 1024, il testo invece
 * chiede che ci siano due parametri di MAXFREQ e MINFREQ.
 * Si trova dunque un'equazione per trovare il valore in rapporto a queste
 * due costanti.
*/

Potentiometer::Potentiometer(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
}

float Potentiometer::readFromPotentiometer(){

  //1 : MAXFREQ = x : 1024
  //toCheck

  if(MAXFREQ < 1024)
    freq = analogRead(pin) / (1024/MAXFREQ);
  else
    freq = analogRead(pin) / (MAXFREQ/1024);
  return freq;
}
