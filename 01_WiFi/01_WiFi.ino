#include <WebServer.h>
#include <WiFi.h>
#include "esp_wpa2.h"

#include <ArduinoJson.h>

#include "config.h"

WebServer server(80); // the default for web pages and web servers

int a0Val = 0;
int a0Min = 5000;
int a0Max = 0;

void handleNotFound() {
  server.send(404, "text/plain", "404! ADDRESS NOT FOUND"); // if sent an address that doesnt exist
}

void handleData() { // if sent an address that exists, create the following object
  StaticJsonDocument<128> resJson;
  JsonObject data = resJson.createNestedObject("data");
  JsonObject A0 = data.createNestedObject("A0");

  A0["value"] = a0Val;
  A0["min"] = a0Min;
  A0["max"] = a0Max; // until here

  String resTxt = "";
  serializeJson(resJson, resTxt); // turns the values into a string and sent to the client (i.e. whoever that requested data from the server)

  server.send(200, "application/json", resTxt);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {} // wait for serial to be available

  WiFi.disconnect(true); // all from the library example (disconnect wifi)
  WiFi.mode(WIFI_STA); // allow arduino to receive connection (connect to an existing network as a client to a router)
  WiFi.begin(SSID, SSID_PASSWORD); // password to the router (rename config.example.h that came with the file to config.h)

  int tryConnectCount = 0;
  while (WiFi.status() != WL_CONNECTED && tryConnectCount < 60) { // if wifi is not connected and havent tried 60 times (half second each time), 
    delay(500); // wait 30 seconds and try again
    Serial.print("."); // print address of the arduino
    tryConnectCount++;
  }
  Serial.println("");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi is NOT connected! 💩");
  }

  server.enableCORS(); // let any kind of client connect to the server (i.e. clients don't need to provide any special permission) (CORS)
  server.on("/data", handleData); // setting up an address (every time someone wants to connect)
  server.onNotFound(handleNotFound); // if unsuccessful in sending data, this is executed
  server.begin(); // turn on the server
}

void loop() {
  a0Val = analogRead(A0);
  a0Min = min(a0Min, a0Val); // current value, smallest value and biggest value
  a0Max = max(a0Max, a0Val);

  server.handleClient(); // if there was a request made to the arduino in the last millisecond
  delay(2);
}

// WHEN RUNNING THIS, CHECK THE SERIAL MONITOR FOR IP ADDRESS TO PUT INTO P5.JS