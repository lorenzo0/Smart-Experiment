#include "SleepModeTask.h"
#include "Arduino.h"

SleepModeTask::SleepModeTask(int pinLed1, int pinPir){
  this -> pinLed1 = pinLed1;
  this -> pinPir = pinPir;
}

void SleepModeTask::init(int period){
  Task::init(period);
  
  led1 = new Led(pinLed1);
  pir = new Pir(pinPir);

  Task::setFirstRun(false);
}

void SleepModeTask::tick(){

  if(!(Task::firstRun)){
    led1 -> switchOff();
    Task::setFirstRun(true);
  }
  
  sleep();
  
  Task::setFirstRun(false);
  Task::setNextTask(0);
  Task::setCompleted(true);
}

void SleepModeTask::sleep(){ 
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 

  //Serial.println("Going to sleep...");
  delay(500);
  
  sleep_cpu();
}

void SleepModeTask::wakeUp(){
  sleep_disable();
  delay(500);
}
