#include "Button.h"
#include "Arduino.h"

int resultButtonState = 0;

Button::Button(int pinButton){
  this->pinButton = pinButton;
  pinMode(pinButton,INPUT);
}
