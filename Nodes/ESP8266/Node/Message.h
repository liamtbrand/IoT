#ifndef Message_h
#define Message_h

#include "Arduino.h"

static class Message{
  public:
    const String LIGHT_ON = "LIGHT:ON";
    const String LIGHT_OFF = "LIGHT:OFF";
    const String LIGHT_QUERY = "LIGHT:?";

    const String SWITCH_ON = "SWITCH:ON";
    const String SWITCH_OFF = "SWITCH:OFF";
} Message;

#endif
