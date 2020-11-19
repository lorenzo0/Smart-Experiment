#include "SleepMode.h"
#include "Arduino.h"
#include "Pir.h"
#include <avr/sleep.h>

bool stopSleepMode;

SleepMode::SleepMode(int pinLed1, int pinPir){
  this -> pinLed1 = pinLed1;
  this -> pinPir = pinPir;
  stopSleepMode=false;
}

void SleepMode::init(){
  Task::init();
  
  led1 = new Led(pinLed1);
  pir = new Pir(pinPir);
}

void SleepMode::tick(){

  sleep();
  
  Task::setInterrupted();
  Task::setNextTask(0);
  /*Serial.println("PIR has detected something, wake up uaio");
  Serial.println(pir->getPresence());*/
  stopSleepMode = false;
}

void SleepMode::sleep(){ 
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
  
  led1 -> switchOff();
  stateLed1 = OFF;

  Serial.println("Going to sleep...");
  delay(200);
  
  sleep_cpu();
}

void SleepMode::wakeUp(){
  sleep_disable();
  stopSleepMode=true;
}
