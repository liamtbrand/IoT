/*
  WiFiConnection.h - Library for storing wifi connection information.
  Created by Liam T. Brand, February 18, 2017.
*/

#include "Arduino.h"
#include "WiFiConnection.h"

WiFiConnection::WiFiConnection(const char* save_filename)
{
  _save_filename = save_filename;
  _connection_count = 0;
  _try_connection = 0;
}

bool WiFiConnection::add(const CONNECTION conn)
{
  if(_connection_count < MAX_CONNECTIONS){
    _connections[_connection_count] = conn;
    _connection_count++;
    save();
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

void WiFiConnection::remove(const char* ssid)
{

  // Temporary storage.
  CONNECTION conns[MAX_CONNECTIONS];
  int ptr = 0;

  // Copy all allowed data to temporary list.
  for(int i = 0; i < _connection_count; ++i){
    if(_connection[i].ssid != ssid){
      conns[ptr] = _connection[i];
      ptr++;
    }
  }

  // Rewrite data.
  _connection_count = ptr;
  for(int i = 0; i < ptr; ++i){
    _connection[i] = conns[i];
  }

  save();
}

void WiFiConnection::save()
{
  File f;
  f = SPIFFS.open(_save_filename,"w+");

  CONNECTION conn;

  resetTryConnections();
  while(hasNext()){
    conn = getNext();
    f.write(conn.ssid);
    f.write(conn.password);
  }

  f.close();
}

void WiFiConnection::load()
{

  File f;
  if(SPIFFS.exists(_save_filename)){
    f = SPIFFS.open(_save_filename,"r");
    _connection_count = 0;

    while(f.available()){
      _connections[_connection_count].ssid = f.readStringUntil('\n');
      _connections[_connection_count].password = f.readStringUntil('\n');
      _connection_count++;
    }

  }else{
    f = SPIFFS.open(_save_filename,"w+");
  }

  f.close();

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

int WiFiConnection::count()
{
  return _connection_count;
}

void WiFiConnection::list()
{
  for(int i = 0; i < _connection_count; ++i){
    Serial.print(_connections[i].ssid);
    Serial.print(":******");
  }
}
