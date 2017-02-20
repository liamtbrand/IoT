/*
  HubAPI.h - HubAPI for IoT
  Created by Liam T. Brand, February 20, 2017.
*/
#ifndef HubAPI_h
#define HubAPI_h

#include "Arduino.h"
#include <ESP8266WiFi.h>

class HubAPI
{
  public:
    HubAPI(const char* address, int port);

    void connect();
    //bool connected();
    //void disconnect();

    //void send(); // Sends the specified data to the hub.
    //void next(); // Gets the next data from the hub.

    void loop();

  private:
    const char* _address;
    int _port;
    WiFiClient _client;
    int _LEDPin = 1;
    int _value = LOW;

};

#endif
