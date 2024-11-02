
// LoraHelper.h
#ifndef LORAHELPER_H
#define LORAHELPER_H

#include <Arduino.h>
#include <LoRa.h>
#include <ArduinoJson.h>

struct Missao {
    unsigned long tempo;
    float profundidade;
};

struct Pacote{
    int comando;
    Missao missao;
};

class LoraHelper {
public:
    LoraHelper(int csPin, int resetPin, int irqPin, long frequency);

    // Função para inicializar o módulo LoRa
    bool iniciarLoRa();

    // Função para enviar a struct DataPacket via LoRa
    void enviarPacote(const Pacote &data);

    // Função para ler e reconstruir um pacote LoRa
    bool lerPacote(Pacote &receivedData);

private:
    int csPin;
    int resetPin;
    int irqPin;
    long frequency;
};

#endif // LORAHELPER_H
