#ifndef __ERRORTASK_
#define __ERRORTASK_

#include "Task.h"
#include "Led.h"

class ErrorTask: public Task{
  
  int pinLed2;
  int timeToCompleteTask;
  
  LedImpl* led2;
  Task* pIdleTask;
  
  enum { ON, OFF } stateLed2;
  

public: 

  ErrorTask(int pinLed2);//, Task* pIdleTask);
  void init(int period);  
  void tick();

};

#endif
