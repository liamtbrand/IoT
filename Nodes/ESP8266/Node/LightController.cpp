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
  digitalWrite(_pin,LOW);
  _on = false;

}

_Bool LightController::isOn()
{
  return _on;
}

void LightController::setOn(){
  digitalWrite(_pin,HIGH);
  _on = true;
}

void LightController::setOff(){
  digitalWrite(_pin,LOW);
  _on = false;
}
