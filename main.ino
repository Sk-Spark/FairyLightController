#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "SparkMI"
#define STAPSK  "123456789"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

extern const char index_html[];

ESP8266WebServer server(80);

const int led = 13;
uint c1 = 4;

void handleRoot() {
  // server.send(200, "text/plain", "hello from esp8266!");
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

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  //C1
  // pinMode(c1, OUTPUT);
  analogWrite(c1,0);

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

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  // Send a GET request to <ESP_IP>/slider?pin=<pin>&value=<inputMessage>
  server.on("/slider", HTTP_GET, [] () {
    String message = "Slider update:\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      if(server.argName(i) == "value")
      {
        analogWrite(c1,server.arg(i).toInt());
      }
    }
    server.send(200, "text/plain", message);
    Serial.println(message);
  }); 

  // Send a GET request to <ESP_IP>/toggle?pin=<pin>
  server.on("/toggle", HTTP_GET, [] () {
    String message = "Toggle update:\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(200, "text/plain", message);
    Serial.println(message);
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
