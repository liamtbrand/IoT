/*
  HubAPI.h - HubAPI for IoT
  Created by Liam T. Brand, February 20, 2017.
*/

#include "Arduino.h"
#include "HubAPI.h"
#include <ESP8266WiFi.h>

HubAPI::HubAPI(const char* address, int port)
{
  _address = address;
  _port = port;
}

void HubAPI::connect()
{
  Serial.println("Attempting to connect to hub...");
  if(!_client.connect(_address,_port)){
    Serial.println("Couldn't connect to hub...");
  }else{
    Serial.println("Connected to hub successfully.");
    _client.println("Test string! Works :)");
  }
}

void HubAPI::loop()
{
  if (_client.available()) {
    char c = _client.read();
    Serial.print(c);
  }

  digitalWrite(_LEDPin,_value);

}
