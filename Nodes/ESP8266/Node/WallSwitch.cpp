/*
  WallSwitch.h - Interface to get the state of the wall switch.
  Created by Liam T. Brand, March 13, 2017.
*/

#include "WallSwitch.h"

WallSwitch::WallSwitch(int pin)
{
  _pin = pin;
  _lastState = !isOn(); // push initial state.
}

_Bool WallSwitch::hasChangedState()
{
  if(_lastState != isOn()){
    return true;
  }else{
    return false;
  }
}

_Bool WallSwitch::readState()
{
  _lastState = isOn();
  return _lastState;
}

_Bool WallSwitch::isOn()
{
  return digitalRead(_pin) == LOW ? true : false;
}
