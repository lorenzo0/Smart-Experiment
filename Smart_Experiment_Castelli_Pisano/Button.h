#ifndef __BUTTON__
#define __BUTTON__

#include "ClickedButton.h"


class Button: public ClickedButton { 
  
public:
  Button(int pinButton);
  void getButtonState();
  
private:
  int pinButton;  
  
};

#endif
