/*
  HubAPI.h - HubAPI for IoT
  Created by Liam T. Brand, February 20, 2017.
*/

#include "Arduino.h"
#include "HubAPI.h"
#include <ESP8266WiFi.h>
#include "Message.h"

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

void HubAPI::notifyOfDisconnect()
{
  _disconnected = true;
}

void HubAPI::sendMessage(String message){
  _messageQueue.add(message);
}

_Bool HubAPI::hasMessage()
{
  return _messageInQueue.hasNext();
}

String HubAPI::getMessage()
{
  return _messageInQueue.getNext();
}

void HubAPI::loop()
{
  if(_disconnected){ // Try reconnect if we are disconnected.
    connect();
  }else{

    if(abs(millis() - _lastKeepAlivePacketSendTime) > _kaPacketPeriod){
      sendMessage(Message.KEEPALIVE);
      _lastKeepAlivePacketSendTime = millis();
    }
    
  }

  if (_client.available()) {
    _cIn = _client.read();
    if(_cIn == '\n'){
      _messageInQueue.add(_messageIn);
      _messageIn = "";
    }else{
      _messageIn += _cIn;
    }
  }

  if(!_disconnected){

    // If we have a message waiting to be sent:
    if(_messageQueue.hasNext()){
      msg = _messageQueue.getNext();
      _bytesSent = _client.println(msg);
      
      if(_bytesSent != msg.length()+2){
        notifyOfDisconnect();
      }
    }

  }
}
