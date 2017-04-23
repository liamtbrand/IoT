#ifndef Message_h
#define Message_h

#include "Arduino.h"

static class Message{
  public:
    const String VERSION = "VERSION:0.201";

    const String KEEPALIVE = "KEEPALIVE";

    const String LIGHT_ON = "LIGHT:ON";
    const String LIGHT_OFF = "LIGHT:OFF";
    const String LIGHT_QUERY = "LIGHT:?";

    const String SWITCH_ON = "SWITCH:ON";
    const String SWITCH_OFF = "SWITCH:OFF";
} Message;

#endif
