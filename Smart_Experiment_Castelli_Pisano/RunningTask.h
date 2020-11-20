#ifndef __RUNNINGTASK__
#define __RUNNINGTASK__

#include "Task.h"
#include "Sonar.h"
#include "Led.h"
#include "Potentiometer.h"

class RunningTask: public Task{  

public: 

  RunningTask(int pinLed1, int pinLed2, int pinEchoSonar, int pinTrigSonar, int Pot);
  void init(int period);  
  void tick();
  void sendData();
  float readFromSonar();
  float readFromPot();
  

private:

  int pinLed1;
  int pinLed2;
  int pinEchoSonar;
  int pinTrigSonar;
  int pinPot;
  
  LedImpl* led1;
  LedImpl* led2;
  Potentiometer* pot;
  Sonar* sonar;
  
  float sonarData;
  float tempPot;  //da rimuovere
  float potData;

  float pos1, pos2;
  float vel_ist1, acc_ist1;
  
  enum { ON, OFF } stateLed1, stateLed2;
  const double vs = 331.45 + 0.62*20;

};

#endif
