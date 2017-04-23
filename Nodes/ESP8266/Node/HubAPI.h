/*
  HubAPI.h - HubAPI for IoT
  Created by Liam T. Brand, February 20, 2017.
*/
#ifndef HubAPI_h
#define HubAPI_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "FIFOQueue.h"

class HubAPI
{
  public:
    HubAPI(const char* address, int port);

    void connect();
    //bool connected();
    //void disconnect();

    //void send(); // Sends the specified data to the hub.
    //void next(); // Gets the next data from the hub.

    // Disconnect notification
    void notifyOfDisconnect();

    // Queue a message to be sent to the hub.
    void sendMessage(String message);

    _Bool hasMessage();
    String getMessage();

    void loop();

  private:
    const char* _address;
    int _port;
    WiFiClient _client;

    FIFOQueue _messageQueue;
    FIFOQueue _messageInQueue;
    
    char _cIn;
    String _messageIn;

    // Data send check
    int _bytesSent = 0;
    String msg;

    // Disconnect status
    _Bool _disconnected = true;

    // Last keepalive packet sent
    long int _lastKeepAlivePacketSendTime = 0;
    long int _kaPacketPeriod = 10000;

};

#endif
