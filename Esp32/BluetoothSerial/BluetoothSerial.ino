// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Note: Pairing is authenticated automatically by this device

#include "BluetoothSerial.h"
String device_name = "ESP32-BT-Slave";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

#define RXD2 16
#define TXD2 17

BluetoothSerial SerialBT;
uint8_t pin_len = 4;
const char *pin = "1234";
void setup() {
 
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);    // Serial 8n1 obrigatório!  
  SerialBT.begin(device_name);  //Bluetooth device name

  SerialBT.enableSSP(); // Habilita a configuração de senha  
  // Define a senha para emparelhamento
  esp_bt_gap_set_pin(ESP_BT_PIN_TYPE_FIXED, pin_len, (uint8_t*)pin);
  
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  //Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

void loop() {
  if (Serial2.available()) {
    SerialBT.write(Serial2.read());
  }
  if (SerialBT.available()) {
    Serial2.write(SerialBT.read());
  }
 
}
