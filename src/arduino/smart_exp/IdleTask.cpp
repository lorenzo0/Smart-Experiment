#include "IdleTask.h"
#include "Arduino.h"
#include "Scheduler.h"

IdleTask::IdleTask(int pinLed1, int pinLed2, int pinButton){
  this -> pinLed1 = pinLed1;
  this -> pinLed2 = pinLed2;
  this -> pinButton = pinButton;
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
    Task::nameNextTask = 1;
  }

  Task::currentTs = millis();
  
  if(Task::currentTs - Task::ts0 > timeToCompleteTask){
    Task::setCompleted(); 
    Task::setNextTask(2);
    Task::firstRun = false;
  }/*else if(Task::isInterrupted()){
    Serial.println("Hey");
    Task::setNextTask(1);
    Task::firstRun = false;
  }*/
}
