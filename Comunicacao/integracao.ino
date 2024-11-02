
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";

// Inicia o servidor na porta 80
WebServer server(80);

// Função para exibir o formulário HTML
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

// Função para processar o JSON recebido via POST
void handlePost() {
    // Verifica se os dados do POST foram enviados
    if (server.hasArg("plain")) {
        String jsonPayload = server.arg("plain");  // Captura o conteúdo do POST
        Serial.print("JSON recebido: ");
        Serial.println(jsonPayload);

        // Envia uma resposta de confirmação ao cliente
        server.send(200, "application/json", "{\"status\":\"sucesso\", \"mensagem\":\"JSON recebido\"}");
    } else {
        // Responde com erro se não houver dados
        server.send(400, "application/json", "{\"status\":\"erro\", \"mensagem\":\"Nenhum dado recebido\"}");
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    // Conecta ao WiFi
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao WiFi...");
    }
    Serial.println("Conectado ao WiFi!");
    Serial.print("IP da ESP32: ");
    Serial.println(WiFi.localIP());

    // Define as rotas
    server.on("/", handleForm);           // Rota para o formulário
    server.on("/data", HTTP_POST, handlePost);  // Rota para receber JSON via POST

    // Inicia o servidor
    server.begin();
    Serial.println("Servidor iniciado");
}

void loop() {
    // Mantém o servidor em funcionamento
    server.handleClient();
}
