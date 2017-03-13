/*
  LightSwitch.h - Interface to set the state of the light.
  Created by Liam T. Brand, March 13, 2017.
*/

#include "LightSwitch.h"

LightSwitch::LightSwitch(int pin)
{
  _PIN = pin;
}

_Bool LightSwitch::isOn()
{
  return digitalRead(_PIN) == LOW ? true : false;
}

void LightSwitch::setOn(){
  digitalWrite(_PIN,LOW);
}

void LightSwitch::setOff(){
  digitalWrite(_PIN,HIGH);
}
