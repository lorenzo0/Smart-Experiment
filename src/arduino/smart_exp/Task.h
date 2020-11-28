#ifndef __TASK__
#define __TASK__
#include "Arduino.h"

class Task {

private: 

  int myPeriod;
  int timeElapsed;
  boolean active;
  boolean periodic;
  boolean completed;
  boolean interrupted;
  
public:

  long ts0, currentTs;
  boolean firstRun;
  int nameNextTask;
  
   /* periodic */
  virtual void init(int period){
    myPeriod = period;
    periodic = true;  
    interrupted = false;
    completed = false;
    timeElapsed = 0;
  }

  /* aperiodic */
  virtual void init(){
    periodic = false;
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

  void setNotInterrupted(){
    interrupted = false;
  }

  void setNotCompleted(){
    completed = false;
  }

  void setNextTask(int nameNextTask){
    this -> nameNextTask = nameNextTask;
  }

  void setActive(boolean cond){
    timeElapsed = 0;
    active = cond;
    ts0 = millis();
    interrupted = false;
    completed = false;
  }

  int getNextTask(){
    return nameNextTask;
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
