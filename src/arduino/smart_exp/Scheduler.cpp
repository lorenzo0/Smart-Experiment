#include "Scheduler.h"
#include "Task.h"
#include "IdleTask.h"
#include "SleepModeTask.h"
#include "RunningTask.h"
#include <TimerOne.h>

const int SLEEP_TIME  = 5 * 1000;
const int MAX_TIME = 20 * 1000;
const int ERROR_TIME = 2 * 1000;

volatile boolean timerFlagScheduler;
extern boolean handleInterrupt;

void timerHandler(void){
  timerFlagScheduler = true;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlagScheduler = false;
  handleInterrupt = false;
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
  i = indexCurrentTaskActive;
  Serial.println("I: "+String(i));

   if (taskList[i] -> updateAndCheckTime(basePeriod))
      taskList[i] -> tick();
   if (handleInterrupt == true){
      Serial.println("Ci sono - 2");
      handleInterrupt = false;
      Scheduler::redirectTask(taskList[i] -> getNextTask());
  }if(taskList[i]->isCompleted()){
      Serial.println("Task completato");
      Scheduler::redirectTask(taskList[i] -> getNextTask());
      taskList[i]->setCompleted(false);
  }
}

/*0 è idle
1 è error
2 sleep
3 running*/

void Scheduler::redirectTask(int nextState){
  Serial.println("Ci sono - 4");
  switch(nextState){
    case 0:
      setIndexCurrentTaskActive(0);
      Serial.println("Idle state");
      break;
    case 1:
      setIndexCurrentTaskActive(1);
      Serial.println("Error state - 4");
      break;
     case 2:
      setIndexCurrentTaskActive(2);
      Serial.println("Sleep state");
      break;
     case 3:
      setIndexCurrentTaskActive(3);
      Serial.println("Running state");
      break;
  }
  Serial.flush();
}

void Scheduler::setIndexCurrentTaskActive(int index){
  this->indexCurrentTaskActive = index;
}
