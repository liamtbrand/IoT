/*
  HubAPI.h - HubAPI for IoT
  Created by Liam T. Brand, February 20, 2017.
*/
#ifndef HubAPI_h
#define HubAPI_h

#include "Arduino.h"

class HubAPI
{
  public:
    HubAPI(const char* address, const int port);

    void connect();
    //bool connected();
    //void disconnect();

    //void send(); // Sends the specified data to the hub.
    //void next(); // Gets the next data from the hub.

    void loop();

  private:
    const char* _address;
    const int _port;

};

#endif
