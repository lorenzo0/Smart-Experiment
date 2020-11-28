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
  virtual void redirectTask(int nextState);
  void setIndexCurrentTaskActive(int index);

private:
  int indexCurrentTaskActive=0;
  int i=0;
};

/*0 è idle
1 è error
2 sleep*/

#endif