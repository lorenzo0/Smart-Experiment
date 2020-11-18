#ifndef __LED__
#define __LED__

#include "LedImpl.h"

class Led: public LedImpl { 
public:
  Led(int pin);
  void switchOn();
  void switchOff();    
private:
  int pin;  
};

#endif
