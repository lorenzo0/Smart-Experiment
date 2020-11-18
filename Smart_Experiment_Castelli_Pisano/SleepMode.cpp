#include "SleepMode.h"
#include "Arduino.h"
#include "Pir.h"
#include <avr/sleep.h>

bool stopSleepMode;
int pinState;

SleepMode::SleepMode(int pinLed1, int pinButton, int pinPir){
  this -> pinLed1 = pinLed1;
  this -> pinButton = pinButton;
  this -> pinPir = pinPir;
  stopSleepMode=false;
}


void SleepMode::init(){
  Task::init();
  
  led1 = new Led(pinLed1);
 
  button = new Button(pinButton);

  pir = new Pir(pinPir);
  
  led1 -> switchOff();
  stateLed1 = OFF;
  stateButton = NOTCLICKED;

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();
}

void SleepMode::tick(){
  Serial.println("Tick");
  pinState = pir->checkPresence();
  if(pinState == 1)
    Task::setInterrupted();
}
