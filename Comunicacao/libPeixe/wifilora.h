#ifndef WIFILORA_H
#define WIFILORA_H

#include <Arduino.h>
#include <LoRa.h>
// #include <WiFi.h>
// #include <WebServer.h>  // Biblioteca WebServer para servidor HTTP básico

class WiFiLora {
public:
    WiFiLora();  // Construtor simples

    // Funções de inicialização para WiFi e LoRa
    // void iniciarWiFi(const char* ssid, const char* password);
    void iniciarLoRa(long frequency);

    // Funções para envio e recebimento de mensagens LoRa
    void enviarMensagem(String mensagem);
    String receberMensagem();

private:
    // const char* ssid;
    // const char* password;
    long frequency;

    // WebServer server = WebServer(80);  // Servidor HTTP básico
    QueueHandle_t filaLoRa;  // Fila para mensagens LoRa

    // Funções de configuração para WiFi, servidor HTTP e LoRa
    // void configurarWiFi();
    // void configurarServidorHTTP();

    // Tarefas assíncronas para WiFi e LoRa
    // static void taskWiFi(void* param);
    static void taskLoRa(void* param);
};

#endif
