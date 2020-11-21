#ifndef __RUNNINGTASK__
#define __RUNNINGTASK__

#include "Task.h"
#include "Sonar.h"
#include "Led.h"
#include "Potentiometer.h"
#include "Servo/servo_motor_impl.h"
#include "Button.h"

class RunningTask: public Task{  

public: 

  RunningTask(int pinLed1, int pinLed2, int pinButtonStop, int pinEchoSonar,
                int pinTrigSonar, int pinPot, int pinServoMotor);
  void init(int period);  
  void tick();
  void sendData();
  void elaborateData();
  void saveData();
  void static handleInterrupts();
  void calculateVelocity(int cont);
  

private:

  int pinLed1;
  int pinLed2;
  int pinEchoSonar;
  int pinTrigSonar;
  int pinPot;
  int pinServoMotor;
  int pinButtonStop;
  int timeToCompleteTask;
  
  LedImpl* led1;
  LedImpl* led2;
  Potentiometer* pot;
  Sonar* sonar;
  ServoMotor* pMotor;
  Button* buttonToStop;
  
  float sonarData;
  float tempPot;  //da rimuovere
  float potData;

  float pos[4];
  double t[4], tStart;
  float vel_ist1, vel_ist2, acc_ist;
  boolean written;
  int cont;
  
  enum { ON, OFF } stateLed1, stateLed2;
  enum { CLICKED, NOTCLICKED } stateButton;
  const double vs = 331.45 + 0.62*20;

};

#endif
