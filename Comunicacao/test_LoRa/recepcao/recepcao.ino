//#include <SPI.h>
#include <LoRa.h>

const int csPin = 18;      // Pino CS (chip select) para LoRa
const int resetPin = 23;   // Pino de reset para LoRa
const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
  while (!Serial);      // Aguarda a inicialização da porta serial

  Serial.println("Inicializando LoRa...");

  // Configura os pinos SPI para LoRa
  LoRa.setPins(csPin, resetPin, irqPin);

  // Inicializa o módulo LoRa na frequência de 915 MHz (ajuste conforme necessário para sua região)
  if (!LoRa.begin(915E6)) {
    Serial.println("Erro ao iniciar LoRa.");
    while (1);
  }

  Serial.println("LoRa inicializado com sucesso.");
}

void loop() {
  // Tenta receber um pacote
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Lê o pacote recebido
    Serial.print("Pacote recebido: ");
    while (LoRa.available()) {
      String message = LoRa.readString();
      Serial.print(message);
    }
    Serial.println();
  }
}
