
/*
 * Date: 10/01/2017
 * Author: Liam Brand
 * Description:
 *
 * This software is designed to run on the ESP8266.
 * NodeMCU 1.0 (ESP-12E Module), 80MHz
 * 9600 baud
 *
 */

#include <ESP8266WiFi.h>
#include "WiFiAPs.h"
#include "NodeWiFi.h"
#include "WallSwitch.h"
#include "LightController.h"
#include "PinMappings.h"
#include "VirtualSwitch.h"
#include "HubAPI.h"
#include "Message.h"
#include "NodeConfig.h"
#include "NodeOTA.h"

// ---- SETTINGS ----

const int SERIAL_BAUDRATE = 9600; //115200?

const char* CONFIG_FILE = "/config.txt";
NodeConfig nodeConfig(CONFIG_FILE);

const char* CONNECTIONS_FILE = "/connections.txt";
WiFiAPs APs(CONNECTIONS_FILE);

WallSwitch wallSwitch(PIN.D1);
VirtualSwitch virtualSwitch = new VirtualSwitch(false);
LightController lightController(PIN.D2);

HubAPI hubAPI(nodeConfig.getHubAddress(),nodeConfig.getHubPort());

NodeWiFi nodeWiFi(&APs,nodeConfig.getAPSSID(),nodeConfig.getAPPassword());

NodeOTA nodeOTA;

// ---- MAIN CODE ----

void setup(void) {

  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("ESP8266");
  Serial.println("I support 2.4GHz Wireless... FYI.");
  randomSeed(analogRead(0));

  Serial.println("WiFi Setup");

  nodeWiFi.setup();

  nodeOTA.setup();

  hubAPI.sendMessage(Message.LIGHT_QUERY); // Request light state push back
}

void loop(void) {

  // Check for over the air updates.
  nodeOTA.loop();

  // Manage the wifi connections.
  nodeWiFi.loop();

  // Check for light updates. Communicate with hub.
  hubAPI.loop();

  if(hubAPI.hasMessage()){
    // If there is a message waiting, process it.
    String message = hubAPI.getMessage();

    if(message == Message.LIGHT_ON){
      virtualSwitch.setState(true);
    }
    if(message == Message.LIGHT_OFF){
      virtualSwitch.setState(false);
    }
  }

  // If the wall switch has changed state, queue a notification.
  if(wallSwitch.hasChangedState()){
    if(wallSwitch.readState()){
      hubAPI.sendMessage(Message.SWITCH_ON);
    }else{
      hubAPI.sendMessage(Message.SWITCH_OFF);
    }
  }

  // If the virtual switch has changed state, push the change to the light.
  // The light should always reflect what the virtual switch is doing.
  if(virtualSwitch.hasChangedState()){
    Serial.println("SETTING STATE");
    lightController.setState(virtualSwitch.readState());
  }

}
