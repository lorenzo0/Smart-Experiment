#include "ErrorTask.h"
#include "Arduino.h"

long time; 
float fadeValue;
const int ERROR_TIME = 2 * 1000;

ErrorTask::ErrorTask(int pinLed2){
  this -> pinLed2 = pinLed2;
  time = 0;
  fadeValue = 0;
}

void ErrorTask::init(int period){
  Task::init(period);
    
  led2 = new Led(pinLed2);
  
  led2 -> switchOn();
  stateLed2 = ON;
}

void ErrorTask::tick(){
  //Serial.println("ErrorTask");
  Task::currentTs = millis();

  if(Task::currentTs - Task::ts0 > ERROR_TIME){
    Task::setCompleted();    
    Task::setNextTask(0);
  }else
    ErrorTask::blinkingLed();
}

void ErrorTask::blinkingLed(){
  time = millis();
  fadeValue = 128+127*cos(2*PI/2000*time);
  analogWrite(pinLed2, fadeValue);
}
