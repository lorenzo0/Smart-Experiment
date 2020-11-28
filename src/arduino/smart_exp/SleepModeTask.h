#ifndef __SLEEPMODETASK__
#define __SLEEPMODETASK__

#include "Task.h"
#include "Led.h"
#include "Pir.h"

class SleepModeTask: public Task{
  
  int pinLed1;
  int pinPir;
  LedImpl* led1;
  Pir* pir;

public: 

  SleepModeTask(int pinLed1, int pinPir);
  void init(int period);  
  void tick();
  void sleep();
  void static wakeUp();
};

#endif
