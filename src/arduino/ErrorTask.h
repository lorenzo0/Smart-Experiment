#ifndef __ERRORTASK_
#define __ERRORTASK_

#include "Task.h"
#include "Led.h"

class ErrorTask: public Task{

  int pinLed1;
  int pinLed2;
  int timeToCompleteTask;

  LedImpl* led1;
  LedImpl* led2;  

public: 

  ErrorTask(int pinLed1, int pinLed2);
  void init(int period);  
  void tick();

};

#endif
