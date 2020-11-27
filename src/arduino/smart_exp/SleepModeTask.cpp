#include "SleepModeTask.h"
#include "Arduino.h"
#include "Pir.h"
#include <avr/sleep.h>

bool stopSleepMode;

SleepModeTask::SleepModeTask(int pinLed1, int pinPir){
  this -> pinLed1 = pinLed1;
  this -> pinPir = pinPir;
  stopSleepMode=false;
}

void SleepModeTask::init(){
  Task::init();
  
  led1 = new Led(pinLed1);
  pir = new Pir(pinPir);

  Task::firstRun = false;
}

void SleepModeTask::tick(){

  if(!(Task::firstRun)){
    led1 -> switchOff();
    Task::firstRun = true;
  }

  sleep();
  
  Task::setInterrupted();
  Task::setNextTask(0);
  Task::firstRun = false;
  /*Serial.println("PIR has detected something, wake up uaio");
  Serial.println(pir->getPresence());*/
  stopSleepMode = false;
}

void SleepModeTask::sleep(){ 
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 

  Serial.println("Going to sleep...");
  delay(200);
  
  sleep_cpu();
}

void SleepModeTask::wakeUp(){
  sleep_disable();
  stopSleepMode=true;
}
