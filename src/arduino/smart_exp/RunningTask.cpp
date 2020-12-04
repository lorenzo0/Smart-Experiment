#include "Sonar.h"
#include "Arduino.h"
#include "Potentiometer.h"
#include "RunningTask.h"
#include "MsgService.h"

/*
 * l'idea è quella di inviare, tramite seriale il minor numero di dati, data la poca memoria 
 * instanziabile. Verranno dunque memorizzate due variabili pos1 e pos2 da cui andremo a calcolare
 * vel_ist1 e acc_ist1 (la due non è calcolabile, ci servirebbe un terzo valore). Sarà poi il programma java
 * a memorizzarli per mostrare uno storico nella parte finale oltre, ovviamente, per riportare l'andamento
 * in tempo reale dell'oggetto.
*/


RunningTask::RunningTask(int pinLed1, int pinLed2, int pinEchoSonar,
                            int pinTrigSonar, int pinPot, int pinServoMotor, int pinTemp){
  this->pinLed1 = pinLed1;
  this->pinLed2 = pinLed2;
  this->pinEchoSonar = pinEchoSonar;
  this->pinTrigSonar = pinTrigSonar;
  this->pinPot = pinPot;
  this->pinServoMotor = pinServoMotor;
  this->pinTemp = pinTemp;
}

void RunningTask::init(int period){
  
  Task::init(period);

  led1 = new Led(pinLed1);
  led2 = new Led(pinLed2);
  pot = new Potentiometer(pinPot);
  sonar = new Sonar(pinEchoSonar, pinTrigSonar, pinTemp);
  pMotor = new ServoMotorImpl(pinServoMotor);
  pot = new Potentiometer(pinPot);
  firstVel= true;  
  calcAcel=false;
  Task::setFirstRun(false);
}

void RunningTask::tick(){

  if(!(Task::firstRun)){
    
    led2 -> switchOn();
    led1 -> switchOff();
    Task::setFirstRun(true);
    Task::setNextTask(0);

    
    
    for(int i=0; i<2; i++){
      pos[i] = 0;
      t[i] = 0;
    }
    
    tempPot = 1000;
    MsgService.sendMsg(String(tempPot));
    //funziona la lettura ma il potenziometro è scazzato
    //tempPot = pot -> readFromPotentiometer();
    
    
    Task::ts0 = millis();
    tStart = Task::ts0;
  
    pMotor->on();
      pMotor->setPosition(0);
    pMotor->off();
  
    cont = 0;
  }
  
  Task::currentTs = millis();

  /*
   * in questa task non c'è differenza se viene interrotto o completato il task,
   * viene dunque gestito in modo singolo
  */
  if(Task::currentTs - Task::ts0 > MAX_TIME){
    Task::setCompleted(true);
    Task::setFirstRun(false);
  }else{
  
    while(Task::currentTs - tStart < tempPot){
      Task::currentTs = millis();
    }
    
    saveData();
  }
}


void RunningTask::saveData(){
  for(int i=0; i<2; i++){
    //Serial.println("Pos[i]: "+ String(pos[i]));
    if(pos[i] == 0 && written != true){
      pos[i] = sonar -> getDistance();
      t[i] = millis();
      written = true;

      calculateVelocity();
    }
  }

  if(cont == 1){    
    for(int i=0; i<2; i++){
      //Serial.println("Pos[i]: "+ String(pos[i]));
    }
    pos[0] = pos[1];
    t[0] = t[1];
    
    pos[1] = 0;
    t[1] = 0;
    
    cont = 0;
  }

    written = false;
    tStart = Task::currentTs;
}
void RunningTask::calculateVelocity(){
  pMotor -> on();
  
  if(pos[1] != 0.0){
    cont++;
       if(firstVel==true){
        posServo =0;
        vel_ist[0] = abs(((pos[1] - pos[0])*100) / ((t[1] - t[0])/1000));

        for (int i = 0; i <= round(vel_ist[0]*6); i++) {
          //Serial.println(posServo);
          pMotor->setPosition(posServo);
          delay(10);
          posServo ++;
        }
        firstVel=false;
        calcAcel=true;
        MsgService.sendMsg(String(pos[0])+"|"+String(vel_ist[0])+"|0.0");

      }else{
        vel_ist[1] = abs(((pos[1] - pos[0])*100) / ((t[1] - t[0])/1000));
        if (vel_ist[1]<=vel_ist[0]){
          //Serial.println("sono in uno");
          posServo = round(vel_ist[0]*6);
          for (int i = 0; i <=round(vel_ist[0]*6-vel_ist[1]*6); i++) {
            //Serial.println(posServo);
            pMotor->setPosition(posServo);         
            delay(10);
            posServo --;
          }
        }else{
          //Serial.println("sono in due");
          posServo = round(vel_ist[0]*6);
          for (int i = 0; i <=round(vel_ist[1]*6-vel_ist[0]*6); i++) {
            //Serial.println(posServo);
            pMotor->setPosition(posServo);         
            delay(10);
            posServo ++;
          }
        }
       
      }

     /* Serial.print("vel_ist[0]*6: ");
      Serial.println(round(vel_ist[0]*6));*/
      
      if(calcAcel){
       /* Serial.println("-----------------");
        Serial.print("vel_ist[1]*6: ");
        Serial.println(round(vel_ist[1]*6));
        Serial.print("vel_ist[0]*6: ");
        Serial.println(round(vel_ist[0]*6));*/
        acc_ist = ((vel_ist[1] - vel_ist[0]) / (( t[1] - t[0])/1000));
        acc_ist = abs(acc_ist);
        MsgService.sendMsg(String(pos[1])+"|"+String(vel_ist[1])+"|"+String(acc_ist));
        //send pos[1] + vel[1] + acc_ist

        /*Serial.print("acc_ist: ");
        Serial.println(acc_ist);
      
        Serial.println("-----------------");*/
      
        vel_ist[0] = vel_ist[1];
        vel_ist[1] = 0;        
      }

      delay(500);

      
  }else{
    MsgService.sendMsg(String(pos[0])+"|0.0|0.0"); 
    //delay(1000);
    firstVel=true;
  }
    //Serial.println("Pos[0]: "+ String(pos[0]));
    //send position
  pMotor -> off();
}
