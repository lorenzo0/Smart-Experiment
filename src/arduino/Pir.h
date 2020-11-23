#ifndef __PIR__
#define __PIR__

class Pir{ 
public:
  Pir(int pinPir);
  int getPresence();  
  
private:
  int pinPir;  
};

#endif
