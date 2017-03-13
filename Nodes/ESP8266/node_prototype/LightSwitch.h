/*
  LightSwitch.h - Interface to set the state of the light.
  Created by Liam T. Brand, March 13, 2017.
*/
#ifndef LightSwitch_h
#define LightSwitch_h

#include "Arduino.h"

class LightSwitch
{

  public:
    LightSwitch(int pin);

    _Bool isOn();

    void setOn();
    void setOff();

  private:
    int _PIN;

};

#endif
