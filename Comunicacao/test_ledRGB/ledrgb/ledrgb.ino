#include <SPI.h>
#include <LoRa.h>

const int csPin = 18;      // Pino CS (chip select) para LoRa
const int resetPin = 23;   // Pino de reset para LoRa
const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa

//////
const int pwmPinR = 13;  // Pino GPIO onde o PWM será gerado
const int pwmPinG = 15;  // Pino GPIO onde o PWM será gerado
const int pwmPinB = 25;  // Pino GPIO onde o PWM será gerado
int pinList[] = {pwmPinR, pwmPinG, pwmPinB};
void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
  while (!Serial);      // Aguarda a inicialização da porta serial
  pinMode(pwmPinR, OUTPUT);
  pinMode(pwmPinG, OUTPUT);
  pinMode(pwmPinB, OUTPUT);
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
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
      // Lê o pacote recebido
      byte message[packetSize];
      int i = 0;
      while (LoRa.available()) {
          message[i] = LoRa.read();
          i++;
      }
      Serial.print("Pacote recebido: ");
      for (int j = 0; j < packetSize; j++) {
          Serial.print(message[j]);
          analogWrite(pinList[j], message[j]);
          Serial.print(" ");
      }
      Serial.println();
  }
}

/*

void loop() {


  // Ajusta as cores do LED RGB
  analogWrite(pwmPinR, redValue);
  analogWrite(pwmPinG, greenValue);
  analogWrite(pwmPinB, blueValue);
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
/////////
/*
void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
  while (!Serial);      // Aguarda a inicialização da porta serial


}


*/
