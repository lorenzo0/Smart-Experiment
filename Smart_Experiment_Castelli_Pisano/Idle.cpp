#include "Idle.h"
#include "Arduino.h"
#include <EnableInterrupt.h>

boolean stopTask;

Idle::Idle(int pinLed1, int pinLed2, int pinButton){
  this -> pinLed1 = pinLed1;
  this -> pinLed2 = pinLed2;
  this -> pinButton = pinButton;
}

void Idle::init(int period){
  Task::init(period);
  
  led1 = new Led(pinLed1);
  led2 = new Led(pinLed2);
  
  button = new Button(pinButton);
  enableInterrupt(pinButton, handleInterrupts, RISING);

  led1 -> switchOff();
  stateLed1 = OFF;
  
  led2 -> switchOn();
  stateLed2 = ON;
  
  stateButton = NOTCLICKED;
}

void Idle::tick(){
  Serial.println("Tick");
}

void static Idle::handleInterrupts(){
  //qui funziona ma dobbiamo stoppare il task
}
