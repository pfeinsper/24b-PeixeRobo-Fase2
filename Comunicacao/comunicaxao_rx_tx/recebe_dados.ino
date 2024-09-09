#include <HardwareSerial.h>

// Definir os pinos para RX e TX
#define RX_PIN 16  // Pino para RX
#define TX_PIN 17  // Pino para TX

// Criar um objeto Serial personalizado
HardwareSerial mySerial(1);  // Usando UART1

void setup() {
  // Inicializar a Serial principal (Serial Monitor)
  Serial.begin(115200);
  
  // Inicializar a Serial nos pinos definidos (RX e TX)
  mySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);  // Configura a baud rate e pinos

  Serial.println("ESP32 UART Receiver");
}

void loop() {
  // Verifica se há dados disponíveis na UART
  if (mySerial.available()) {
    // Lê os dados recebidos
    String receivedData = mySerial.readStringUntil('\n');  // Lê até encontrar nova linha
    Serial.print("Dados recebidos: ");
    Serial.println(receivedData);
  }

  delay(100);  // Pequeno delay para evitar sobrecarga
}
