#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

 
const char *ssid = "Alexahome";
const char *password = "loranthus";
 
ESP8266WebServer server(80);
 
void handleSentVar() {
  
  if (server.hasArg("sensor_reading")) { // this is the variable sent from the client
    
    String readingInt = server.arg("sensor_reading");

 
    Serial.println(readingInt);
    server.send(200, "text/html", "Data received");
  }
}
 
void setup() 
{
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
 
  WiFi.softAP(ssid, password);
 
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/data/", HTTP_GET, handleSentVar);
  server.begin();
  Serial.println("HTTP server started");
 
}
 
void loop() {
  server.handleClient();
}
