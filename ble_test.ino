#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define bleServerName "ESP32_BLETEST"

bool deviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Device Connected");
  };
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Device Disconnected");
  };
};

void setup() {


  Serial.begin(115200);

  Serial.println("Started running");

  BLEDevice::init(bleServerName);

  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  pServer->getAdvertising()->start();
  Serial.println("Waiting for a client...");

}

void loop() {

  if (deviceConnected) {
    Serial.println("SUCCESS!!");
  }

  delay(1000);
}