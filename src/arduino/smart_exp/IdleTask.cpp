#include "IdleTask.h"
#include "Arduino.h"
#include "MsgService.h"

IdleTask::IdleTask(int pinLed1, int pinLed2, int pinButton){
  this -> pinLed1 = pinLed1;
  this -> pinLed2 = pinLed2;
  this -> pinButton = pinButton;
}

void IdleTask::init(int period){
  Task::init(period);
  
  led1 = new Led(pinLed1);
  led2 = new Led(pinLed2);
  
  button = new Button(pinButton);
  Task::setFirstRun(false);
}

void IdleTask::tick(){

  if(!(Task::firstRun)){
    //MsgService.sendMsg("IDLE");
    led1 -> switchOn();
    led2 -> switchOff();
    Task::setFirstRun(true);
    Task::setNextTask(3);
    Task::ts0 = millis();
  }

  Task::currentTs = millis();
  
  if(Task::currentTs - Task::ts0 > SLEEP_TIME){
    Task::setCompleted(true); 
    Task::setNextTask(2);
    Task::setFirstRun(false);
  }
}
