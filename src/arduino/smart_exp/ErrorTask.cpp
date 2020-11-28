#include "ErrorTask.h"
#include "Arduino.h"

long time; 
float fadeValue;

ErrorTask::ErrorTask(int pinLed1, int pinLed2){
  this -> pinLed2 = pinLed2;
  this -> pinLed1 = pinLed1;
  time = 0;
  fadeValue = 0;
}

void ErrorTask::init(int period){
  Task::init(period);
    
  led2 = new Led(pinLed2);
  Task::firstRun = false;
}

void ErrorTask::tick(){
  if(!(Task::firstRun)){
    led1 -> switchOff();
    led2 -> switchOn();
    Task::firstRun = true;
  }
    
  Serial.println("ErrorTask");
  Task::currentTs = millis();

  if(Task::currentTs - Task::ts0 > ERROR_TIME){
    Task::setCompleted();    
    Task::setNextTask(0);
    Task::firstRun = false;
  }else
    led2 -> blinking();
}
