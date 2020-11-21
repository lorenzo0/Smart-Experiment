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

  Task::firstRun = false;
}

void IdleTask::tick(){
  
  if(!(Task::firstRun)){
    led1 -> switchOn();
    led2 -> switchOff();
    Task::firstRun = true;
  }
  
  //Serial.println("Idle");
  Task::currentTs = millis();

  if(stopIdle){
    Task::setInterrupted();
    stopIdle = false;
    Task::setNextTask(1);
    Task::firstRun = false;
  }else if(Task::currentTs - Task::ts0 > timeToCompleteTask){
    Task::setCompleted(); 
    Task::setNextTask(2);
    Task::firstRun = false;
  }
}

void IdleTask::handleInterrupts(){
  stopIdle = true;
}
