#ifndef __SONAR__
#define __SONAR__
#include "TempAndHum.h"
class Sonar{
  
public: 

  Sonar(int pinSonarEcho, int pinSonarTrig, int pinTemp);
  float tick();
  float getDistance();

private:

  int pinSonarEcho;
  int pinSonarTrig;
  int pinTemp;
  TempAndHum* temp;
  
};

#endif
