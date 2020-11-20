#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
}

float Potentiometer::readFromPotentiometer(){
  return analogRead(pin);
}
