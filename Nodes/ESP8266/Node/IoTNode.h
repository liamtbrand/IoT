/*
  IoTNode.h - Node for IoT ESP8266
  Created by Liam T. Brand, February 18, 2017.
*/
#ifndef IoTNode_h
#define IoTNode_h

#include "Arduino.h"
#include "WiFiAPs.h"
#include "HubAPI.h"
#include "WallSwitch.h"
#include "LightSwitch.h"
#include "SetupController.h"

class IoTNode
{
  public:
    IoTNode(WiFiAPs* APs, const char* AP_ssid, const char* AP_pass, WallSwitch* wallSwitch, LightSwitch* lightSwitch, SetupController* setupController, HubAPI* hubAPI);

    WiFiAPs* _APs;

    void scanWiFi();
    void connectWiFi();

    void runInit();
    void runLoop();

    void setupInit();
    void setupLoop();

    void setup();
    void loop();

  private:
    const int _SETUP = 0;
    const int _RUN = 1;
    int _mode;
    int _initialized;
    unsigned long _last_try_connect;
    const char* _AP_ssid;
    const char* _AP_pass;
    int _networks_found = 0;

    WallSwitch* _wallSwitch;
    LightSwitch* _lightSwitch;

    SetupController* _setupController;
    HubAPI* _hubAPI;

};

#endif
