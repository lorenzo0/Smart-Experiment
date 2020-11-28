#define PIR 7
#define LED_UNO 3
#define LED_DUE 5
#define SENS_TEMP_HUM 4
#define POT A0
#define BUTTON_START 13
#define BUTTON_END 12
#define SONAR_TRIG 10
#define SONAR_ECHO 11
#define SERVO_MOTOR 9

#define CALIBRATION_TIME_SEC 10
#define DHTTYPE DHT11

#include "Scheduler.h"
#include "IdleTask.h"
#include "ErrorTask.h"
#include "SleepModeTask.h"
#include "RunningTask.h"
#include "Interrupts.h"

Scheduler scheduler;

/*
 * Le costanti relative alla frequenza del potenziometro, 
 * vengono definite nella classe di implementazione 'Potentiometer.cpp'
*/

void setup(){
  pinMode(PIR,INPUT);
  pinMode(POT,INPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_END,INPUT);
  pinMode(SONAR_ECHO, INPUT); 

  pinMode(SONAR_TRIG, OUTPUT);
  pinMode(LED_UNO,OUTPUT);
  pinMode(LED_DUE,OUTPUT);

  Serial.begin(9600);

  /*Serial.print("Calibrating sensors... ");
  
  for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("SENSORS READY.");*/
  
  Task* errorTask = new ErrorTask(LED_UNO, LED_DUE);
  Task* idleTask = new IdleTask(LED_UNO, LED_DUE, BUTTON_START);
  Task* sleepTask = new SleepModeTask(LED_UNO, PIR);
  Task* runningTask = new RunningTask(LED_UNO, LED_DUE, SONAR_ECHO, SONAR_TRIG, POT, SERVO_MOTOR);
  
  scheduler.init(50);

  Interrupts* handlingInterrupts = new Interrupts();
  handlingInterrupts -> init();
  
  idleTask -> init(50);
  errorTask -> init(50);
  sleepTask -> init(50);
  runningTask -> init(50);

  scheduler.setIndexCurrentTaskActive(0);

  scheduler.addTask(idleTask);
  scheduler.addTask(errorTask);
  scheduler.addTask(sleepTask);
  scheduler.addTask(runningTask);

}

void loop() {
  scheduler.schedule();
}
