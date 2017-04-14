/*
  LightSwitch.h - Interface to set the state of the light.
  Created by Liam T. Brand, March 13, 2017.
*/

#include "LightSwitch.h"

LightSwitch::LightSwitch(int pin)
{
  _PIN = pin;
  // Set the light pin as output.
  pinMode(_PIN,OUTPUT);
  digitalWrite(_PIN,LOW);
  _on = false;
  
}

_Bool LightSwitch::isOn()
{
  return _on;
}

void LightSwitch::setOn(){
  digitalWrite(_PIN,HIGH);
  _on = true;
}

void LightSwitch::setOff(){
  digitalWrite(_PIN,LOW);
  _on = false;
}
