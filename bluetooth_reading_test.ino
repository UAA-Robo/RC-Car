/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updated by chegewara

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 4fafc201-1fb5-459e-8fcc-c5c9c331914b
   And has a characteristic of: beb5483e-36e1-4688-b7f5-ea07361b26a8

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   A connect hander associated with the server starts a background task that performs notification
   every couple of seconds.
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ArduinoBlue.h> // ArduinoBlue bluetooth library

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

#define BLUETOOTH_TX 1 // Set your TX pin
#define BLUETOOTH_RX 3 // Set your RX pin

//EspSoftwareSerial::UART softSerial;

// SoftwareSerial softSerial(BLUETOOTH_TX, BLUETOOTH_RX);
ArduinoBlue phone(Serial1); // Object for smartphone robot control.ArduinoBlue phone(softSerial); // Object for smartphone robot control.

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

//#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define SERVICE_UUID        "f2c12ff2-f8a8-425d-a866-9a1a24ae4fb9"
#define CHARACTERISTIC_UUID "348c2643-3137-41fd-97bc-a8f66bc8df91"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};



void setup() {
  Serial.begin(115200);
  Serial1.begin(115200); 
  Serial.println("Herellll");

  
  // Check pins are valid
  //myPort.begin(38400, SWSERIAL_8N1, BLUETOOTH_RX, BLUETOOTH_TX, false);
  // softSerial.begin(115200, SWSERIAL_8N1, BLUETOOTH_RX, BLUETOOTH_TX, false);
  // if (!softSerial) { // If the object did not initialize, then its configuration is invalid
  //   Serial.println("Invalid EspSoftwareSerial pin configuration, check config"); 
  //   while (1) { // Don't continue with invalid configuration
  //     delay (1000);
  //   }
  // } 

  // Create the BLE Device
  BLEDevice::init("ESP32");
  Serial.println("Herelpppp");


  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  Serial.println("Here1");

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();

}

void loop() {
  Serial.println("Here2");

  //  if (pCharacteristic->getValue().length() > 0) {
  //   std::string rxValue = pCharacteristic->getValue();
  //   for (int i = 0; i < rxValue.length(); i++) {
  //     Serial1.write(rxValue[i]); // Send each character to ArduinoBlue
  //   }
  // }
  Serial.println("HERE!");
  //int throttle = phone.getThrottle() - 49;
  Serial.println("Throttle:");
  //Serial.println(throttle);

}