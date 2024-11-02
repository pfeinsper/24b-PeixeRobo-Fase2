// Esse código deve ser carregado num Arduino Nano

#include <SoftwareSerial.h>

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial a 9600 bps
}

void loop() {
  Serial.println("Olá, ESP32!"); // Envia uma mensagem ao ESP32
  delay(1000); // Aguarda 1 segundo antes de enviar novamente
} 
