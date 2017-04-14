/*
  SetupController.h - Controller for setup of the device.
  Created by Liam T. Brand, February 18, 2017.
*/

#include "SetupController.h"
#include <ESP8266WiFi.h>

SetupController::SetupController(WiFiServer* server, WiFiAPs* APs)
{
  _server = server;
  _server->begin();
  _APs = APs;
}

String SetupController::prepareSetupPageHTML()
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            //"Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            //"Analog input:  " + String(analogRead(A0)) +
            
            "<form action=\"/update-hub-details\"><fieldset><legend>Hub Details:</legend>" +
            "Hub IP: <br>" +
            "<input type=\"text\" name=\"ip\" value=\"192.168.1.4\"><br>" +
            "Hub Port: <br>" +
            "<input type=\"text\" name=\"port\" value=\"9999\"><br><br>" +
            "<input type=\"submit\" value=\"Update\">"+
            "</fieldset></form><br>" +
            
            "<fieldset><legend>WiFi Access Points:</legend>";
            
            _APs->resetTryConnections();
            if(!_APs->hasNext()){
              htmlPage += "No APs Saved...<br>";
            }
            while(_APs->hasNext()){
              WiFiAPs::CONNECTION conn = _APs->getNext();
              htmlPage += String(conn.ssid) + ":" + String(conn.password) + "<br>";
            }

            htmlPage += String("</fieldset><br>") +
            
            "<form action=\"/add-ap\"><fieldset><legend>Add AP:</legend>" +
            "SSID: <br>" +
            "<input type=\"text\" name=\"ssid\"><br>" +
            "Password: <br>" +
            "<input type=\"text\" name=\"password\"><br><br>" +
            "<input type=\"submit\" value=\"Add\">"+
            "</fieldset></form><br>" +

            "<form action=\"/remove-ap\"><fieldset><legend>Remove AP:</legend>" +
            "SSID: <br>" +
            "<input type=\"text\" name=\"ssid\"><br><br>" +
            "<input type=\"submit\" value=\"Remove\">"+
            "</fieldset></form> " +
            
            "</html>" +
            String("\r\n");
  return htmlPage;
}

void SetupController::loop()
{
  WiFiClient client = _server->available();
  //Serial.println(client);
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("\n[Client connected]");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          client.println(prepareSetupPageHTML());
          break;
        }
      }
    }
    delay(1); // give the web browser time to receive the data

    // close the connection:
    client.stop();
    Serial.println("[Client disonnected]");
  }
}
