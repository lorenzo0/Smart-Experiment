#include "Sonar.h"
#include "Led.h"
#include "Arduino.h"
#include "Potentiometer.h"
#include "RunningTask.h"

/*
 * l'idea è quella di inviare, tramite seriale il minor numero di dati, data la poca memoria 
 * instanziabile. Verranno dunque memorizzate due variabili pos1 e pos2 da cui andremo a calcolare
 * vel_ist1 e acc_ist1 (la due non è calcolabile, ci servirebbe un terzo valore). Sarà poi il programma java
 * a memorizzarli per mostrare uno storico nella parte finale oltre, ovviamente, per riportare l'andamento
 * in tempo reale dell'oggetto.
*/


boolean stopRunning;

RunningTask::RunningTask(int pinLed1, int pinLed2, int pinEchoSonar,
                            int pinTrigSonar, int pinPot, int pinServoMotor){
  this->pinLed1 = pinLed1;
  this->pinLed2 = pinLed2;
  this->pinEchoSonar = pinEchoSonar;
  this->pinTrigSonar = pinTrigSonar;
  this->pinPot = pinPot;
  this->pinServoMotor = pinServoMotor;

  timeToCompleteTask = 0;
}

void RunningTask::init(int period){
  Task::init(period);
  timeToCompleteTask = period;

  led1 = new Led(pinLed1);
  led2 = new Led(pinLed2);
  pot = new Potentiometer(pinPot);
  sonar = new Sonar(pinEchoSonar, pinTrigSonar);
  pMotor = new ServoMotorImpl(pinServoMotor);
  
  led2 -> switchOn();
  stateLed2 = ON;

  led1 -> switchOff();
  stateLed2 = OFF;

  for(int i=0; i<4; i++){
    pos[i] = 0;
    t[i] = 0;
  }

  //funziona la lettura ma il potenziometro è scazzato
  tempPot = 600;
  
  Task::ts0 = millis();
  tStart = Task::ts0;

  cont = 0;

}

void RunningTask::tick(){
  Task::currentTs = millis();

  /*
   * in questa task non c'è differenza se viene interrotto o completato il task,
   * viene dunque gestito in modo singolo
  */
  if(Task::currentTs - Task::ts0 > timeToCompleteTask || stopRunning){
    Serial.println("Completato");
    Task::setCompleted();
    Task::setNextTask(0);
  }else{
  
    while(Task::currentTs - tStart < tempPot){
      Task::currentTs = millis();
    }
    
    saveData();
  }
 
}

void RunningTask::saveData(){
  for(int i=0; i<4; i++){
    if(pos[i] == 0.00 && written != true){
      pos[i] = sonar -> getDistance();
      t[i] = millis();
      written = true;
      
      cont++;
      calculateVelocity(cont);
    }

    
    
    if(pos[3] != 0.0){
        for(int i=0; i<4; i++){
            Serial.println(pos[i]);
          }
    
         for(int y=0; y<4;y++){
            pos[y] = 0;
            t[y] = 0;
         }
       pos[0] = sonar -> getDistance();
       t[0] = millis();
    }
  }

    written = false;
    tStart = Task::currentTs;
}
void RunningTask::calculateVelocity(int cont){
  pMotor -> on();

  switch(cont){
    case 2: 
      vel_ist1 = (((pos[1] - pos[0])*100) / ((t[1] - t[0])/1000));

      pMotor->setPosition(vel_ist1*6);

      delay(200);

      Serial.print("vel_ist1: ");
      Serial.println(vel_ist1);
      Serial.println("-----------------");
      break;

    case 4:

      vel_ist2 = (((pos[3] - pos[2])*100) / ((t[3] - t[2])/1000));

      pMotor->setPosition(vel_ist2*6);
      delay(200);

      Serial.print("vel_ist2: ");
      Serial.println(vel_ist2);

      acc_ist = ((vel_ist2 - vel_ist1) / ( t[3] - t[1])/1000);

      Serial.print("acc_ist: ");
      Serial.println(acc_ist);
    
      Serial.println("-----------------");
      this->cont = 0;
      break;
  }
  pMotor -> off();
}

void RunningTask::handleInterrupts(){
  stopRunning = true;
}
