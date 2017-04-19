/*
  Switch.h - Interface to get the state of the wall switch.
  Created by Liam T. Brand, March 13, 2017.
*/
#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

class Switch
{
  public:
    virtual _Bool hasChangedState() = 0;
    virtual _Bool readState() = 0;
    virtual _Bool isOn() = 0;
};

#endif
