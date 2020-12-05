#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__


class Potentiometer { 
  
public:
  Potentiometer(int pin);
  float readFromPotentiometer();
  
private:
  int pin;  
  float freq;

  const int MAXFREQ = 1;
  const int MINFREQ = 50;
};

#endif
