/*
  LightController.h - Interface to set the state of the light.
  Created by Liam T. Brand, March 13, 2017.
*/

#include "LightController.h"

LightController::LightController(int pin)
{
  _pin = pin;
  // Set the light pin as output.
  pinMode(_pin,OUTPUT);
  setState(false);
}

_Bool LightController::isOn()
{
  return _on;
}

void LightController::setState(_Bool state)
{
  _on = state;
  if(_on){
    digitalWrite(_pin,HIGH);
  }else{
    digitalWrite(_pin,LOW);
  }
}
