#include <Arduino.h>
#include <LoraHelper.h>

// Pinos Lora TTGO T-Beam
const int csPin = 18;      // Pino CS (chip select) para LoRa
const int resetPin = 23;   // Pino de reset para LoRa
const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa
// Frequência escolhida
const int freq = 915E6;

LoraHelper lora(csPin, resetPin, irqPin, freq);

void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (lora.iniciarLoRa()) {
        Serial.println("Receptor LoRa pronto.");
    }
}

void loop() {
    Pacote receivedData;
    if (lora.lerPacote(receivedData)) {
        Serial.print("Tempo: ");
        Serial.print(receivedData.missao.tempo);
        Serial.print(", Pacote: ");
        Serial.println(receivedData.missao.profundidade);
        Serial.print("Comando: ");
        Serial.println(receivedData.comando);
    }
}
