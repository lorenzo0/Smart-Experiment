#include "ErrorTask.h"
#include "Arduino.h"

long time; 
float fadeValue;
//sarebbe 2
const int ERROR_TIME = 10 * 1000;

ErrorTask::ErrorTask(int pinLed2){
  this -> pinLed2 = pinLed2;
  time = 0;
  fadeValue = 0;
}

void ErrorTask::init(int period){
  Task::init(period);
    
  led2 = new Led(pinLed2);
  Task::ts0 = millis();
  
  led2 -> switchOn();
  stateLed2 = ON;
}

void ErrorTask::tick(){
  Task::currentTs = millis();

  if(Task::currentTs - Task::ts0 > ERROR_TIME)
    Task::setCompleted();
  else
    ErrorTask::blinkingLed();
}

void ErrorTask::blinkingLed(){
  time = millis();
  fadeValue = 128+127*cos(2*PI/2000*time);
  analogWrite(pinLed2, fadeValue);
}
