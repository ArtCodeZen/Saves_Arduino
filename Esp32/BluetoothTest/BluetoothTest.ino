#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
String receivedData = "";

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");
  pinMode(2, OUTPUT);
  Serial.println("ESP32 Bluetooth Classic - Aguardando conexão...");
}
bool ledState = false;
void loop() {
  if (SerialBT.available()) {
    char receivedChar = SerialBT.read(); // Lê um caractere do BluetoothSerial
    // Verifica se recebeu uma linha completa
    if (receivedChar == '\n') {
      Serial.println("Dados recebidos: " + receivedData);
      if(receivedData.equals("led")){
        SerialBT.println(ledState? "led ligado" : "led desligado");
        digitalWrite(2, ledState);
        ledState = !ledState;
       
      }
      
     
      // Limpa a String para receber novos dados
      receivedData = "";
    }
    else{
      receivedData += receivedChar; // Adiciona o caractere à String
    }
  }

  // Aqui você pode fazer outras operações enquanto espera por dados do BluetoothSerial

  delay(200);
  
  
        
}
