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

RunningTask::RunningTask(int pinLed1, int pinLed2, int pinEchoSonar, int pinTrigSonar, int pinPot){
  this->pinLed1 = pinLed1;
  this->pinLed2 = pinLed2;
  this->pinEchoSonar = pinEchoSonar;
  this->pinTrigSonar = pinTrigSonar;
  this->pinPot = pinPot;
}

void RunningTask::init(int period){
  Task::init(period);

  led1 = new Led(pinLed1);
  led2 = new Led(pinLed2);
  pot = new Potentiometer(pinPot);
  
  led2 -> switchOn();
  stateLed2 = ON;

  //funziona la lettura ma il potenziometro è scazzato
  tempPot = 200;
}

void RunningTask::tick(){
  Task::currentTs = millis();
  
  Serial.println(Task::currentTs);*/
  
  while(Task::currentTs - Task::ts0 < tempPot){
    Task::currentTs = millis();

    //TODO
  }


  Task::ts0 = Task::currentTs;
  
}

float RunningTask::readFromSonar()
{
    digitalWrite(pinTrigSonar,LOW);
    delayMicroseconds(3);
    digitalWrite(pinTrigSonar,HIGH);
    delayMicroseconds(5);
    digitalWrite(pinTrigSonar,LOW);

    //conversione in metri
    long tUS = pulseInLong(pinEchoSonar, HIGH);
    double t = tUS / 1000.0 / 1000.0 / 2;
    double d = t*vs;
    return d;
}

float RunningTask::readFromPot(){
  return pot->readFromPotentiometer();
}
