#ifndef __TEMPANDHUM__
#define __TEMPANDHUM__

class TempAndHum { 
  
public:
  TempAndHum(int pin);
  float getHumidity();
  float getTemperature();
  float getSpeedOfSound();
  
};

#endif
