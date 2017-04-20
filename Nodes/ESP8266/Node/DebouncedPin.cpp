#include "Arduino.h"
#include "DebouncedPin.h"

DebouncedPin::DebouncedPin(int pin)
{
  _pin = pin;
  _lastSampleTime = millis();
  _debounceTime = 200;
  _lastState = digitalRead(_pin);
}

int DebouncedPin::read()
{
  if(digitalRead(_pin) != _lastState){
    if(abs(millis() - _lastSampleTime) > _debounceTime){
      if(_lastState == HIGH){
        _lastState = LOW;
      }else{
        _lastState = HIGH;
      }
      _lastSampleTime = millis();
    }
  }
  return _lastState;
}
