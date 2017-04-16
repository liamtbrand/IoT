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
  //Serial.println("Attempting to connect to hub...");
  _disconnected = !_client.connect(_address,_port);
}

void HubAPI::notifyOfState(_Bool state) // Notify that the light is on or off..
{
  _newState = state;
  _notifyOfState = true;
}

void HubAPI::notifyOfDisconnect()
{
  _disconnected = true;
}

void HubAPI::loop()
{
  if(_disconnected){ // Try reconnect if we are disconnected.
    connect();
  }

  if(!_disconnected){

    if (_client.available()) {
      char c = _client.read();
      Serial.print(c);
    }

    // If we are notifying of state, send notification.
    if(_notifyOfState == true){
      _notifyOfState = false;
      if(_newState != _state){
        _state = _newState;
        // Send message to hub...
        if(_state == true){
          _bytesSent = _client.println("STATE:ON");
          if(_bytesSent != 9){
            notifyOfDisconnect();
          }
        }else{
          _bytesSent = _client.println("STATE:OFF");
          if(_bytesSent != 10){
            notifyOfDisconnect();
          }
        }
      }
    }

  }
}
