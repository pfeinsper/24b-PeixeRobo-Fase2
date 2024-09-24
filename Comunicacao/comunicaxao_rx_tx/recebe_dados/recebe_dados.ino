#include <HardwareSerial.h>

HardwareSerial Serial2(2); // Definir UART2

void setup() {
  Serial.begin(115200); // Inicializa o console
  Serial2.begin(9600, SERIAL_8N1, 15, 14); // RX2=15, TX2=14 (UART2)
}

void loop() {
  if (Serial2.available()) {
    char incomingData = Serial2.read(); // Ler dados recebidos pela UART2
    Serial.print("Recebido do Arduino: ");
    Serial.println(incomingData); // Exibir no console
  }

  Serial2.println("Dados da ESP32 para Arduino via UART2"); // Enviar dados pela UART2
  delay(1000);
}
