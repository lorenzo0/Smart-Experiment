#include "Arduino.h"
#include "Sonar.h"

Sonar::Sonar(int pinSonarEcho, int pinSonarTrig, int pinTemp){
  this->pinSonarEcho = pinSonarEcho;  
  this->pinSonarTrig = pinSonarTrig;
  this->pinTemp = pinTemp;

  temp = new TempAndHum(pinTemp);
}

float Sonar:: tick(){
  float distance = getDistance();
  return distance;
}

float Sonar:: getDistance(){
  const double vs = 331.45 + 0.62*20;
  Serial.println(String(temp -> getTemperature()));
  //const double vs = 331.45 + 0.62*( temp -> getTemperature());

  digitalWrite(pinSonarTrig,LOW);
  delayMicroseconds(3);
  digitalWrite(pinSonarTrig,HIGH);
  delayMicroseconds(5);
  digitalWrite(pinSonarTrig,LOW);
  
  long tUS = pulseInLong(pinSonarEcho, HIGH);

  double t = tUS / 1000.0 / 1000.0 / 2;
  double d = t*vs;
  return d;
}
