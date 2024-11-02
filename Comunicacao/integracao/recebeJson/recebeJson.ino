//RECEPTOOOR
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
}

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

    // Realiza ações com os parâmetros e cria uma resposta
    String response = createResponse("actionResult", "success");
    sendLoRaMessage(response); // Envia a resposta de volta
}

String createResponse(const char* key, const char* value) {
    StaticJsonDocument<200> responseDoc;
    responseDoc[key] = value;

    String responseString;
    serializeJson(responseDoc, responseString);  // Serializa a resposta em JSON
    return responseString;
}

void sendLoRaMessage(String message) {
    LoRa.beginPacket();
    LoRa.print(message);  // Envia a mensagem
    LoRa.endPacket();
    Serial.println("Resposta enviada: " + message);
}
