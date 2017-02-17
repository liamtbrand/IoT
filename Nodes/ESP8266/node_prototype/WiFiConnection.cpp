/*
  WiFiConnection.h - Library for storing wifi connection information.
  Created by Liam T. Brand, February 18, 2017.
*/

#include "Arduino.h"
#include "WiFiConnection.h"

WiFiConnection::WiFiConnection()
{
  _connection_count = 0;
  _try_connection = 0;
}

bool WiFiConnection::add(const CONNECTION conn)
{
  if(_connection_count < MAX_CONNECTIONS){
    _connections[_connection_count] = conn;
    _connection_count++;
    return true;
  }
  return false;
}

void WiFiConnection::resetTryConnections()
{
  _try_connection = 0;
}

bool WiFiConnection::hasNext()
{
  return _try_connection < _connection_count;
}

CONNECTION WiFiConnection::getNext()
{
  _try_connection++;
  return _connections[_try_connection-1];
}
