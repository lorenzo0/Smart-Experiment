#include "ErrorTask.h"
#include "Arduino.h"

ErrorTask::ErrorTask(int pinLed1, int pinLed2){
  this -> pinLed2 = pinLed2;
  this -> pinLed1 = pinLed1;
  time = 0;
  fadeValue = 0;
}

void ErrorTask::init(int period){
  Task::init(period);

  led1 = new Led(pinLed1);
  led2 = new Led(pinLed2);
  Task::setFirstRun(false);
}

void ErrorTask::tick(){

  if(!(Task::firstRun)){
    //MsgService.sendMsg("ERROR");
    led1 -> switchOff();
    led2 -> switchOn();
    Task::setFirstRun(true);
    Task::ts0 = millis();
  }
  
  Task::currentTs = millis();

  if(Task::currentTs - Task::ts0 > ERROR_TIME){
    Task::setCompleted(true);    
    Task::setNextTask(0);
    Task::setFirstRun(false);
  }else
    led2 -> blinking();
}
