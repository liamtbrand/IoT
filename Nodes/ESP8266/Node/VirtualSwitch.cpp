#include "VirtualSwitch.h"

VirtualSwitch::VirtualSwitch(_Bool state)
{
  _state = state;
  _lastState = _state;
}

_Bool VirtualSwitch::hasChangedState()
{
  if(_lastState != isOn()){
    return true;
  }else{
    return false;
  }
}

_Bool VirtualSwitch::readState()
{
  _lastState = isOn();
  return _lastState;
}

_Bool VirtualSwitch::isOn()
{
  return _state;
}

void VirtualSwitch::setState(_Bool state)
{
  _state = state;
  _lastState = !_state;
}
