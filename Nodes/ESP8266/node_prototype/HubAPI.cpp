/*
  HubAPI.h - HubAPI for IoT
  Created by Liam T. Brand, February 20, 2017.
*/

#include "Arduino.h"
#include "HubAPI.h"
#include <ESP8266WiFi.h>

HubAPI::HubAPI(const char* address, const int port)
{
  _address = address;
  _port = port;
}

HubAPI::connect()
{
  if(!client.connect(_address,_port)){
    Serial.println("Couldn't connect to hub...");
  }else{
    Serial.println("Connected to hub successfully.");
    client.println("Test string! Works :)");
  }
}

HubAPI::loop()
{
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
}
