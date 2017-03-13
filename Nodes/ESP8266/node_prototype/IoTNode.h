/*
  IoTNode.h - Node for IoT ESP8266
  Created by Liam T. Brand, February 18, 2017.
*/
#ifndef IoTNode_h
#define IoTNode_h

#include "Arduino.h"
#include "WiFiConnection.h"
#include "HubAPI.h"

class IoTNode
{
  public:
    IoTNode(WiFiConnection* WiFiConn, const char* AP_ssid, const char* AP_pass);

    WiFiConnection* _APs;
    HubAPI _HubAPI = HubAPI("192.168.1.4",9999);

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

};

#endif
