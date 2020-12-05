#include "Arduino.h"
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

/*
   * Nella task Running non c'è differenza se il task viene interrotto o completato,
   * viene dunque gestito in modo singolo, assegnando il nextTask allo stato di Idle
*/
  
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
    
    tempPot = pot -> readFromPotentiometer();
    MsgService.sendMsg(String(tempPot));    
    
    Task::ts0 = millis();
    tStart = Task::ts0;  
    cont = 0;
  }
  
  Task::currentTs = millis();

  if(Task::currentTs - Task::ts0 > MAX_TIME){
    Task::setCompleted(true);
    Task::setFirstRun(false);
  }else{

    /* 
     *  Devo eseguire saveData ogni -tot- millisecondi, 
     *  riempio dunque la distanza di questi due periodi attraverso
     *  un while che porta il microprocessore in busy waiting
    */
    
    while(Task::currentTs - tStart < tempPot){
      Task::currentTs = millis();
    }
    
    saveData();
  }
}

/*
 * La procedura saveData è strutturata in modo tale da mantenere all'interno di arduino il minor spazio di memoria occupato.
 * Per farlo, è stato pensato un meccanismo composto da due strutture dati formate da due sole posizioni. 
 * In queste, verranno memorizzate le ultime posizioni dell'oggetto in esame ed il tempo in cui sono state prese la misurazione.
 * Una volta completato lo spazio previsto delle strutture dati (tempPot*2, alla seconda iterazione di saveData), viene calcolata la velocità
 * istantanea_1 data dai dati a dispozione. Successivamente, viene sovrascritto in modo iterativo il dato in posizione [0] dal dato in 
 * posizione [1]. Da questa situazione in poi, verranno calcolate le velocità istantanee in ogni ciclo. Quando si avranno a disposizione
 * le due velocità istantanee verrà calcolata l'accellerazione istantanea. Come ultima operazione, viene prevista la sovra-scrittura della
 * velocità in posizione [0] con quella in posizione [1]. 
 * 
 * Per la comunicazione tramite seriale viene definito un pattern d'invio delle informazioni composto da tre campi, divise dal carattere |.
 * I dati inviati sono così strutturati:
 *    posizione corrente|velocità istantanea|accellerazione istantanea
 * 
 * Nel caso in cui velocità e/o l'accellerazione non sono calcolate, viene inviato un dato pari a 0.0
 * Nel programma JAVA viene poi gestita questa situazione.
 * 
 * N.B Questa procedura permette, oltre che occupare il minor spazio di memoria in arduino, anche di inviare solo le informazioni
 * -necessarie- tramite seriale al programma Java. Facendo così ottimiziamo entrambi i processi, garantendo una trasmissione rapida dei dati tramite seriale.
*/
void RunningTask::saveData(){
  for(int i=0; i<2; i++){
    if(pos[i] == 0 && written != true){
      pos[i] = sonar -> getDistance();
      t[i] = millis();
      written = true;

      calculateVelocity();
    }
  }

  if(cont == 1){
    
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
        vel_ist[0] = abs(((pos[1] - pos[0])*100) / ((t[1] - t[0])/1000));

        for (int i = 0; i <= round(vel_ist[0]*6); i++) {
          pMotor->setPosition(i);
          delay(10);
        }
        firstVel=false;
        calcAcel=true;
        MsgService.sendMsg(String(pos[0])+"|"+String(vel_ist[0])+"|0.0");

      }else{
        vel_ist[1] = abs(((pos[1] - pos[0])*100) / ((t[1] - t[0])/1000));
        
        if (vel_ist[1]<=vel_ist[0]){
          
          posServo = round(vel_ist[0]*6);
          
          for (int i = 0; i <=round(vel_ist[0]*6-vel_ist[1]*6); i++) {
            pMotor->setPosition(posServo);         
            delay(10);
            posServo --;
          }
          
        }else{
          
          posServo = round(vel_ist[0]*6);
          
          for (int i = 0; i <=round(vel_ist[1]*6-vel_ist[0]*6); i++) {
            pMotor->setPosition(posServo);         
            delay(10);
            posServo ++;
          }
        }
       
      }
      
      if(calcAcel){
        acc_ist = ((vel_ist[1] - vel_ist[0]) / (( t[1] - t[0])/1000));
        acc_ist = abs(acc_ist);
        MsgService.sendMsg(String(pos[1])+"|"+String(vel_ist[1])+"|"+String(acc_ist));
      
        vel_ist[0] = vel_ist[1];
        vel_ist[1] = 0;        
      }

      delay(500);

      
  }else{
    MsgService.sendMsg(String(pos[0])+"|0.0|0.0"); 
    firstVel=true;
  }
  pMotor -> off();
}
