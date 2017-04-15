/*
  WallSwitch.h - Interface to get the state of the wall switch.
  Created by Liam T. Brand, March 13, 2017.
*/

#include "WallSwitch.h"

WallSwitch::WallSwitch(int pin)
{
  _pin = pin;
}

_Bool WallSwitch::isOn()
{
  return digitalRead(_pin) == LOW ? true : false;
}
