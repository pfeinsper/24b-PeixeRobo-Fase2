#include <WiFi.h>
//server
// Defina o SSID e a senha da rede Wi-Fi do hotspot
const char* ssid = "teste_wifi";
const char* password = "vambora123";

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
  
  // Inicia o servidor
  wifiServer.begin();
  Serial.println("Servidor iniciado.");
  Serial.print("IP do servidor: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = wifiServer.available(); // Espera por clientes

  if (client) {
    Serial.println("Cliente conectado.");

    // Espera até que o cliente envie dados
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.print("Requisição recebida: ");
        Serial.println(request);
        
        // Resposta do servidor
        client.println("OK - Estou tranquilo fora d'gua");
        client.println("Content-type:text/plain");
        client.println();
        client.println("ESP32 Server: Mensagem recebida com sucesso!");
        client.println();
      }
    }
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}
