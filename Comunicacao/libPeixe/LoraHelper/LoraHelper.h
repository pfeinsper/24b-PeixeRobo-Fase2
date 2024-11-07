
// LoraHelper.h
#ifndef LORAHELPER_H
#define LORAHELPER_H

#include <Arduino.h>
#include <LoRa.h>
#include <ArduinoJson.h>
#include <vector>


struct Missao {
    unsigned long tempo;
    float profundidade;
};
struct ListaMissao {
    std::vector<Missao> missoes;
};

struct Pacote{
    int comando;
    ListaMissao listaMissao;
};

struct DadosArduino {
    unsigned long tempo;
    int estado;
    float sensores[5];
};

// AVALIAR ENVIO DE MAIS parametros para uma missão

class LoraHelper {
public:
    LoraHelper(int csPin, int resetPin, int irqPin, long frequency);

    // Função para inicializar o módulo LoRa
    bool iniciarLoRa();

    // Função para enviar a struct DataPacket via LoRa
    void enviarPacote(const Pacote &data);

    // Função para ler e reconstruir um pacote LoRa
    bool lerPacote(Pacote &receivedData);

    void sinalizarFimMissao();
    void receberFimMissao();
    void enviarDadosArduino(const std::vector<DadosArduino>& dados);

private:
    int csPin;
    int resetPin;
    int irqPin;
    long frequency;
};

#endif // LORAHELPER_H
