#include <Arduino.h>
#include <LoRa.h>
#include <LoraPeixe.h>

#define csPin 18
#define resetPin 23
#define irqPin 26


void setup() {
    Serial.begin(115200);
    LoRa.setPins(csPin, resetPin, irqPin);
    LoRa.begin(915E6);  // Inicializa na mesma frequência
}

void loop() {
    LoRa.beginPacket();
    LoRa.print("Olá, LoRa!");
    LoRa.endPacket();
    Serial.println("Mensagem enviada!");
    delay(500);  // Envia uma mensagem a cada segundo
}
