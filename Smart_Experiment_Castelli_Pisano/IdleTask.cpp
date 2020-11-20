#include "IdleTask.h"
#include "Arduino.h"
#include "Scheduler.h"

const int SLEEP_TIME  = 5 * 1000;
bool stopIdle;

IdleTask::IdleTask(int pinLed1, int pinLed2, int pinButton){
  this -> pinLed1 = pinLed1;
  this -> pinLed2 = pinLed2;
  this -> pinButton = pinButton;
  stopIdle = false;
}

void IdleTask::init(int period){
  Task::init(period);
  
  led1 = new Led(pinLed1);
  led2 = new Led(pinLed2);
  
  button = new Button(pinButton);

  led1 -> switchOff();
  stateLed1 = OFF;
  
  led2 -> switchOn();
  stateLed2 = ON;
  
  stateButton = NOTCLICKED;
}

void IdleTask::tick(){
  //Serial.println("Idle");
  Task::currentTs = millis();

  if(stopIdle){
    Task::setInterrupted();
    stopIdle = false;
    Task::setNextTask(1);
  }else if(Task::currentTs - Task::ts0 > SLEEP_TIME){
    Task::setCompleted(); 
    Task::setNextTask(2);
  }
}

void IdleTask::handleInterrupts(){
  stopIdle = true;
}
