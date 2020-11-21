#include "IdleTask.h"
#include "Arduino.h"
#include "Scheduler.h"

boolean stopIdle;

IdleTask::IdleTask(int pinLed1, int pinLed2, int pinButton){
  this -> pinLed1 = pinLed1;
  this -> pinLed2 = pinLed2;
  this -> pinButton = pinButton;
  stopIdle = false;
  timeToCompleteTask = 0;
}

void IdleTask::init(int period){
  Task::init(period);
  timeToCompleteTask = period;
  
  led1 = new Led(pinLed1);
  led2 = new Led(pinLed2);
  
  button = new Button(pinButton);

  led1 -> switchOn();
  stateLed1 = ON;
  
  led2 -> switchOff();
  stateLed2 = OFF;
  
  stateButton = NOTCLICKED;
}

void IdleTask::tick(){
  //Serial.println("Idle");
  Task::currentTs = millis();

  if(stopIdle){
    Task::setInterrupted();
    stopIdle = false;
    Task::setNextTask(1);
  }else if(Task::currentTs - Task::ts0 > timeToCompleteTask){
    Task::setCompleted(); 
    Task::setNextTask(2);
  }
}

void IdleTask::handleInterrupts(){
  stopIdle = true;
}
