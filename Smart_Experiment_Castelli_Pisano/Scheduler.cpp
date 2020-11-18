#include "Scheduler.h"
#include "Task.h"
#include <TimerOne.h>

const int SLEEP_TIME  = 5 * 1000;
const int MAX_TIME = 20 * 1000;
const int ERROR_TIME = 2 * 1000;

volatile boolean timerFlagScheduler;

void timerHandler(void){
  timerFlagScheduler = true;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlagScheduler = false;
  long period = 1000l*basePeriod;
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
  nTasks;
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
              taskList[i]->tick();
      } 
    }
    if (taskList[i] -> isInterrupted() || taskList[i] -> isCompleted())
        Scheduler::redirectTask(taskList[i] -> getNextTask());
  }
}

void Scheduler::redirectTask(int currentState){
  switch(currentState){
    case 0:
      taskList[0] -> setActive(true);
      break;
    case 1:
      taskList[1] -> setActive(true);
      break;
  }
}
