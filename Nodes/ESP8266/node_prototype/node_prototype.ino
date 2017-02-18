
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

// ---- SETTINGS ----

const int SERIAL_BAUDRATE = 115200; //9600?

const char* WIFI_AP_SSID = "ESP8266 IoT Setup";
const char* WIFI_AP_PASSWORD = "IoT Setup";

const char* CONFIG_FILE = "/config.txt";
const char* CONNECTIONS_FILE = "/connections.txt";

IoTNode node;

// Node Modes
const int SETUP = 0;
const int NODE = 1;

// ---- GLOBAL VARIABLES ----

WiFiConnection connections(CONNECTIONS_FILE);

int MODE = SETUP;
bool INITIALIZED = false;

unsigned long last_try_connect = 0;

WiFiServer server(80);

// ---- SERVER FUNCTIONS ----

void hostWiFi(){
  Serial.println("Starting WiFi Access Point...");
  delay(1000);
  WiFi.softAP(WIFI_AP_SSID,WIFI_AP_PASSWORD);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(myIP);
}

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

int networks_found = 0;

void tryToConnectWiFi(void){
  scanWiFi();
  connectWiFi();
}

void scanWiFi(void){
  Serial.println("Scanning WiFi networks...");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  networks_found = n;
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

void connectWiFi(void){

  int tries = 0;
  connections.resetTryConnections();
  WiFiConnection::CONNECTION conn;

  while(connections.hasNext() && WiFi.status() != WL_CONNECTED){

    conn = connections.getNext();

    for(int n = 0; n < networks_found && WiFi.status() != WL_CONNECTED; ++n){

      //Serial.print("Checking: ");
      //Serial.println(conn.ssid);

      //Serial.print("Against: ");
      //Serial.println(WiFi.SSID(n).c_str());

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

// ---- SETUP CODE ----

void setupInit(void){

  Serial.println("Setup Init");

  hostWiFi();
  last_try_connect = millis();

  INITIALIZED = true;
}

void setupLoop(void){

  Serial.println("Setup Loop");

  // AP phase should last 120 seconds,
  // Then we should try again to connect to WiFi.
  if(millis() - last_try_connect > 20000){ // TODO change back to 120.. 20 for testing.
    if(connections.count() > 0){
      Serial.println("Switching to Node Mode.");
      MODE = NODE;
      INITIALIZED = false;
    }else{
      Serial.println("No known APs, please create one.");
    }
  }

  Serial.println("Waiting for connections...");
  delay(10000);
}

// ---- NODE CODE ----

void nodeInit(void){

  Serial.println("Node Init");

  if(connections.count() == 0){
    INITIALIZED = false;
    MODE = SETUP;
    return; // Exit early, cause no point trying to connect.
  }

  int max_attempts = 3;
  int attempt = 0;
  while(WiFi.status() != WL_CONNECTED && attempt < max_attempts) {
    tryToConnectWiFi();
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("Waiting 10s before trying again...");
      delay(10000);
    }else{
      // Success
      INITIALIZED = true;
      break;
    }
    ++attempt;
  }

  if(INITIALIZED == false){
    MODE = SETUP;
  }
}

void nodeLoop(void){

  Serial.println("Node Loop");

  if(WiFi.status() != WL_CONNECTED){
    INITIALIZED = false; // We will try to reconnect.
  }

  Serial.println("tick");
  delay(1000);
  Serial.println("tock");
  delay(1000);
  Serial.println("Waiting...");
  delay(3000);

  connectToHub();
  sendHubData();
}

// ---- MAIN CODE ----

void setup(void) {

  Serial.begin(9600);
  //Serial.println("AT+RST");
  Serial.println("ESP8266");
  Serial.println("I support 2.4GHz Wireless... FYI.");
  randomSeed(analogRead(0));
  delay(2000);

  // Reset all connections...
  connections.save();

  // Load in any stored connections.
  //connections.add("Liam's iPhone","derpderp");
  //connections.add("SPARK-8GAY6T","TZXFK93XZC");
  connections.load();
  connections.list();

  // If we have a network we know,
  // We should be in node mode.
  if(connections.count() > 0){
    MODE = NODE;
  }

}

void loop(void) {

  if(MODE == NODE){

    if(INITIALIZED == false) nodeInit();
    if(INITIALIZED == true) nodeLoop();

  }else if(MODE == SETUP){

    if(INITIALIZED == false) setupInit();
    if(INITIALIZED == true) setupLoop();

  }else{
    //ERRORS
  }

}
