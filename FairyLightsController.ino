#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
// #include <zlib.h>

#include "index_html.h"
#include "main_js.h"
#include "main_css.h"
#include "config.h"
// #include "main_js_zip.h"

// Connectors data array details
#define CNTR_ARRAY_ROWS 4 // number of connecters supported
#define CNTR_ARRAY_COLS 2

const char* ssid = STASSID;
const char* password = STAPSK;
const uint EEPROM_SIZE = 512; //No. of bytes to reserve
int EEPROM_ADDR = 0;

ESP8266WebServer server(80);

// Status Led pin D0
const int led = 13;
uint INITIAL_BRIGHTNESS = 360;
/*
 Connector array
 [{<connecter pin>, <init vlaue>}]
*/
uint connecters[CNTR_ARRAY_ROWS][CNTR_ARRAY_COLS] = {{D1,INITIAL_BRIGHTNESS},{D2,INITIAL_BRIGHTNESS},
  {D3,INITIAL_BRIGHTNESS},{D4,INITIAL_BRIGHTNESS}};

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void writeState(uint* state, uint len){
  EEPROM_ADDR = 0;
  String msg="EEPROM Write: ";

  for(int i=0; i<len; ++i){
    // EEPROM.write(EEPROM_ADDR, state[i]);
    EEPROM.put(EEPROM_ADDR, state[i]);
    EEPROM_ADDR += sizeof(uint);
    msg += state[i];
    msg += '\n';
  }
  EEPROM.commit();
  Serial.println(msg);
}

void readState(uint * state){
  // uint state[CNTR_ARRAY_ROWS];
  EEPROM_ADDR = 0;
  String msg="EEPROM read: ";
  uint d;
  for(int i=0; i<CNTR_ARRAY_ROWS; ++i){
    EEPROM.get(EEPROM_ADDR, d);
    EEPROM_ADDR += sizeof(uint);
    state[i] = d;
    msg += d;
    msg += '\n';
  }  
  Serial.println(msg);
  // return &state[0];
}

void setupLights(){
  uint state[CNTR_ARRAY_ROWS];
  readState(state);
  for(int i=0; i<CNTR_ARRAY_ROWS; ++i){
    analogWrite(connecters[i][0],state[i]);
    connecters[i][1] = state[i];
  }
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);

  EEPROM.begin(EEPROM_SIZE);
  Serial.begin(115200);
  
  setupLights();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

   // *** mDNS Setup ***
  if (!MDNS.begin("flc"))
  { // Start the mDNS responder for esp8266.local
      Serial.println("Error setting up MDNS responder!");
  }
  else{
      Serial.println("mDNS responder started. \nConnect to: http://flc.local/");
      // Add service to MDNS-SD
      MDNS.addService("http", "tcp", 80);
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/main.js", []() {
    // server.sendHeader("Content-Encoding", "gzip");
    server.send(200, "application/javascript", main_js);
  });

  server.on("/main.css", []() {
    server.send(200, "text/css", main_css);
  });

  // Send a GET request to <ESP_IP>/slider?pin=<pin>&value=<inputMessage>
  server.on("/slider", HTTP_GET, [] () {
    String message = "Slider update:\n";
    uint cntr = -1;
    uint newValue = 0;
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      if(server.argName(i) == "pin"){
        cntr = server.arg(i).toInt()-1;
      }
      if(server.argName(i) == "value")
      {
        newValue = server.arg(i).toInt();
      }
      if(cntr >=0 && cntr <=CNTR_ARRAY_ROWS){
        connecters[cntr][1] = newValue;
        analogWrite(connecters[cntr][0] , connecters[cntr][1]);
      }
    }
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", message);
    Serial.println(message);
  }); 

  // Send a GET request to <ESP_IP>/toggle?pin=<pin>
  server.on("/toggle", HTTP_GET, [] () {
    String message = "Toggle update:\n";
    uint cntr=-1;
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i).toInt() + "\n";
      cntr = server.arg(i).toInt()-1;
      if(cntr >=0 && cntr < CNTR_ARRAY_ROWS){        
        if(connecters[cntr][1]>10)
          connecters[cntr][1] = 0;
        else  
          connecters[cntr][1] = INITIAL_BRIGHTNESS;
        analogWrite(connecters[cntr][0],connecters[cntr][1]);
      }
    }
    
    server.send(200, "text/plain", message);
    Serial.println(message);
  });

  // Get Controller connecters status
  server.on("/status",HTTP_GET, [] (){
    StaticJsonDocument<200> root;
    String payload = "";
    JsonArray status = root.createNestedArray("status");
    // uint state[CNTR_ARRAY_ROWS]; 
    // readState(state);
    for(int i=0; i<CNTR_ARRAY_ROWS; ++i){
      status.add(connecters[i][1]);
    }

    serializeJson(root, payload);
    Serial.println(payload);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/json", payload);
  }); 

  // Get Controller connecters status
  server.on("/readSavedVal",HTTP_GET, [] (){
    StaticJsonDocument<200> root;
    String payload = "";
    JsonArray status = root.createNestedArray("status");
    uint state[CNTR_ARRAY_ROWS]; 
    readState(state);
    for(int i=0; i<CNTR_ARRAY_ROWS; ++i){
      status.add(state[i]);
    }

    serializeJson(root, payload);
    Serial.println(payload);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/json", payload);
  }); 

  // Save lights brightness
  server.on("/saveState",HTTP_POST, [] (){
    StaticJsonDocument<200> root;
    String message = "Save State:\n";   
    uint *state;
    String postBody = server.arg("plain");  
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, postBody);
    if (error) {
        // if the file didn't open, print an error:
        Serial.print(F("Error parsing JSON "));
        Serial.println(error.c_str());
        String msg = error.c_str();
        server.send(400, F("text/html"), "Error in parsin json body! <br>" + msg); 
    } 
    else 
    {
      JsonObject postObj = doc.as<JsonObject>(); 
      uint16 len = 0;
      if(postObj.containsKey("len")){
        len = postObj["len"];
        message += "len: ";
        message += len + '\n';
        state = new uint(len);
      } 
      if(postObj.containsKey("state")) {
        String msg = postObj["state"];
        message += msg+'\n';
        for(int i=0; i<len; ++i){
          uint16 d = postObj["state"][i];
          state[i] = d;
          message += d;
          message += '\n';
        }
      }
      writeState(state, len);
      // readState();
    }
    
    Serial.println(message);
    server.sendHeader("Access-Control-Allow-Origin", "http://localhost:8080");
    server.send(200, "text/plain", "OK");
  }); 

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();  
}
