// ComunicacaoUart.h

#ifndef COMUNICACAO_UART_H
#define COMUNICACAO_UART_H

#include <Arduino.h>

// Definições de tipo de dado para os pacotes
#define PACKET_TYPE_INT32   0x01  // int32_t
#define PACKET_TYPE_FLOAT   0x02  // float
#define PACKET_TYPE_INT16   0x03  // int16_t
#define PACKET_TYPE_DOUBLE  0x04  // double
#define PACKET_TYPE_UINT32  0x05  // uint32_t
#define PACKET_TYPE_UINT16  0x06  // uint16_t
#define PACKET_TYPE_UINT8   0x07  // uint8_t
#define PACKET_TYPE_INT8    0x08  // int8_t
#define PACKET_TYPE_CHAR    0x09  // char
#define PACKET_TYPE_BOOL    0x0A  // bool
#define PACKET_TYPE_STRING  0x0B  // string (tamanho variável)
#define PACKET_TYPE_ACK     0xFF  // ACK (confirmação de recebimento)

struct DadosArduino {
    unsigned long tempo;
    int estado;
    float sensores[5];
};

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



class ComunicacaoUart {
public:
    ComunicacaoUart(HardwareSerial& serialPort, uint32_t baudRate);

    void sendPacket(uint8_t dataType, void* value, size_t dataSize);
    bool readPacket();
    void confirmarRecebimento();

    // Funções para enviar e receber dados dos sensores
    void enviaDadosSensores(float dados[6]);
    bool recebeDadosSensores(float dados[6]);
    bool recebeConfirmacao();
    DadosArduino recebeDadosArduino();

private:
    HardwareSerial& serial;
    uint8_t calculateChecksum(uint8_t* data, size_t length);
};

#endif
