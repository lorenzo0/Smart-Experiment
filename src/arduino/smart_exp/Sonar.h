#ifndef __SONAR__
#define __SONAR__

class Sonar{
  
public: 

  Sonar(int pinSonarEcho, int pinSonarTrig);
  float tick();
  float getDistance();

private:

  int pinSonarEcho;
  int pinSonarTrig;
};

#endif
