#ifndef VirtualSwitch_h
#define VirtualSwitch_h

#include "Arduino.h"
#include "Switch.h"

class VirtualSwitch : public Switch
{
  public:
    VirtualSwitch(_Bool state);

    _Bool hasChangedState();
    _Bool readState();
    _Bool isOn();

    void setState(_Bool state);

  private:
    _Bool _lastState;
    _Bool _state;
};

#endif
