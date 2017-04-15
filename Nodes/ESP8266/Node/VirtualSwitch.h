#ifndef VirtualSwitch_h
#define VirtualSwitch_h

#include "Arduino.h"
#include "Switch.h"

class VirtualSwitch : public Switch
{
  public:
    VirtualSwitch(_Bool state);

    _Bool isOn();

    void setOn();
    void setOff();

  private:
    _Bool _state;
};

#endif
