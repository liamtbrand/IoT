/*
  SetupController.h - Controller for setup of the device.
  Created by Liam T. Brand, February 18, 2017.
*/
#ifndef SetupController_h
#define SetupController_h

#include "Arduino.h"
#include "WiFiConnection"

class SetupController
{

  public:
    SetupController(WiFiConnection conns);

    void loop();

  private:

};

#endif
