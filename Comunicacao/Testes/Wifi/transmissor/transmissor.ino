#include <WiFi.h>

// Defina o SSID e a senha da rede Wi-Fi do hotspot
const char* ssid = "teste_wifi";
const char* password = "vambora123";

// Defina o IP do servidor ESP32 (ajuste conforme o endereço IP obtido)
const char* serverIP = "192.168.137.141"; // Exemplo: "192.168.137.141"
const int serverPort = 80; // Porta do servidor

int num = 1;

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
}

void loop() {
  WiFiClient client;

  // Tenta se conectar ao servidor
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Conectado ao servidor!");

    // Concatena mensagem e envia ao servidor
    String texto = "Olá, Servidor! Estou embaixo d'gua ";
    String resultado = texto + num;
    client.println(resultado);
      num = num + 1;

    // Espera por uma resposta do servidor
    if (client.available()) { 
      String response = client.readStringUntil('\r');
      Serial.print("Resposta do servidor: ");
      Serial.println(response);
    }

    // Fecha a conexão
    client.stop();
    Serial.println("Conexão encerrada.");
  } else {
    Serial.println("Falha na conexão ao servidor.");
  }

  delay(2000); // Aguarda 5 segundos antes de tentar enviar a próxima mensagem
}
