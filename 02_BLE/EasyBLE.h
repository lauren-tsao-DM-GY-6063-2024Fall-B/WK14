#include <ArduinoBLE.h>

class EasyBLE {
public:
  EasyBLE() {}

  void setup(String& deviceName, String& serviceUUID) {
    EasyBLE::setupStatic(deviceName, serviceUUID, EasyBLE::CHARACTERISTIC_UUID);
  }

  void setValue(String& value) {
    BLE.central();
    EasyBLE::pCharacteristic->writeValue(value.c_str(), value.length());
  }

private:
  static BLECharacteristic* pCharacteristic;
  static String CHARACTERISTIC_UUID;

  static void setupStatic(String& deviceName, String& serviceUUID, String& charactUUID) {
    BLEService* mService = new BLEService(serviceUUID.c_str());
    EasyBLE::pCharacteristic = new BLECharacteristic(charactUUID.c_str(), BLERead | BLEWrite, 128);

    if(!BLE.begin()){
      Serial.println("BLE begin failed");
    }
    Serial.println("BLE started");

    BLE.setLocalName(deviceName.c_str());
    BLE.setAdvertisedService(*mService);
    mService->addCharacteristic(*pCharacteristic);
    BLE.addService(*mService);
    BLE.advertise();
  }
};

BLECharacteristic* EasyBLE::pCharacteristic;
String EasyBLE::CHARACTERISTIC_UUID("250b0d01-1b4f-4f16-9171-f63c733dbeef");
