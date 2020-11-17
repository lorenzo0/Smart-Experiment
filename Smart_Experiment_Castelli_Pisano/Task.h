#ifndef __TASK__
#define __TASK__
#include "Arduino.h"

class Task {

private: 

  int myPeriod;
  int timeElapsed;
  boolean active;
  bool periodic;
  bool completed;
  bool interrupted;
  
public:

  long ts0, currentTs;

   /* periodic */
  virtual void init(int period){
    myPeriod = period;
    periodic = true;  
    active = true;
    interrupted = false;
    completed = false;
    timeElapsed = 0;
  }

  /* aperiodic */
  virtual void init(){
    periodic = false;
    active = true;
    completed = false;
    interrupted = false;
    timeElapsed = 0;
  }

  void setCompleted(){
    completed = true;
    active = false;
    interrupted = false;
  }
  
  void setInterrupted(){
    completed = false;
    active = false;
    interrupted = true;
  }

  bool isCompleted(){
    return completed;
  }

  bool isInterrupted(){
    return interrupted;
  }

  bool isPeriodic(){
    return periodic;
  }

  bool isActive(){
    return active;
  }
  
  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod ){
      timeElapsed = 0;
      return true;
    } else 
      return false; 
  }
  
};

#endif
