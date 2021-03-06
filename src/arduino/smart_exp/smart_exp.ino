/*
 * AVVISO PER MODIFICARE LE COSTANTI RICHIESTE IN SPECIFICA.
 * 
 * Per modificare la minima e massima frequenza (in Hz) è necessario accedere alla classe Potentiometer.h
 * Per modificare la massima durata delle varie task invece:
 *    - SLEEP_TIME in IdleTask.h
 *    - MAX_TIME in RunningTask.h
 *    - ERROR_TIME in ErrorTask.h
 *    
 * Come richiesto, vengono inizialmente impostate così di seguito:
 *    - SLEEP_TIME  = 5 secondi
 *    - MAX_TIME = 20 secondi
 *    - ERROR_TIME = 2 secondi
 *    - MINFREQ = 1 Hz
 *    - MAXFREQ = 50 Hz
 *
 * N.B La massima velocità viene definita a 30 cm/s visto l'ambiente dove viene eseguito.
 * E' possibile comunque variare questo valore, stabilito a design time.
*/

#define PIR 7
#define LED_UNO 3
#define LED_DUE 5
#define SENS_TEMP_HUM 6
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
#include "MsgService.h"
#include "servo_motor_impl.h"

Scheduler scheduler;
ServoMotor* pMotor;

/* 
 *  In setup viene prevista una calibratura dei sensori, in particolare
 *  viene messo in azione il servomotore. Vengono inizializzate le task che sono previste
 *  per il corretto funzionamento del sistema;
 *    - idle task, stato di attesa
 *    - error task, si vuole mandare in esecuzione l'esperimento ma non viene identificato nessun oggetto
 *    - sleep task, risparmio energetico (modalità power down) massimo di arduino, rimane in ascolto l'interrupt handler
 *    - running task, task di esecuzioned dell'esperimento
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
  
  pMotor = new ServoMotorImpl(9);
  
  MsgService.sendMsg("CALIBRATION");
  pMotor->on();  
    for (int i = 0; i < 180; i++) {
      pMotor->setPosition(i);         
      delay(15);
    }
    for (int i = 180; i >= 0; i--) {
      pMotor->setPosition(i);         
      delay(15);
    }
   pMotor->off();
  
  Serial.println("SENSORS READY.");
  delay(200);
  
  Task* errorTask = new ErrorTask(LED_UNO, LED_DUE);
  Task* idleTask = new IdleTask(LED_UNO, LED_DUE, BUTTON_START);
  Task* sleepTask = new SleepModeTask(LED_UNO, PIR);
  Task* runningTask = new RunningTask(LED_UNO, LED_DUE, SONAR_ECHO, SONAR_TRIG, POT, SERVO_MOTOR, SENS_TEMP_HUM);
  
  scheduler.init(50);
  MsgService.init();

  Interrupts* handlingInterrupts = new Interrupts();
  handlingInterrupts -> init();
  
  idleTask -> init(50);
  errorTask -> init(50);
  sleepTask -> init(50);
  runningTask -> init(1000);

  scheduler.setIndexCurrentTaskActive(0);

  scheduler.addTask(idleTask);
  scheduler.addTask(errorTask);
  scheduler.addTask(sleepTask);
  scheduler.addTask(runningTask);

}

void loop() {
  scheduler.schedule();
}
