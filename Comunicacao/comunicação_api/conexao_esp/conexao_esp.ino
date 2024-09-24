#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Credenciais da rede Wi-Fi - Tive que utilizar o hotspot do meu notebook para conectar o ESP32
const char* ssid = "DESKTOP-3FR9M9F 5743";
const char* password = "78[21gQ2";
// URL da API
const char* serverUrl = "http://10.102.28.213:5000/enviar"; // API de teste (pode substituir pela sua URL)
const char* serverUrl_GET = "http://10.102.28.213:5000/"; // API de teste (pode substituir pela sua URL)

void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial
  delay(1000);

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Conectado ao Wi-Fi.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());  // Mostra o IP do ESP32

  // Realiza a requisição GET
  realizarGET(serverUrl_GET);
}

void loop() {
  String dados = "Informação do sensor";  // Exemplo de dados que você quer enviar
  enviarParaAPI(dados);
  delay(10000);  // Aguarde 10 segundos antes de enviar novamente
}

// Função para realizar requisição GET
void realizarGET(const char* url) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    Serial.print("Conectando à API: ");
    Serial.println(url);

    http.begin(url);  // Inicializa a conexão com a URL
    int httpResponseCode = http.GET();  // Realiza a requisição GET

    if (httpResponseCode > 0) {
      // Requisição bem-sucedida
      Serial.print("Código de resposta: ");
      Serial.println(httpResponseCode);

      String response = http.getString();  // Captura a resposta da API
      Serial.println("Resposta da API:");
      Serial.println(response);  // Mostra o resultado no monitor serial
    } else {
      // Exibe o código de erro se falhar
      Serial.print("Erro na requisição GET. Código: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Fecha a conexão HTTP
  } else {
    Serial.println("Falha na conexão Wi-Fi.");
  }
}

void enviarParaAPI(String dados) {
  // Conecta ao Wi-Fi
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("Conectando ao Wi-Fi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println(" Conectado!");
  }

  // Envia dados via HTTP POST para a API
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  // Cria o objeto JSON usando ArduinoJson
  StaticJsonDocument<200> doc;
  doc["data"] = dados;

  // Serializa o JSON para uma string
  String jsonPayload;
  serializeJson(doc, jsonPayload);
  Serial.println(jsonPayload);
  int httpResponseCode = http.POST(jsonPayload);
  Serial.println(httpResponseCode);

  if (httpResponseCode > 0) {
    Serial.println("Dados enviados com sucesso!");
    Serial.println(http.getString());
  } else {
    Serial.println("Erro ao enviar dados: " + String(httpResponseCode));
  }

  http.end();
}