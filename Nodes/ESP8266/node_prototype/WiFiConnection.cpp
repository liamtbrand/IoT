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

bool WiFiConnection::add(const char* ssid, const char* password)
{
  CONNECTION conn;
  conn.ssid = ssid;
  conn.password = password;
  add(conn);
}

void WiFiConnection::load(const char* filename)
{
  /*
  File f;
  if(SPIFFS.exists(filename)){
    f = SPIFFS.open(filename,"r");
    _connection_count = 0;

    while(f.available()){
      _CONNECTIONS[_CONNECTION_COUNT].ssid = f.readStringUntil('\n');
      _CONNECTIONS[_CONNECTION_COUNT].password = f.readStringUntil('\n');
      _CONNECTION_COUNT++;
    }
    
  }else{
    f = SPIFFS.open(CONNECTIONS_FILE,"w+");
  }
  
  f.close();
  */
}

void WiFiConnection::resetTryConnections()
{
  _try_connection = 0;
}

bool WiFiConnection::hasNext()
{
  return _try_connection < _connection_count;
}

WiFiConnection::CONNECTION WiFiConnection::getNext()
{
  _try_connection++;
  return _connections[_try_connection-1];
}
