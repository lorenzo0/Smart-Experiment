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
  int i = indexCurrentTaskActive;
  Serial.println("I: "+String(i));

   if (taskList[i] -> updateAndCheckTime(basePeriod))
      taskList[i] -> tick();
   if (handleInterrupt == true){
      Serial.println("Ci sono - 2");
      handleInterrupt = false;
      Scheduler::redirectTask(taskList[i] -> getNextTask());
      //taskList[i]->setFirstRun(false);
  }if(taskList[i]->isCompleted()){
      Serial.println("Task completato");
      Scheduler::redirectTask(taskList[i] -> getNextTask());
      taskList[i]->setNotCompleted();
  }
  
    /*
    while (taskList[] -> isActive()){
        if (taskList[i] -> updateAndCheckTime(basePeriod)) 
            taskList[i]->tick(); 
        if (handleInterrupt == true){
            taskList[i]-> setActive(false);
            taskList[i]-> setInterrupted();
            Serial.println("Ci sono - 2");
            Serial.println(taskList[i]->isActive());
            //Serial.flush();
            handleInterrupt = false;
            Serial.println(taskList[i]->isInterrupted());
            //taskList[i]->setFirstRun(false);
        }
    }
    
    if (taskList[i] -> isInterrupted() || taskList[i] -> isCompleted()){
        Serial.println("Ci sono - 3");
        //Serial.flush();
        taskList[i] -> setNotInterrupted();
        taskList[i] -> setNotCompleted();
        Scheduler::redirectTask(taskList[i] -> getNextTask());
    }
    Serial.println("ueueue");

    for(int y=0;y<4;y++){
      Serial.println("TaskList["+String(y)+"]"+String(taskList[y]->isActive()));
    }
    Serial.flush(); 

  /*if(handleInterrupt){
    taskList[0]-> setActive(false);
    taskList[0]-> setInterrupted();
    handleInterrupt = false;
  }
  if (taskList[0] -> isInterrupted()){
      taskList[0] -> setNotInterrupted();
      Serial.println("Ci sono - 3");
      Scheduler::redirectTask(taskList[0] -> getNextTask());
  }

 Serial.println("Sto uscendo");
 Serial.flush(); */
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
      /*disableInterrupt(7);
      disableInterrupt(12);
      enableInterrupt(8, handleInterrupts, RISING);**/
      break;
    case 1:
      setIndexCurrentTaskActive(1);
      Serial.println("Error state - 4");
      /*disableInterrupt(8);
      disableInterrupt(12);
      disableInterrupt(7);*/
      break;
     case 2:
      setIndexCurrentTaskActive(2);
      Serial.println("Sleep state");
      /*disableInterrupt(8);
      disableInterrupt(12);
      enableInterrupt(7, handleInterrupts, RISING);*/
      break;
     case 3:
      setIndexCurrentTaskActive(3);
      Serial.println("Running state");
      /*disableInterrupt(8);
      disableInterrupt(7);
      enableInterrupt(12, handleInterrupts, RISING);*/
      break;
  }
  Serial.flush();
}

void Scheduler::setIndexCurrentTaskActive(int index){
  this->indexCurrentTaskActive = index;
}
