#ifndef DebouncedPin_h
#define DebouncedPin_h

#include "Arduino.h"

class DebouncedPin
{
  public:
    DebouncedPin(int pin);

    int read();

  private:
    int _lastState;
    long int _lastSampleTime;
    long int _debounceTime;
    int _pin;
};

#endif
