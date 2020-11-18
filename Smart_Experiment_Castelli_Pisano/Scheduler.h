#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 50

class Scheduler {
  
  int basePeriod;
  int nTasks;
  String nameTask;
  Task* taskList[MAX_TASKS];  
  Task* taskObject;

public:
  void init(int basePeriod);  
  virtual bool addTask(Task* task);  
  virtual void schedule();
  virtual void redirectTask(int currentState);
};

/*0 è idle
1 è error*/

#endif
