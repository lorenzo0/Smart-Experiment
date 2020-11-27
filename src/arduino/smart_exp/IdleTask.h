#ifndef __IDLETASK__
#define __IDLETASK__

#include "Task.h"
#include "Led.h"
#include "Button.h"

class IdleTask: public Task{  

public: 

  IdleTask(int pinLed1, int pinLed2, int pinButton);
  void init(int period);  
  void tick();
  void static handleInterrupts();
  void setNextToGo();

private:

  int pinLed1;
  int pinLed2;
  int pinButton;
  int timeToCompleteTask;
  
  LedImpl* led1;
  LedImpl* led2;
  Button* button;

};

#endif
