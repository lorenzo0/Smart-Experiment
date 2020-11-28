#ifndef __TASK__
#define __TASK__
#include "Arduino.h"

class Task {

private: 

  int myPeriod;
  int timeElapsed;
  boolean completed;
  
public:

  long ts0, currentTs;
  boolean firstRun;
  int nameNextTask;
  
   /* periodic */
  virtual void init(int period){
    myPeriod = period;
    completed = false;
    timeElapsed = 0;
  }


  void setCompleted(boolean setState){
    this -> completed = setState;
  }

  void setNextTask(int nameNextTask){
    this -> nameNextTask = nameNextTask;
  }

  int getNextTask(){
    return nameNextTask;
  }
  
  bool isCompleted(){
    return completed;
  }

  bool isFirstRun(){
    return firstRun;
  }

  void setFirstRun(boolean first){
    firstRun = first;
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
