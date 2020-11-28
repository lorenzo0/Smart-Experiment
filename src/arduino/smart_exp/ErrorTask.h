#ifndef __ERRORTASK_
#define __ERRORTASK_

#include "Task.h"
#include "Led.h"

class ErrorTask: public Task{

public: 

  ErrorTask(int pinLed1, int pinLed2);
  void init(int period);  
  void tick();

private: 
  const int ERROR_TIME = 2 * 1000;
  
  int pinLed1;
  int pinLed2;

  LedImpl* led1;
  LedImpl* led2;  

};

#endif
