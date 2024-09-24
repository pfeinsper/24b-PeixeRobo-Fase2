//#include <SPI.h>
#include <LoRa.h>

const int csPin = 18;      // Pino CS (chip select) para LoRa
const int resetPin = 23;   // Pino de reset para LoRa
const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa

const int ARRAY_SIZE = 1;
int16_t receivedArray[ARRAY_SIZE];  // Array para armazenar os números recebidos

union{
  struct{
    int16_t var1;
    int8_t var2;
    bool var3;
  } data;
  uint8_t raw[4]; 
}
memcpy

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
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    if (LoRa.readBytes((uint8_t*)receivedArray, sizeof(receivedArray)) == sizeof(receivedArray)) {
      Serial.println("Array de números recebido:");

      // Exibe os números recebidos e verifica cada um
      for (int i = 0; i < ARRAY_SIZE; i++) {
        Serial.print("Número ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(receivedArray[i]);
        Serial2.print(receivedArray[i]);
  //     // Lê o pacote recebido
  //     int16_t message[packetSize];
  //     int i = 0;
  //     while (LoRa.available()) {
  //         message[i] = LoRa.read();
  //         i++;
  //     }
  //     Serial.print("Pacote recebido: ");
  // for (int j = 0; j < packetSize; j++) {
  //     Serial.print(message[j]);
  //     Serial2.print(message[j]);
  //     Serial.print(" ");
  //     }
  //     Serial.println();
  }
  }
}
}