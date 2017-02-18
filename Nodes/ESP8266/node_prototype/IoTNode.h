/*
  IoTNode.h - Node for IoT ESP8266
  Created by Liam T. Brand, February 18, 2017.
*/
#ifndef IoTNode_h
#define IoTNode_h

#include "Arduino.h"

class IoTNode
{

  public:
    IoTNode();

    WiFiConnection connections("/connections.txt");

    void setup();
    void loop();

  private:
    int _SETUP = 0;
    int _RUN = 1;
    _mode = _RUN; // Try run mode first.

};

#endif
