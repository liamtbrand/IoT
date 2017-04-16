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

    // State notification
    void notifyOfState(_Bool state);

    // Disconnect notification
    void notifyOfDisconnect();

    void loop();

  private:
    const char* _address;
    int _port;
    WiFiClient _client;
    uint8_t _LEDPin = 16;
    uint8_t _value = LOW;

    // State notification
    _Bool _state = false;
    _Bool _notifyOfState = false;
    _Bool _newState = false;

    // Data send check
    int _bytesSent = 0;

    // Disconnect status
    _Bool _disconnected = true;

};

#endif
