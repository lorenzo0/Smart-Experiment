#ifndef __TASK__
#define __TASK__
#include "Arduino.h"

class Task {
  int myPeriod;
  int timeElapsed;
  extern boolean stopTask;
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
    stopTask = false;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod && !(cout << stopTask)){
      timeElapsed = 0;
      return true;
    } else {
      stopTask = false;
      return false; 
    }
  }
  
};

#endif
