#ifndef __SONAR__
#define __SONAR__

class Sonar{
  
  int pinSonarEcho;
  int pinSonarTrig;
  
public: 

  Sonar(int pinSonarEcho, int pinSonarTrig);
  float tick();
  float getDistance();

};

#endif
