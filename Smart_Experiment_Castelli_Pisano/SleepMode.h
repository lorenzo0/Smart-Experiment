#ifndef __SLEEPMODE__
#define __SLEEPMODE__

#include "Task.h"
#include "Led.h"
#include "Pir.h"

class SleepMode: public Task{
  
  int pinLed1;
  int pinPir;
  LedImpl* led1;
  Pir* pir;
  enum { ON, OFF } stateLed1;


public: 

  SleepMode(int pinLed1, int pinPir);
  void init();  
  void tick();
  void sleep();
  void static wakeUp();
};

#endif
