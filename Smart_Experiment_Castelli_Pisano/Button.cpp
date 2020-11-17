#include "Button.h"
#include "Arduino.h"

int resultButtonState = 0;

Button::Button(int pinButton){
  this->pinButton = pinButton;
  pinMode(pinButton,INPUT);
}

void Button::getButtonState(){
  Serial.println("Ci sono!");
  resultButtonState = 1;
  //tick finisce
}
