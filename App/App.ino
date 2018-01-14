#include <ESP8266WiFi.h>
#include<Wire.h>
WiFiServer server(80);//Service Port
 
void setup() {
  setupDetection();
  setupLED();
  setupweb();
}
void loop() {
  checkForFall();
}
