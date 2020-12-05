#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
}

/*
 * Il potenziometro 10K rileva valore da 1 a 1024, il testo invece
 * chiede che ci siano due parametri di MAXFREQ e MINFREQ.
 * Si trova dunque un'equazione per trovare il valore in rapporto a queste
 * due costanti.
 * 
 * freqPot : 1024 = x : MAXFREQ
*/

float Potentiometer::readFromPotentiometer(){
    freq = analogRead(pin)*MAXFREQ / 1024;
  return freq;
}
