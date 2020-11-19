#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pinPir){
  this->pinPir = pinPir;
  pinMode(pinPir,INPUT);
}

int Pir::getPresence(){
  return digitalRead(pinPir);
}
