#include "Idle.h"
#include "Arduino.h"
#include "Scheduler.h"
#include <EnableInterrupt.h>

const int SLEEP_TIME  = 5 * 1000;
bool stopIdle;

Idle::Idle(int pinLed1, int pinLed2, int pinButton){
  this -> pinLed1 = pinLed1;
  this -> pinLed2 = pinLed2;
  this -> pinButton = pinButton;
  stopIdle = false;
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
  Serial.println("Idle");
  Task::currentTs = millis();
+
  if(stopTask){
    Task::setInterrupted();
    stopTask = false;
  }else if(Task::currentTs - Task::ts0 > SLEEP_TIME){
    Task::setCompleted();    
    Task::setNextTask(1);
  }
}

void Idle::handleInterrupts(){
  stopIdle = true;
}
