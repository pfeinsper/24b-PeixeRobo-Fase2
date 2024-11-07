#include "LoraHelper.h"

// Construtor da classe LoraHelper
LoraHelper::LoraHelper(int csPin, int resetPin, int irqPin, long frequency)
    : csPin(csPin), resetPin(resetPin), irqPin(irqPin), frequency(frequency) {}


// Função para inicializar o módulo LoRa
bool LoraHelper::iniciarLoRa() {
    LoRa.setPins(csPin, resetPin, irqPin);
    if (!LoRa.begin(frequency)) {
        Serial.println("Falha ao inicializar o módulo LoRa!");
        return false;
    }
    Serial.println("Módulo LoRa inicializado com sucesso!");
    return true;
}

// Função para enviar o Pacote como JSON via LoRa
void LoraHelper::enviarPacote(const Pacote &data) {
    // Cria um objeto JSON e preenche com os dados da struct
    StaticJsonDocument<256> doc;
    doc["comando"] = data.comando;
    doc["missao"]["profundidade"] = data.missao.profundidade;
    doc["missao"]["tempo"] = data.missao.tempo;

    // Serializa o JSON para uma string
    String jsonStr;
    serializeJson(doc, jsonStr);

    // Envia o JSON via LoRa
    LoRa.beginPacket();
    LoRa.print(jsonStr);  // Escreve a string JSON diretamente no pacote
    LoRa.endPacket();

    Serial.println("Pacote JSON enviado via LoRa: " + jsonStr);
}

// Função para ler o JSON via LoRa e reconstruir a struct Pacote
bool LoraHelper::lerPacote(Pacote &receivedData) {
    int packetSize = LoRa.parsePacket();
    if (packetSize > 0) {
        String receivedJson;

        // Ler todos os bytes disponíveis e formar a string JSON
        while (LoRa.available()) {
            receivedJson += (char)LoRa.read();
        }

        // Desserializar a string JSON para o objeto Pacote
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, receivedJson);
        if (error) {
            Serial.print("Erro ao desserializar JSON: ");
            Serial.println(error.c_str());
            return false;
        }

        // Preenche a struct Pacote com os dados do JSON
        receivedData.comando = doc["comando"];
        receivedData.missao.profundidade = doc["missao"]["profundidade"];
        receivedData.missao.tempo = doc["missao"]["tempo"];

        Serial.println("Pacote JSON recebido e desserializado com sucesso.");
        return true;
    }
    return false;  // Nenhum pacote recebido
}



void LoraHelper::sinalizarFimMissao() {
    LoRa.beginPacket();
    LoRa.write(0xFF);  // Envia um byte de sinalização
    LoRa.endPacket();

    Serial.println("Sinal de fim de missão enviado via LoRa.");
}

void LoraHelper::receberFimMissao() {
    int packetSize = LoRa.parsePacket();
    if (packetSize > 0) {
        uint8_t receivedByte = LoRa.read();
        if (receivedByte == 0xFF) {
            Serial.println("Recebido sinal de fim de missão via LoRa.");
        } else {
            Serial.println("Byte inválido recebido.");
        }
        return true;
    }
    return false;  // Nenhum pacote recebido
}