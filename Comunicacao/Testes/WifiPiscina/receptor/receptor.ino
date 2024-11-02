#include <WiFi.h>
//server
// Defina o SSID e a senha da rede Wi-Fi do hotspot
const char* ssid = "teste_wifi";
const char* password = "vambora123";
int num = 0;
WiFiServer wifiServer(80); // Porta 80 para HTTP
int lista[1000];

void setup() {
  Serial.begin(115200);
  
  // Conecte-se ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando-se à rede Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  
  // Mostra a intensidade do sinal (RSSI)
  Serial.print("Intensidade do sinal Wi-Fi (RSSI): ");
  Serial.println(WiFi.RSSI());
  
  // Inicia o servidor
  wifiServer.begin();
  Serial.println("Servidor iniciado.");
  Serial.print("IP do servidor: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = wifiServer.available();

  if (client) {
    Serial.println("Cliente conectado.");

    // Lê os dados recebidos do cliente
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\n'); // Ler até a nova linha enviada pelo cliente
        request.trim();  // Remove espaços extras ou linhas vazias
        if (request.length() > 0) {
          Serial.print("Requisição recebida: ");
          Serial.println(request);

          // Responde ao cliente
          client.println("OK - Estou tranquilo fora d'gua");
          client.println("Content-type:text/plain");
          client.println("ESP32 Server: Mensagem recebida com sucesso!");

          // Exibe o RSSI e contadores
          Serial.print(millis());
          Serial.print(",");
          Serial.print(WiFi.RSSI());
          Serial.print(",");
          Serial.print(1);
          Serial.print(",");
          Serial.println(num);
          num += 1;
        }
      } else {
        // Fecha a conexão se o cliente não estiver mais enviando dados
        client.stop();
        Serial.println("Cliente desconectado.");
        break;
      }
    }
  }
}
