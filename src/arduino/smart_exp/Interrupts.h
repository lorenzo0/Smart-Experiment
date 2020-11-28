#ifndef __INTERRUPTS__
#define __INTERRUPTS__

#include "Scheduler.h"

class Interrupts{  

public: 

  void init();

private:
  Scheduler scheduler;
  
};

#endif
