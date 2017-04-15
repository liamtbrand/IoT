#include "VirtualSwitch.h"

VirtualSwitch::VirtualSwitch(_Bool state)
{
  _state = state;
}

_Bool VirtualSwitch::isOn()
{
  return _state;
}

void VirtualSwitch::setOn()
{
  _state = true;
}

void VirtualSwitch::setOff()
{
  _state = false;
}
