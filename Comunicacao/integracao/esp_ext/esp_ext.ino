#include <LoRa.h>
#include <LoraHelper.h>
#include <ArduinoJson.h>
#include <WiFi.h>

// Configurações Wi-Fi
const char* ssid = "teste_wifi";
const char* password = "vambora123";

// Configurações de IP fixo
// IPAddress localIP(192, 168, 1, 100);  // IP fixo da ESP32
// IPAddress gateway(192, 168, 137, 1);   // Gateway (geralmente o roteador) ou seu hotspot
// IPAddress subnet(255, 255, 255, 0);  // Máscara de sub-rede


// Pinos Lora TTGO T-Beam
#define csPin 18
#define resetPin 23
#define irqPin 26
// Frequencia de operação
#define freq 915E6

// Inicialização de objetos
WiFiServer wifiServer(80);

LoraHelper lora(csPin, resetPin, irqPin, freq);
Pacote pacote;

void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (lora.iniciarLoRa()) {
        Serial.println("Transmissor LoRa pronto.");
    }
    // if (!WiFi.config()) {
    //     Serial.println("Falha ao configurar IP fixo.");
    //   }

    // Conecta ao Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Conectando ao Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nWi-Fi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
   // Configura a rota POST para receber JSON
     // Iniciar o servidor
  wifiServer.begin();
  Serial.println("Servidor iniciado.");

}

void loop() {

    // Verifique se há clientes conectados
  WiFiClient client = wifiServer.available();

   if (client) {
    Serial.println("Cliente conectado.");

    String request = "";
    bool isPost = false;
    int contentLength = 0;

    // Lê a requisição HTTP
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;

        // Verifica se o método é POST
        if (request.startsWith("POST")) {
          isPost = true;
        }

        // Detecta o fim dos cabeçalhos HTTP
        if (request.endsWith("\r\n\r\n")) {
          // Processa o cabeçalho Content-Length para determinar o tamanho do corpo
          int index = request.indexOf("Content-Length: ");
          if (index != -1) {
            contentLength = request.substring(index + 16).toInt();
            Serial.printf("Content-Length detectado: %d\n", contentLength);
          }
          break;
        }
      }
    }

    // Processa o corpo da requisição (se for POST)
    String body = "";
    if (isPost && contentLength > 0) {
      while (body.length() < contentLength) {
        if (client.available()) {
          char c = client.read();
          body += c;
        }
      }
      Serial.println("Corpo da requisição recebido:");
      Serial.println(body);
    }
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, body);
    if (error) {
        Serial.print("Erro ao processar JSON: ");
    }

    // Extraindo valores do JSON
    float profundidade = doc["profundidade"];  // Se o valor for um número decimal
    unsigned long tempo = doc["tempo"];  // Se o valor for um número inteiro

    Serial.println("Dados recebidos via POST:");
    Serial.printf("tempo (convertido): %lu\n", tempo);
    Serial.printf("profundidade (convertido): %.2f\n", profundidade);
    // unsigned long tempo_par = strtoul(tempo, NULL, 10);
    // float profund_par = strtof(profundidade, NULL);
    // Enviar uma resposta HTTP ao cliente
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println(); // Linha em branco para separar cabeçalhos do corpo
    client.println("{\"status\":\"sucesso\",\"mensagem\":\"Requisição POST recebida!\"}");

    // Fecha a conexão
    client.stop();
    Pacote pacote;
    pacote = lora.preencherPacote(tempo, profundidade,0);
    unsigned long tempoAnterior = 0;  // Variável para armazenar o último tempo de envio
    unsigned long intervalo = 2000;    // Intervalo de 2 segundo (2000 ms)
    // reenvia de 2 em 2 segundos se não receber confirmação
    while(!lora.recebeConfirmacao()) {
        unsigned long tempoAtual = millis();  // Obtém o tempo atual
        // Verifica passou 2 segundos desde o ultimo envio
        if (tempoAtual - tempoAnterior >= intervalo) {
            lora.enviarPacote(pacote);  // Envia o pacote
            tempoAnterior = tempoAtual;  // Atualiza o tempo do último envio
        }
    }

    // DadosArduino listaDados[300];  // Lista para armazenar até 500 dados
    // int totalDados = 0;  // Contador de dados recebidos
    // bool resultado = lora.receberDadosMissao(listaDados, totalDados, tempo);

    Serial.println("Confirmação recebida, tudo entregue");


  }
  
  // lora.preencherPacote(pacote);

  // //lora.enviarDadosMissao(longValue, intValue, floatValues, 5);
  // lora.enviarPacote(pacote);

  // delay(5000);  // Aguarde 5 segundos antes de enviar novamente
}
