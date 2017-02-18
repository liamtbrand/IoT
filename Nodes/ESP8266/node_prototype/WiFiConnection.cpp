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
  strcpy(conn.ssid,ssid);
  strcpy(conn.password,password);
  add(conn);
}

void WiFiConnection::remove(const char* ssid)
{

  // Temporary storage.
  CONNECTION conns[MAX_CONNECTIONS];
  int ptr = 0;

  // Copy all allowed data to temporary list.
  for(int i = 0; i < _connection_count; ++i){
    if(_connections[i].ssid != ssid){
      conns[ptr] = _connections[i];
      ptr++;
    }
  }

  // Rewrite data.
  _connection_count = ptr;
  for(int i = 0; i < ptr; ++i){
    _connections[i] = conns[i];
  }

  save();
}

void WiFiConnection::save()
{
  Serial.println("Saving...");
  File f;
  SPIFFS.begin();
  f = SPIFFS.open(_save_filename,"w");
  if(!f) Serial.println("Error opening file to write..");
  else{

    //Serial.println("Saving connection settings...");
  
    resetTryConnections();
    while(hasNext()){
      CONNECTION conn;
      conn = getNext();
      f.print(conn.ssid);
      f.print('\n');
      f.print(conn.password);
      f.print('\n');
      Serial.print("Saving record: ");
      Serial.print(conn.ssid);
      Serial.print(":");
      Serial.println(conn.password);
      //Serial.println("Saved record:");
      //Serial.println(conn.ssid);
    }
  
  }
  f.close();
  SPIFFS.end();
}

void WiFiConnection::load()
{
  Serial.println("Loading...");
  Serial.println(_save_filename);
  File f;
  SPIFFS.begin();
  
  if(SPIFFS.exists(_save_filename)){
    f = SPIFFS.open(_save_filename,"r");
    if(!f){
      Serial.println("Error opening file for read...");
    }else{
      _connection_count = 0;
      const int buff_size = 128;
      char buff[buff_size] = "";
      int len;

      while(f.available()){

        CONNECTION conn;

        len = f.readBytesUntil('\n',buff,buff_size);
        buff[len] = '\0';
        strcpy(conn.ssid,buff);

        len = f.readBytesUntil('\n',buff,buff_size);
        buff[len] = '\0';
        strcpy(conn.password,buff);

        _connections[_connection_count] = conn;
        _connection_count++;
        
      }
      
    }

  }else{
    Serial.println("Connection save file doesn't exist.");
    f = SPIFFS.open(_save_filename,"w+");
  }

  f.close();
  SPIFFS.end();

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
  Serial.println("List APs:");
  for(int i = 0; i < _connection_count; ++i){
    Serial.print(_connections[i].ssid);
    Serial.println(":******");
  }
}
