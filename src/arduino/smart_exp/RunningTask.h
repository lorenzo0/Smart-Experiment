#ifndef __RUNNINGTASK__
#define __RUNNINGTASK__

#include "Task.h"
#include "Sonar.h"
#include "Led.h"
#include "Potentiometer.h"
#include "servo_motor_impl.h"
#include "Button.h"

class RunningTask: public Task{  

public: 

  RunningTask(int pinLed1, int pinLed2, int pinEchoSonar,
                int pinTrigSonar, int pinPot, int pinServoMotor, int pinTemp);
  void init(int period);  
  void tick();
  void sendData();
  void elaborateData();
  void saveData();
  void sendSingleData();
  void static handleInterrupts();
  void calculateVelocity();
  

private:

  int pinLed1;
  int pinLed2;
  int pinEchoSonar;
  int pinTrigSonar;
  int pinPot;
  int pinServoMotor;
  int pinButtonStop;
  int pinTemp;
  
  LedImpl* led1;
  LedImpl* led2;
  Potentiometer* pot;
  Sonar* sonar;
  ServoMotor* pMotor;
  
  float sonarData;
  float tempPot;  //da rimuovere
  float potData;

  float pos[2], vel_ist[2];
  double t[2], tStart;
  float acc_ist;
  boolean written, firstVel, calcAcel;
  int cont;
 
  const int MAX_TIME = 20 * 1000;

  int delta =1;
  int posServo;

};

#endif
