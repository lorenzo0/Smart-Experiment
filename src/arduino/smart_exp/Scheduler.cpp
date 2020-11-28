#include "Scheduler.h"
#include "Task.h"
#include "IdleTask.h"
#include "SleepModeTask.h"
#include "RunningTask.h"
#include <TimerOne.h>

volatile boolean timerFlagScheduler;

extern boolean InterruptStart;
extern boolean InterruptStop;
extern boolean InterruptPir;

void timerHandler(void){
  timerFlagScheduler = true;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlagScheduler = false;
  
  InterruptStart = false;
  InterruptStop = false;
  InterruptPir = false;
  
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
  //Serial.println("I: "+String(i));

   if (taskList[i] -> updateAndCheckTime(basePeriod))
      taskList[i] -> tick();
      
   if (InterruptStart == true && i == 0){
      //Serial.println("Ci sono - start");
      InterruptStart = false;
      taskList[i] -> setFirstRun(false);
      Scheduler::redirectTask(taskList[i] -> getNextTask());
   }else if(InterruptStop == true && i == 3){
      //Serial.println("Ci sono - stop");
      InterruptStop = false;
      taskList[i] -> setFirstRun(false);
      Scheduler::redirectTask(taskList[i] -> getNextTask());
   }else if(InterruptPir == true && i == 2){
      //Serial.println("Ci sono - pir");
      InterruptPir = false;
      taskList[i] -> setFirstRun(false);
      Scheduler::redirectTask(taskList[i] -> getNextTask());
   }
      
   if(taskList[i]->isCompleted()){
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
