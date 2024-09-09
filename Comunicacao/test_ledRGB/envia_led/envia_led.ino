#include <SPI.h>
#include <LoRa.h>

const int csPin = 16;      // Pino CS (chip select) para LoRa
const int resetPin = 3;   // Pino de reset para LoRa
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
   Serial.println("VAMBORAAA");

    Serial.println("Enviando pacote...");
    int redValue = getInput("vermelho");
    int greenValue = getInput("verde");
    int blueValue = getInput("azul");

  // Inicia a mensagem LoRa
    // Cria um buffer para armazenar os valores de cor
    byte colorBuffer[3];
    colorBuffer[0] = redValue;
    colorBuffer[1] = greenValue;
    colorBuffer[2] = blueValue;

    // Envia os valores de cor via LoRa
    LoRa.beginPacket();
    LoRa.write(colorBuffer, sizeof(colorBuffer));
    LoRa.endPacket();

  delay(5000); // Aguarda 5 segundos antes de enviar o próximo pacote
}

int getInput(String colorName) {
  Serial.print("Digite o valor para ");
  Serial.print(colorName);
  Serial.print(": ");
  
  while (Serial.available() == 0) {
    // Espera até que o usuário digite algo
  }

  String inputString = Serial.readString();
  inputString.trim(); // Remove espaços em branco
  int value = inputString.toInt();

  // Garantir que o valor esteja no intervalo correto (0-255)
  value = constrain(value, 0, 255);

  Serial.print(colorName);
  Serial.print(" ajustado para: ");
  Serial.println(value);

  return value;
}
