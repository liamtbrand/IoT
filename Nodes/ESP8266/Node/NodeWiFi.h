/*
  NodeWiFi.h - Node for IoT ESP8266
  Created by Liam T. Brand, February 18, 2017.
*/
#ifndef NodeWiFi_h
#define NodeWiFi_h

#include "Arduino.h"
#include "WiFiAPs.h"

class NodeWiFi
{
  public:
    NodeWiFi(WiFiAPs* APs, const char* AP_ssid, const char* AP_pass);

    WiFiAPs* _APs;

    void scanWiFi();
    void connectWiFi();

    void runInit();
    void runLoop();

    void setupInit();
    void setupLoop();

    void setup();
    void loop();

    // Notification of disconnect
    _Bool isConnected();

  private:
    const int _SETUP = 0;
    const int _RUN = 1;
    int _mode;
    int _initialized;
    unsigned long _last_try_connect;
    const char* _AP_ssid;
    const char* _AP_pass;
    int _networks_found = 0;
    unsigned long _APTimeout = 20000; // TODO change back to 120.. 20 for testing.

};

#endif
