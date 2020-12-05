#include "Button.h"
#include "Arduino.h"

Button::Button(int pinButton){
  this->pinButton = pinButton;
  pinMode(pinButton,INPUT);
}
