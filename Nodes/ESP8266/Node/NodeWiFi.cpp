/*
  NodeWiFi.h - Node for IoT ESP8266
  Created by Liam T. Brand, February 18, 2017.
*/
#include "Arduino.h"
#include "NodeWiFi.h"
#include "WiFiAPs.h"
#include <ESP8266WiFi.h>

NodeWiFi::NodeWiFi(WiFiAPs* APs, const char* AP_ssid, const char* AP_pass)
{
  // File containing Access Point Authentication Data.
  _APs = APs;
  _mode = _SETUP;
  _initialized = false;
  _last_try_connect = 0;
  _AP_ssid = AP_ssid;
  _AP_pass = AP_pass;
}

void NodeWiFi::scanWiFi(void)
{
  Serial.println("Scanning WiFi networks...");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  _networks_found = n;
  Serial.println("Scan complete.");
  if (n == 0)
    Serial.println("No networks found.");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");
}

void NodeWiFi::connectWiFi(void)
{
  int tries = 0;
  _APs->resetTryConnections();
  WiFiAPs::CONNECTION conn;

  while(_APs->hasNext() && WiFi.status() != WL_CONNECTED){

    conn = _APs->getNext();

    for(int n = 0; n < _networks_found && WiFi.status() != WL_CONNECTED; ++n){

      if(strcmp(WiFi.SSID(n).c_str(),conn.ssid) == 0){ //if we know the network, try connect.

        Serial.print("Connecting to: ");
        Serial.println(conn.ssid);
        WiFi.mode(WIFI_STA);
        WiFi.begin(conn.ssid,conn.password);
        ++tries;

        //wait 10s for connection
        for(int x = 0; x < 10; ++x){
          delay(1000);
          Serial.print(".");
          if(WiFi.status() == WL_CONNECTED){
            break;
          }
        }

        Serial.println("");

        if(WiFi.status() != WL_CONNECTED){
          Serial.print("Connection to ");
          Serial.print(conn.ssid);
          Serial.println(" failed.");
        }

      }
    }
  }

  Serial.println("");

  if(WiFi.status() == WL_CONNECTED){
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }else{
    if(tries == 0) {
      Serial.println("No known networks available.");
    }
    Serial.println("Unable to establish a WiFi connection.");
  }

}

void NodeWiFi::runInit()
{
  Serial.println("Node Init");

  if(_APs->count() == 0){
    _initialized = false;
    _mode = _SETUP;
    return; // Exit early, cause no point trying to connect.
  }

  int max_attempts = 3;
  int attempt = 0;
  while(WiFi.status() != WL_CONNECTED && attempt < max_attempts) {
    scanWiFi();
    connectWiFi();
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("Waiting 10s before trying again...");
      delay(10000);
    }else{
      // Success
      _initialized = true;
      break;
    }
    ++attempt;
  }

  if(_initialized == false){
    _mode = _SETUP;
  }
}

void NodeWiFi::runLoop()
{

  if(WiFi.status() != WL_CONNECTED){
    _initialized = false; // We will try to reconnect.
  }

  //connectToHub();
  //sendHubData();
}

void NodeWiFi::setupInit()
{
  Serial.println("Setup Init");

  Serial.println("Starting WiFi Access Point...");
  delay(1000);
  WiFi.softAP(_AP_ssid,_AP_pass);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(myIP);

  _last_try_connect = millis();

  _initialized = true;
}

void NodeWiFi::setupLoop()
{
  //Serial.println("Setup Loop");

  // AP phase should last 120 seconds,
  // Then we should try again to connect to WiFi.
  
  if(millis() - _last_try_connect > _APTimeout){ 
    if(_APs->count() > 0){
      Serial.println("Switching to Node Mode.");
      _mode = _RUN;
      _initialized = false;
    }else{
      Serial.println("No known APs, please create one.");
      //delay(1000);
    }
  }

  //Serial.println("Waiting for connections...");
}

void NodeWiFi::setup()
{
  // Load in any stored connections.
  //_APs.add("Liam's iPhone","derpderp");
  //_APs.add("SPARK-8GAY6T","TZXFK93XZC");
  _APs->load();
  _APs->list();

  // If we have a network we know,
  // We should be in node mode.
  if(_APs->count() > 0){
    _mode = _RUN;
  }
}

void NodeWiFi::loop()
{
  switch(_mode){

    case 1: // _RUN
      if(_initialized == false) runInit();
      if(_initialized == true) runLoop();
      break;

    case 0: // _SETUP
      if(_initialized == false) setupInit();
      if(_initialized == true) setupLoop();
      break;

    default:
      Serial.println("Error in node switch.");
      break;
  }
}
