#include "Interrupts.h"
#include "Arduino.h"
#include <EnableInterrupt.h>

boolean handleInterrupt;
long timeInterrupts=0;

void handleInterrupts(){
  if(millis()-timeInterrupts>250){
    Serial.println("Ci sono - 1");
    Serial.flush();
    handleInterrupt = true;
    timeInterrupts = millis();
  }
}

void Interrupts::init(){
  enableInterrupt(8, handleInterrupts, RISING);
  enableInterrupt(12, handleInterrupts, RISING);
}
