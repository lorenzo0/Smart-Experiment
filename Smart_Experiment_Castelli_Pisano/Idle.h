#ifndef __IDLE__
#define __IDLE__

#include "Task.h"
#include "Led.h"
#include "Button.h"

class Idle: public Task{
  
  int pinLed1;
  int pinLed2;
  int pinButton;
  LedImpl* led1;
  LedImpl* led2;
  Button* button; 
  enum { ON, OFF } stateLed1, stateLed2;
  enum { CLICKED, NOTCLICKED } stateButton;
  

public: 

  Idle(int pinLed1, int pinLed2, int pinButton);
  void init(int period);  
  void tick();
  void static handleInterrupts();

};

#endif
