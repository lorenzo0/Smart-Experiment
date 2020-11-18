#ifndef __SLEEPMODE__
#define __SLEEPMODE__

#include "Task.h"
#include "Led.h"
#include "Button.h"
#include "Pir.h"

class SleepMode: public Task{
  
  int pinLed1;
  int pinButton;
  int pinPir;
  LedImpl* led1;
  Button* button;
  Pir* pir;
  enum { ON, OFF } stateLed1;
  enum { CLICKED, NOTCLICKED } stateButton;


public: 

  SleepMode(int pinLed1, int pinButton, int pinPir);
  void init();  
  void tick();
};
#endif
