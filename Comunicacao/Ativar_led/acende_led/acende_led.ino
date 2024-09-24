#include <SoftwareSerial.h>

// Cria uma porta serial em pinos 10 e 11
SoftwareSerial mySerial(10, 11); // RX, TX

int ledPin = 13;  // LED no pino 13 (ou outro pino de sua escolha)

void setup() {
  // Configura a comunicação serial
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(ledPin, OUTPUT);  // Configura o pino do LED como saída
  digitalWrite(ledPin, LOW);  // Inicialmente o LED está desligado
  Serial.print("prepado para receber");
}

void loop() {
  if (mySerial.available() > 0) {
    // Lê o valor recebido da outra placa
    int16_t valorRecebido = mySerial.parseInt();  // Lê número inteiro
    Serial.println("RECEBEU");
    Serial.println(valorRecebido);
    // Mostra o valor recebido no Serial Monitor
    Serial.print("Valor recebido via UART: ");
    Serial.println(valorRecebido);

    // Acende ou apaga o LED baseado no valor recebido
    if (valorRecebido > 0) {
      Serial.println("acende");

      digitalWrite(ledPin, HIGH);
    } else {
      Serial.println("Apaga");

      digitalWrite(ledPin, LOW);
    }
  }
}
