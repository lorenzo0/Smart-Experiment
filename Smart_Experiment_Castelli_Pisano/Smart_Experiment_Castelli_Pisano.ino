#define PIR 7
#define LED_UNO 3
#define LED_DUE 5
#define SENS_TEMP_HUM 4
#define POT A0
#define BUTTON_START 9
#define BUTTON_END 12
#define SONAR_TRIG 10
#define SONAR_ECHO 11

#define CALIBRATION_TIME_SEC 10
#define DHTTYPE DHT11

#include "Scheduler.h"
#include "Idle.h"

Scheduler scheduler;

const int SLEEP_TIME  = 5 * 1000;
const int MAX_TIME = 20 * 1000;
const int ERROR_TIME = 2 * 1000;


void setup(){
  pinMode(PIR,INPUT);
  pinMode(POT,INPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_END,INPUT);
  pinMode(SONAR_ECHO, INPUT); 

  pinMode(SONAR_TRIG, OUTPUT);
  pinMode(LED_UNO,OUTPUT);
  pinMode(LED_DUE,OUTPUT);

  scheduler.init(100);

  Serial.begin(9600);
 
  Task* idleTask = new Idle(LED_UNO, LED_DUE, BUTTON_END);
  idleTask->init(SLEEP_TIME);

  scheduler.addTask(idleTask);
}

void loop() {
  scheduler.schedule();
}
