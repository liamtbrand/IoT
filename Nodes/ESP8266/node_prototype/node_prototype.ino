
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

// ---- GLOBAL VARIABLES ----

WiFiConnection connections;

// ---- SERVER FUNCTIONS ----

void hostWiFi(){
  Serial.println("Starting WiFi Access Point...");
  delay(1000);
  WiFi.softAP(WIFI_AP_SSID,WIFI_AP_PASSWORD);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(myIP);
}

void serverSetup(){
  
  hostWiFi();

  /*
  SPIFFS.format(); //TODO make some test to verify this.
  SPIFFS.begin();

  config_file = SPIFFS.open(CONFIG_FILE,"w+");

  SPIFFS.end();
  */
}

void serverLoop(){
  
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
  client.println(request);

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
  
}

int networks_found = 0;

void setup(void) {
  
  Serial.begin(9600);
  //Serial.println("AT+RST");
  Serial.println("ESP8266");
  Serial.println("I support 2.4GHz Wireless... FYI.");
  randomSeed(analogRead(0));
  delay(2000);

  // Load in any stored connections.
  connections.load(CONNECTIONS_FILE);

  serverSetup();
  /*

  //add all the known WiFi authentication data.

  addConnection("Liam's iPhone","derpderp");
  addConnection("Jeroen's Wi-Fi Network","F6C461617D");
  addConnection(".","F6C461617D");
  */
}

void tryToConnectWiFi(void){
  scanWiFi();
  connectWiFi();
}
 
void loop(void) {

  serverLoop();
/*
  while(WiFi.status() != WL_CONNECTED) {
    tryToConnectWiFi();
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("Waiting 10s before trying again...");
      delay(10000);
    }
  }
  
  Serial.println("tick");
  delay(1000);
  Serial.println("tock");
  delay(1000);
  Serial.println("Waiting...");
  delay(3000);

  connectToHub();
  sendHubData();
  */
  
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
/*
  for(int n = 0; n < networks_found && WiFi.status() != WL_CONNECTED; ++n){
    for(int i = 0; i < MAX_CONNECTIONS && WiFi.status() != WL_CONNECTED; ++i){
      if(WiFi.SSID(n) == connections[i].ssid){ //if we know the network, try connect.
        
        Serial.print("Connecting to: ");
        Serial.println(connections[i].ssid);
        WiFi.mode(WIFI_STA);
        WiFi.begin(connections[i].ssid,connections[i].password);
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
          Serial.print(connections[i].ssid);
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

  */

}

