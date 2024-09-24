#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


const int csPin = 18;      // Pino CS (chip select) para LoRa
const int resetPin = 23;   // Pino de reset para LoRa
const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa


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
    Serial.print(ssid);


    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Conectado ao Wi-Fi.");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());  // Mostra o IP do ESP32

    // Inicializando o LoRa
    Serial.println("Inicializando LoRa...");

    // Configura os pinos SPI para LoRa
    LoRa.setPins(csPin, resetPin, irqPin);

    // Inicializa o módulo LoRa na frequência de 915 MHz (ajuste conforme necessário para sua região)
    if (!LoRa.begin(915E6)) {
        Serial.println("Erro ao iniciar LoRa.");
        while (1);
    }

    Serial.println("LoRa inicializado com sucesso.");

}


void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
        // Lê o pacote recebido
        byte message[packetSize];
        int i = 0;
        while (LoRa.available()) {
            message[i] = LoRa.read();
            i++;
        }
        Serial.print("Pacote recebido: ");
        for (int j = 0; j < packetSize; j++) {
            Serial.print(message[j]);
            analogWrite(pinList[j], message[j]);
            Serial.print(" ");
        }
    }
}


// Função para adicionar no json
void adicionarJson(JsonObject& json, const char* key, const char* value) {
    json[key] = value;
}
// função que retorna um novo json
String criarJson(String dados) {
    // Cria um objeto JSON
    StaticJsonDocument<200> doc;
    JsonObject json = doc.to<JsonObject>();

    // Adiciona os dados ao JSON
    adicionarJson(json, "dados", dados.c_str());

    // Converte o JSON para uma string
    String jsonStr;
    serializeJson(json, jsonStr);

    return jsonStr;
}