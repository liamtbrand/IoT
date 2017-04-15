/*
  WallSwitch.h - Interface to get the state of the wall switch.
  Created by Liam T. Brand, March 13, 2017.
*/
#ifndef WallSwitch_h
#define WallSwitch_h

#include "Arduino.h"
#include "Switch.h"

class WallSwitch : public Switch
{
  public:
    WallSwitch(int pin);
    
    _Bool isOn();

  private:
    int _pin;
};

#endif
