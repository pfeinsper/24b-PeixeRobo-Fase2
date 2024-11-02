#include <WiFi.h>

// Defina o SSID e a senha da rede Wi-Fi do hotspot
const char* ssid = "teste_wifi";
const char* password = "vambora123";

// Defina o IP do servidor ESP32 (ajuste conforme o endereço IP obtido)
const char* serverIP = "192.168.137.138"; // Exemplo: "192.168.137.141"
const int serverPort = 80; // Porta do servidor

int num = 1;
WiFiClient client;
unsigned long lastAttemptTime = 0;  // Tempo da última tentativa de conexão
const long reconnectionInterval = 10000; // 10 segundos entre tentativas de reconexão

void setup() {
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(25, OUTPUT);

  digitalWrite(2, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(25, HIGH);
  Serial.begin(115200);

  // Conecte-se ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando-se à rede Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConectado!");

  // Conectar ao servidor pela primeira vez
  connectToServer();
}

void loop() {
  // Verifica se está conectado ao Wi-Fi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Desconectado do Wi-Fi. Tentando reconectar...");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nReconectado ao Wi-Fi.");
  }

  // Tenta reconectar ao servidor se a conexão foi perdida
  if (!client.connected()) {
    connectToServer();
  }

  // Envia mensagem ao servidor e fecha a conexão
  if (client.connected()) {
    String texto = "Olá, Servidor! Estou embaixo d'gua ";
    String resultado = texto + num;
    client.print(resultado + "\r\n");  // Usa `client.print` para não enviar uma linha extra
    Serial.println(resultado);
    num += 1;

    // Lê a resposta do servidor
    if (client.available()) {
      String response = client.readStringUntil('\r');
      Serial.print("Resposta do servidor: ");
      Serial.println(response);
    }
    // Fecha a conexão após o envio
    client.stop();
  }
  delay(2000); // Aguarda antes de enviar a próxima mensagem
}

// Função para conectar ao servidor
void connectToServer() {
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Conectado ao servidor!");
  } else {
    Serial.println("Falha na conexão ao servidor.");
  }
}
