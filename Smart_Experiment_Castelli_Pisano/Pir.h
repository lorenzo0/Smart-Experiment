#ifndef __PIR__
#define __PIR__

class Pir{ 
public:
  Pir(int pinPir);
  int checkPresence();  
  
private:
  int pinPir;  
};

#endif
