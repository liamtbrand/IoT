/*
  WallSwitch.h - Interface to get the state of the wall switch.
  Created by Liam T. Brand, March 13, 2017.
*/

#include "WallSwitch.h"
#include "DebouncedPin.h"

WallSwitch::WallSwitch(int pin)
{
  _debouncedPin = new DebouncedPin(pin);
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
  return _debouncedPin->read() == LOW ? true : false;
}
