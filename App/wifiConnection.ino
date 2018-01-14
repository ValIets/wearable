#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include <ArduinoJson.h>
#define DEBUGGING

const char* ssid     = "oneplus";
const char* password = "fietsenhok";
char path[] = "/";
char host[] = "145.132.98.80";
int port = 24192;

StaticJsonBuffer<200> jsonBuffer;

JsonObject& jsonMessage = jsonBuffer.createObject();

boolean iscoming = false;
  
WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections
WiFiClient client;

void setupweb() {
  Serial.begin(115200);
  delay(10);



  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);
  

  // Connect to the websocket server
  if (client.connect(host, port)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
    while(1) {
      // Hang on failure
    }
  }
  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
    while(1) {
      // Hang on failure
    }  
  }

  jsonMessage["mac_address"] = WiFi.macAddress();
  jsonMessage["is_fallen"] = false;
  jsonMessage["has_low_battery"] = false;

  if (client.connected()) {
    String message;
    jsonMessage.printTo(message);
    webSocketClient.sendData(message);
  }

}


boolean sendhelp() {

  //TODO press X to JASON
  String message;
  jsonMessage["is_fallen"] = true;

  if (client.connected()) {
    jsonMessage.printTo(message);
    webSocketClient.sendData(message);
    
    String received;
    while (webSocketClient.socket_client->available() == false){
      delay(500);
      Serial.println("waiting for data");
    }
    if(webSocketClient.socket_client->available()){
      webSocketClient.getData(received);
      if (received.length() > 0) {
        Serial.print("Received data: ");
        Serial.println(received); 

        JsonObject& serverAnswer = jsonBuffer.parseObject(received);

        boolean is_coming = serverAnswer[String("is_coming")];
        
        if(is_coming){
          return true;
        } else {
          return false;
        }
      } else {
        Serial.print("RIP no data");
      }
    }
    
  } else {
    Serial.println("Client disconnected.");
    while (1) {
      // Hang on disconnect.
    }
  }
}

boolean confirmhelp() {
  if (client.connected()) {
    String received;
    
    while (webSocketClient.socket_client->available() == false){
      delay(500);
      Serial.println("waiting for data");
    }
    if(webSocketClient.socket_client->available()){
      webSocketClient.getData(received);
      if (received.length() > 0) {
        Serial.print("Received data: ");
        Serial.println(received); 
        
        JsonObject& serverAnswer = jsonBuffer.parseObject(received);

        boolean is_coming = serverAnswer[String("is_coming")];
        if(!is_coming){
          return true;
        } else {
          return false;
        }
      } else {
        Serial.print("RIP no data");
      }
    }
    
  } else {
    Serial.println("Client disconnected.");
    while (1) {
      // Hang on disconnect.
    }
  }
}

