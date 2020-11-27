#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__


class Potentiometer { 
  
public:
  Potentiometer(int pin);
  float readFromPotentiometer();
  
private:
  int pin;  
  float freq;
};

#endif
