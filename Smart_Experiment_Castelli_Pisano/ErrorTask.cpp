#include "ErrorTask.h"
#include "Arduino.h"

long time; 
float fadeValue;
const int ERROR_TIME = 2 * 1000;

ErrorTask::ErrorTask(int pinLed2){
  this -> pinLed2 = pinLed2;
  time = 0;
  fadeValue = 0;
  timeToCompleteTask = 0;
}

void ErrorTask::init(int period){
  Task::init(period);
  timeToCompleteTask = period;
    
  led2 = new Led(pinLed2);
  led2 -> switchOn();
  stateLed2 = ON;
}

void ErrorTask::tick(){
  //Serial.println("ErrorTask");
  Task::currentTs = millis();

  if(Task::currentTs - Task::ts0 > timeToCompleteTask){
    Task::setCompleted();    
    Task::setNextTask(0);
  }else
    led2 -> blinking();
}
