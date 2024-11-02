
#include <LoRa.h>

const int csPin = 18;      // Pino CS (chip select) para LoRa
const int resetPin = 23;   // Pino de reset para LoRa
const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa


void setup() {
  Serial.begin(115200); // Inicializa o console
  Serial2.begin(9600, SERIAL_8N1, 15, 14); // RX2=15, TX2=14 (UART2)

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
  if (Serial2.available()) {
    String incomingData = Serial2.readString(); // Ler dados recebidos pela UART2
    //String incomingData = Serial.readString();
    Serial.print("Recebido do Arduino: ");
    Serial.println(incomingData); // Exibir no console
      // Inicia a mensagem LoRa
  LoRa.beginPacket();
  LoRa.print(incomingData);
  LoRa.endPacket();
  }

  Serial2.println("Dados da ESP32 para Arduino via UART2"); // Enviar dados pela UART2
  delay(1000);
}
