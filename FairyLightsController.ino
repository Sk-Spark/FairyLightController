#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
// #include <zlib.h>

#include "index_html.h"
#include "main_js.h"
#include "main_css.h"
#include "config.h"
// #include "main_js_zip.h"

// Connectors data array details
#define CNTR_ARRAY_ROWS 4
#define CNTR_ARRAY_COLS 2

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

// Status Led pin D0
const int led = 13;
/*
 Connector array
 [{<connecter pin>, <init vlaue>}]
*/
uint INITIAL_BRIGHTNESS = 360;
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

void setupLights(){
  for(int i=0; i<CNTR_ARRAY_ROWS; ++i){
      analogWrite(connecters[i][0],connecters[i][1]);
    }
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);

  setupLights();

  Serial.begin(115200);
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
    JsonArray data = root.createNestedArray("data");
    for(int i=0; i<CNTR_ARRAY_ROWS; ++i){
      data.add(connecters[i][1]);
    }

    serializeJson(root, payload);
    Serial.println(payload);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", payload);
  }); 

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  // // increase the LED brightness
  // for(int dutyCycle = 0; dutyCycle < 255; dutyCycle++){   
  //   // changing the LED brightness with PWM
  //   analogWrite(c1, dutyCycle);
  //   delay(10);
  // }

  // // decrease the LED brightness
  // for(int dutyCycle = 255; dutyCycle > 0; dutyCycle--){
  //   // changing the LED brightness with PWM
  //   analogWrite(c1, dutyCycle);
  //   delay(10);
  // }
}
