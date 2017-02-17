/*
  WiFiConnection.h - Library for storing wifi connection information.
  Created by Liam T. Brand, February 18, 2017.
*/
#ifndef WiFiConnection_h
#define WiFiConnection_h

#include "Arduino.h"
#include "FS.h"

class WiFiConnection
{
  public:
    struct CONNECTION{
        const char* ssid;
        const char* password;
    }

    // Setup and manage connections
    WiFiConnection();
    bool add(const CONNECTION conn);
    //void remove(const char* ssid);
    //void promote(const char* ssid);
    //void demote(const char* ssid);
    //void save(File f);
    //void load(File f);

    // Access connection data.
    void resetTryConnections();     // Resets the next connection to the first.
    bool hasNext();                 // If we have a next connection to try.
    CONNECTION getNext();           // Get the next connection to try.

  private:
    // We will allow for a maximum of 8 wifi networks.
    const int MAX_CONNECTIONS = 8;
    // Stores the connection information
    CONNECTION _connections[MAX_CONNECTIONS];
    int _connection_count = 0; // Current number of connections stored.
    int _try_connection = 0; // Which connection to try next.
};

#endif
