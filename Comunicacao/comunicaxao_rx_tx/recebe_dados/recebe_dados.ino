// Módulo ESP32 recebendo dados do Arduino via UART2
HardwareSerial SerialESP32(2); // Usando UART2 do ESP32

void setup() {
  Serial.begin(115200); // Comunicação serial com o PC para monitoramento
  SerialESP32.begin(9600, SERIAL_8N1, 25, 27); // Configura UART2: RX=GPIO25, TX=GPIO27
  Serial.println("ESP32 Iniciado e aguardando dados do Arduino...");
}

void loop() {
  if (SerialESP32.available()) {
    String mensagem = SerialESP32.readStringUntil('\n'); // Lê a mensagem até a quebra de linha
    Serial.print("Mensagem recebida: ");
    Serial.println(mensagem);
  }
}
