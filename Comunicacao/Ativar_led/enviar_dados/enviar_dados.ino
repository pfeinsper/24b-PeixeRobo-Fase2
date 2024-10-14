
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

 Serial.println("Tentando inicializar o LoRa...");
  bool loraInitialized = false;

  while (!loraInitialized) {
    // Tenta iniciar o módulo LoRa na frequência de 915 MHz
    if (LoRa.begin(915E6)) {
      Serial.println("LoRa inicializado com sucesso.");
      loraInitialized = true;
    } else {
      Serial.println("Erro ao iniciar LoRa. Tentando novamente...");
      delay(5000); // Aguarda 5 segundos antes de tentar novamente
    }
  }

  Serial.println("LoRa inicializado com sucesso.");
}

void loop() {
  // Inicia a mensagem LoRa
// Cria um buffer para armazenar os valores de cor
    int16_t dataBuffer[1];
    dataBuffer[0] = getInput();

    // Envia os valores de cor via LoRa
    LoRa.beginPacket();
    LoRa.write((uint8_t*)&dataBuffer, sizeof(dataBuffer));
    LoRa.endPacket();

  delay(1000);
}



int getInput() {
  Serial.println("Digite o valor entre -5000 e 5000 ");
  
  while (Serial.available() == 0) {
    // Espera até que o usuário digite algo
  }

  String inputString = Serial.readString();
  inputString.trim(); // Remove espaços em branco
  int value = inputString.toInt();

  // Garantir que o valor esteja no intervalo correto (0-255)
  value = constrain(value, -4500, 4500);
  Serial.println(value);
  Serial.print(" ajustado para: ");
  Serial.println(value);

  return value;
}