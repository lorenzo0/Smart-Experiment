#include "Scheduler.h"
#include "Task.h"
#include "IdleTask.h"
#include "SleepModeTask.h"
#include <TimerOne.h>
#include <EnableInterrupt.h>

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
  nTasks = 0;

  enableInterrupt(12, IdleTask::handleInterrupts, RISING);
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

  //Serial.println("Going");
  
  for (int i = 0; i < nTasks; i++){
    //Serial.println("Keep");
    
    while (taskList[i] -> isActive()){
        if (taskList[i] -> updateAndCheckTime(basePeriod))
            taskList[i]->tick(); 
    }
    
    if (taskList[i] -> isInterrupted() || taskList[i] -> isCompleted())
        Scheduler::redirectTask(taskList[i] -> getNextTask());
    
  }
}

/*0 è idle
1 è error
2 sleep
3 running*/

void Scheduler::redirectTask(int nextState){
  switch(nextState){
    case 0:
      taskList[0] -> setActive(true);
      Serial.println("Idle state");
      disableInterrupt(7);
      enableInterrupt(12, IdleTask::handleInterrupts, RISING);
      break;
    case 1:
      taskList[1] -> setActive(true);
      Serial.println("Error state");
      disableInterrupt(12);
      disableInterrupt(7);
      break;
     case 2:
      taskList[2] -> setActive(true);
      Serial.println("Sleep state");
      disableInterrupt(12);
      enableInterrupt(7, SleepModeTask::wakeUp, RISING);
      break;
     case 3:
      taskList[3] -> setActive(true);
      Serial.println("Running state");
      disableInterrupt(12);
      disableInterrupt(7);
      break;
  }
}
