#include "WebHandlers.h"
#include <Arduino.h>  // Inclua isso para Serial.print

// Implementação da função de exibir o formulário
void handleForm() {
    String html = "<!DOCTYPE html><html><head><title>Enviar JSON</title></head><body>";
    html += "<h2>Formulário para Enviar JSON</h2>";
    html += "<form action=\"/data\" method=\"POST\">";
    html += "<label for=\"name\">Nome:</label><br>";
    html += "<input type=\"text\" id=\"name\" name=\"name\"><br><br>";
    html += "<label for=\"age\">Idade:</label><br>";
    html += "<input type=\"text\" id=\"age\" name=\"age\"><br><br>";
    html += "<input type=\"submit\" value=\"Enviar\">";
    html += "</form>";
    html += "</body></html>";

    server.send(200, "text/html", html);  // Envia o formulário HTML
}

// Implementação da função para processar o JSON recebido
void handlePost() {
    if (server.hasArg("plain")) {
        String jsonPayload = server.arg("plain");  // Captura o conteúdo do POST
        Serial.print("JSON recebido: ");
        Serial.println(jsonPayload);

        // Envia uma resposta de confirmação ao cliente
        server.send(200, "application/json", "{\"status\":\"sucesso\", \"mensagem\":\"JSON recebido\"}");
    } else {
        server.send(400, "application/json", "{\"status\":\"erro\", \"mensagem\":\"Nenhum dado recebido\"}");
    }
}
