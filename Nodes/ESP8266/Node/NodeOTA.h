#ifndef NodeOTA_h
#define NodeOTA_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

class NodeOTA
{
  public:
    NodeOTA();

    void setup();
    void loop();

  private:

};

#endif
