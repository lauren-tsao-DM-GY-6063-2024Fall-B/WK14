#include <ArduinoJson.h>

#include "EasyBLE.h"

String DEVICE_NAME("LDR");
String SERVICE_UUID("250b0d00-1b4f-4f16-9171-f63c733d2850"); // address that the UID (unique universal identifier) uses. (change the last 4 or 3 numbers if you want to run it, maybe something related to the NYU ID)

EasyBLE mBLE; // from the library

int a0Val = 0;
int a0Min = 5000;
int a0Max = 0;

void updateData() {
  StaticJsonDocument<128> resJson;
  JsonObject data = resJson.createNestedObject("data");
  JsonObject A0 = data.createNestedObject("A0");

  A0["value"] = a0Val;
  A0["min"] = a0Min;
  A0["max"] = a0Max;

  String resTxt = "";
  serializeJson(resJson, resTxt);

  mBLE.setValue(resTxt);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  mBLE.setup(DEVICE_NAME, SERVICE_UUID); // send everything over as a json string
}

void loop() {
  a0Val = analogRead(A0);
  a0Min = min(a0Min, a0Val);
  a0Max = max(a0Max, a0Val);

  updateData();
  delay(2);
}

// MAKE SURE THE SERVICE_UUID NUMBER IS THE SAME AS THE ONE ON THE P5JS FILE
// if the bluetooth doesn't work, try to change the baba at the end of the final line in the EasyBLE.h
