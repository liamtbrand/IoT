/*
  SetupController.h - Controller for setup of the device.
  Created by Liam T. Brand, February 18, 2017.
*/
#ifndef SetupController_h
#define SetupController_h

#include "Arduino.h"
#include "WiFiAPs.h"
#include <ESP8266WiFi.h>

class SetupController
{

  public:
    SetupController(WiFiServer* server, WiFiAPs* APs);

    String prepareSetupPageHTML();
    void loop();

  private:
    WiFiServer* _server;
    WiFiAPs* _APs;

};

#endif
