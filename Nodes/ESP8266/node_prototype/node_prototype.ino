
/*
 * Date: 10/01/2017
 * Author: Liam Brand
 * Description:
 *
 * This software is designed to run on the ESP8266.
 * NodeMCU 1.0 (ESP-12E Module), 80MHz
 * 9600 baud
 *
 * This software will send random values to the EnergyMonitor.
 * This project is currently in prototype.
 *
 */

#include <ESP8266WiFi.h>
#include "WiFiConnection.h"
#include "FS.h"
#include "IoTNode.h"

// ---- SETTINGS ----

const int SERIAL_BAUDRATE = 9600; //115200?

const char* WIFI_AP_SSID = "IoT Setup ESP8266";
const char* WIFI_AP_PASSWORD = "IoT Setup";

const char* CONFIG_FILE = "/config.txt";
const char* CONNECTIONS_FILE = "/connections.txt";

IoTNode node;

// ---- SERVER FUNCTIONS ----

// Data structures

struct sample{
  int generation;
  int consumption;
};

// Hub settings, this is where we will post data to.

const int httpPort = 80;
const char* host = "192.168.2.128";
const char* server_root = "EnergyMonitor/www/";
WiFiClient client;

void connectToHub(void){
  if(!client.connect(host,httpPort)){
    Serial.print("Failed to connect to host ");
    Serial.print(host);
    Serial.print(":");
    Serial.println(httpPort);
  }
}

void sendHubData(void){

  String url = "/";
  url += String(server_root);
  url += "input/send_data.php";

  sample random_sample;
  random_sample.generation = random(1000);
  random_sample.consumption = random(2000);

  String data = "";
  data += "current_power_generation=" + String(random_sample.generation) + "&";
  data += "current_power_consumption=" + String(random_sample.consumption) + "&";
  data += "id=" + String(1);

  String nl = "\r\n";

  String request = "";
    request += "POST " + url + " HTTP/1.1" + nl +
               "Host: " + host + nl +
               "Cache-Control: no-cache" + nl +
               "Content-Type: application/x-www-form-urlencoded" + nl +
               "Content-Length: " + String(data.length()) + nl +
               nl +
               data;

  Serial.println("Request: -------");
  Serial.println(request);
  Serial.println("----------------");

  //send the request.

  /*

  if(client.available()) client.println(request);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  Serial.println("Response: ------");
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println("");
  Serial.println("----------------");
  */

}

// ---- MAIN CODE ----

void setup(void) {

  Serial.begin(SERIAL_BAUDRATE);
  //Serial.println("AT+RST");
  Serial.println("ESP8266");
  Serial.println("I support 2.4GHz Wireless... FYI.");
  randomSeed(analogRead(0));
  delay(2000);

  node = IoTNode::IoTNode(CONNECTIONS_FILE);

  node.setup();
}

void loop(void) {
  node.loop();
}
