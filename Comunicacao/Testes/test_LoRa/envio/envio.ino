#include <LoRa.h>

const int csPin = 18;      // Pino CS (chip select) para LoRa
const int resetPin = 23;   // Pino de reset para LoRa
const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa
int numero = 1;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(25,OUTPUT);

  digitalWrite(2,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(25,HIGH);
  
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

    // Inicia a mensagem LoRa
    LoRa.beginPacket();

    // Converte o número para um byte e o envia
    LoRa.write((uint8_t*)&numero, sizeof(numero));

    LoRa.endPacket();
  
    numero = numero*2;
    delay(2000); // Aguarda 2 segundos antes de enviar o próximo pacote
}
