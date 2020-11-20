#ifndef __ERRORTASK_
#define __ERRORTASK_

#include "Task.h"
#include "Led.h"

class ErrorTask: public Task{
  
  int pinLed2;
  LedImpl* led2;
  enum { ON, OFF } stateLed2;
  Task* pIdleTask;

public: 

  ErrorTask(int pinLed2);//, Task* pIdleTask);
  void init(int period);  
  void tick();
  void blinkingLed();

};

#endif
