#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlagScheduler;

void timerHandler(void){
  timerFlagScheduler = true;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlagScheduler = false;
  long period = 1000l*basePeriod;
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
  nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){   
  while (!timerFlagScheduler){}
  timerFlagScheduler = false;

  for (int i = 0; i < nTasks; i++){
    while (taskList[i] -> isActive()){
        if (taskList[i] -> updateAndCheckTime(basePeriod)){
            
            if (taskList[i] -> isInterrupted())
              Serial.println("Task has been interrupted!");
            else if(taskList[i] -> isCompleted())
              Serial.println("Task has completed its time!");
            else
              taskList[i]->tick();
        
      } 
    }
  }
}
