#include "TempAndHum.h"
#include "Arduino.h"
#include "DHT.h"

#define DHTTYPE DHT11

int pinTaH;
DHT dht(pinTaH, DHTTYPE);

TempAndHum::TempAndHum(int pin){
  pinTaH = pin;
}

float TempAndHum::getHumidity(){
  return dht.readHumidity();
}

float TempAndHum::getTemperature(){
  return dht.readTemperature();
}

float TempAndHum::getSpeedOfSound(){
  return (331.45 + (0.42 * dht.readTemperature()));
};
