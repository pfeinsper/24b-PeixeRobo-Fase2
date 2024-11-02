#include "WiFiLora.h"

#define csPin 18       // Pino CS para LoRa
#define resetPin 23    // Pino de reset para LoRa
#define irqPin 26      // Pino de IRQ (DIO0) para LoRa

WiFiLora::WiFiLora() {
    filaLoRa = xQueueCreate(10, sizeof(char) * 256);
}
/*
void WiFiLora::iniciarWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado ao WiFi!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    configurarServidorHTTP();  // Configura o servidor HTTP após a conexão WiFi
}

void WiFiLora::configurarServidorHTTP() {
    server.on("/enviar", HTTP_POST, [this]() {
        if (server.hasArg("mensagem")) {
            String mensagemRecebida = server.arg("mensagem");
            Serial.println("Mensagem recebida via POST: " + mensagemRecebida);

            if (xQueueSend(filaLoRa, mensagemRecebida.c_str(), portMAX_DELAY) != pdPASS) {
                Serial.println("Erro: fila de mensagens cheia.");
            }
            server.send(200, "text/plain", "Mensagem recebida");
        } else {
            server.send(400, "text/plain", "Erro: nenhum dado recebido");
        }
    });

    server.begin();
    Serial.println("Servidor HTTP iniciado");
}
*/

void WiFiLora::iniciarLoRa(long frequency) {
    LoRa.setPins(csPin, resetPin, irqPin);
    if (!LoRa.begin(frequency)) {
        Serial.println("Erro ao inicializar o LoRa!");
        for(;;);
    }
    Serial.println("LoRa inicializado com sucesso");
}

void WiFiLora::enviarMensagem(String mensagem) {
    LoRa.beginPacket();
    LoRa.print(mensagem);
    LoRa.endPacket();
}

String WiFiLora::receberMensagem() {
    String mensagem = "";
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        while (LoRa.available()) {
            mensagem += (char)LoRa.read();
        }
    }
    return mensagem;
}
