/*
  WiFiAPs.h - Library for storing wifi connection information.
  Created by Liam T. Brand, February 18, 2017.
*/

// TODO note: ssid - character string containing network SSID (max. 63 characters)

#ifndef WiFiAPs_h
#define WiFiAPs_h

#include "Arduino.h"
#include "FS.h"

class WiFiAPs
{

  public:
    // Structure to store connection information
    static const int MAX_STRLEN = 128;
    struct CONNECTION{
      char ssid[MAX_STRLEN];
      char password[MAX_STRLEN];
    };
    // We will allow for a maximum of 8 wifi networks.
    static const int MAX_CONNECTIONS = 8;

    // Setup and manage connections
    WiFiAPs(const char* save_filename);
    bool add(const CONNECTION conn);
    bool add(const char* ssid, const char* password);
    void remove(const char* ssid);
    //void promote(const char* ssid);
    //void demote(const char* ssid);
    void save();
    void load();

    // Access connection data.
    void resetTryConnections();     // Resets the next connection to the first.
    bool hasNext();                 // If we have a next connection to try.
    CONNECTION getNext();           // Get the next connection to try.
    int count();                    // Get the number of connections we know.

    // Debug functions
    void list();

  private:
    const char* _save_filename = "";
    // Stores the connection information
    CONNECTION _connections[MAX_CONNECTIONS];
    int _connection_count = 0; // Current number of connections stored.
    int _try_connection = 0; // Which connection to try next.
};

#endif
