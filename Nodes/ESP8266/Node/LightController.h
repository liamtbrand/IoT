/*
  LightController.h - Interface to set the state of the light.
  Created by Liam T. Brand, March 13, 2017.
*/
#ifndef LightController_h
#define LightController_h

#include "Arduino.h"

class LightController
{

  public:
    LightController(int pin);

    _Bool isOn();
    void setOn();
    void setOff();

  private:
    int _pin;
    _Bool _on;

};

#endif
