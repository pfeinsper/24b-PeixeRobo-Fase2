#include <ArduinoJson.h>  // Biblioteca para manipulação de JSON
#include <LoRa.h>         // Biblioteca LoRa

const int csPin = 18;      // Pino CS (chip select) para LoRa
const int resetPin = 23;   // Pino de reset para LoRa
const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa

void setup() {
    Serial.begin(115200);

    LoRa.setPins(csPin, resetPin, irqPin);

    LoRa.begin(915E6); // Inicializa LoRa na frequência 915 MHz
}

void loop() {
    // Verifica se há mensagens recebidas
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        String jsonData = "";
        while (LoRa.available()) {
            jsonData += (char)LoRa.read(); // Lê a mensagem recebida
        }
        Serial.println("Mensagem recebida: " + jsonData);
        
        // Processa a mensagem
        processMessage(jsonData);
    }

    // Envio de um pacote de exemplo
    String params = createMessage("param1", "value1", "param2", "value2");
    sendLoRaMessage(params);
    delay(10000); // Espera 10 segundos para o próximo envio
}

// Função para criar um pacote JSON
String createMessage(const char* param1, const char* value1, const char* param2, const char* value2) {
    StaticJsonDocument<200> doc;  // Documento JSON
    doc["param1"] = value1;
    doc["param2"] = value2;

    String jsonString;
    serializeJson(doc, jsonString);  // Serializa o documento JSON em string
    return jsonString;
}

// Função para enviar mensagem via LoRa
void sendLoRaMessage(String message) {
    LoRa.beginPacket();
    LoRa.print(message);  // Envia a mensagem
    LoRa.endPacket();
    Serial.println("Mensagem enviada: " + message);
}

// Função para processar a mensagem recebida
void processMessage(String jsonData) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonData); // Desserializa a mensagem JSON

    if (error) {
        Serial.println("Falha ao desserializar JSON");
        return;
    }

    // Acessa os parâmetros
    const char* param1 = doc["param1"];
    const char* param2 = doc["param2"];

    Serial.println("Parâmetros recebidos:");
    Serial.println("Param1: " + String(param1));
    Serial.println("Param2: " + String(param2));

    // Aqui você pode realizar a ação com os parâmetros recebidos
    // e criar uma resposta, se necessário.
}
