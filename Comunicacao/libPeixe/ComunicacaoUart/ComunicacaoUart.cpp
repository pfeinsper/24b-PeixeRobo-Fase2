// ComunicacaoUart.cpp

#include "ComunicacaoUart.h"

// Construtor da classe ComunicacaoUart
ComunicacaoUart::ComunicacaoUart(HardwareSerial& serialPort, uint32_t baudRate) 
    : serial(serialPort) {
    serial.begin(baudRate);
}

// Função para calcular o checksum do pacote
uint8_t ComunicacaoUart::calculateChecksum(uint8_t* data, size_t length) {
    uint8_t checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += data[i];
    }
    return checksum % 256;
}

// Função para enviar o pacote pela UART
void ComunicacaoUart::sendPacket(uint8_t dataType, void* value, size_t dataSize) {
    uint8_t packet[3 + dataSize];

    // Montando o cabeçalho do pacote
    packet[0] = dataType;
    packet[1] = dataSize;

    // Copiando os dados para o pacote
    memcpy(&packet[2], value, dataSize);

    // Calculando e adicionando o checksum
    uint8_t checksum = calculateChecksum(packet, 2 + dataSize);
    packet[2 + dataSize] = checksum;

    // Enviando o pacote pela UART
    serial.write(packet, 3 + dataSize);
}

// Função para enviar dados dos sensores
void ComunicacaoUart::enviaDadosSensores(float dados[6]) {
    uint8_t packet[16 + sizeof(float) * 6];

    packet[0] = 6; // Número de campos (6 dados)

    size_t index = 1;
    for (int i = 0; i < 6; i++) {
        packet[index++] = PACKET_TYPE_FLOAT;
        packet[index++] = sizeof(float);

        memcpy(&packet[index], &dados[i], sizeof(float));
        index += sizeof(float);
    }

    uint8_t checksum = calculateChecksum(packet, index);
    packet[index] = checksum;

    serial.write(packet, index + 1);
}

// Função para receber dados dos sensores
bool ComunicacaoUart::recebeDadosSensores(float dados[6]) {
    if (serial.available() < 2) {
        return false;
    }

    uint8_t numFields = serial.read();
    if (numFields != 6) {
        Serial.println("Erro: Pacote não possui 6 campos.");
        return false;
    }

    size_t packetSize = 2 + numFields * (2 + sizeof(float)) + 1;

    if (serial.available() < packetSize - 1) {
        return false;
    }

    uint8_t data[packetSize - 1];
    serial.readBytes(data, packetSize - 1);

    uint8_t receivedChecksum = serial.read();
    uint8_t calculatedChecksum = calculateChecksum(&numFields, 1) + calculateChecksum(data, packetSize - 1);

    if (calculatedChecksum != receivedChecksum) {
        Serial.println("Erro de checksum!");
        return false;
    }

    size_t index = 0;
    for (uint8_t i = 0; i < numFields; i++) {
        uint8_t dataType = data[index++];
        uint8_t dataSize = data[index++];

        if (dataType == PACKET_TYPE_FLOAT && dataSize == sizeof(float)) {
            float floatValue;
            memcpy(&floatValue, &data[index], sizeof(float));
            dados[i] = floatValue;
            index += dataSize;
        } else {
            Serial.println("Tipo de dado desconhecido ou comprimento incorreto.");
            return false;
        }
    }

    return true;
}

bool ComunicacaoUart::recebeDadosArduino(unsigned long& tempo, int& estado, float dados[5]) {
    const size_t packetSize = 29; // Tamanho total do pacote (4 + 4 + 20 + 1)
    
    // Verifica se o número mínimo de bytes está disponível
    if (serial.available() < packetSize) {
        return false;
    }

    uint8_t data[packetSize - 1]; // Pacote sem o checksum
    serial.readBytes(data, packetSize - 1);

    uint8_t receivedChecksum = serial.read();  // Último byte é o checksum
    uint8_t calculatedChecksum = calculateChecksum(data, packetSize - 1);

    if (calculatedChecksum != receivedChecksum) {
        Serial.println("Erro de checksum!");
        return false;
    }

    // Extrai os dados do pacote
    size_t index = 0;

    // 1. Extrai o tempo (unsigned long, 4 bytes)
    memcpy(&tempo, &data[index], sizeof(unsigned long));
    index += sizeof(unsigned long);

    // 2. Extrai o estado da missão (int, 4 bytes)
    memcpy(&estado, &data[index], sizeof(int));
    index += sizeof(int);

    // 3. Extrai os dados dos sensores (5 floats, 4 bytes cada)
    for (uint8_t i = 0; i < 5; i++) {
        memcpy(&dados[i], &data[index], sizeof(float));
        index += sizeof(float);
    }

    Serial.println("Dados recebidos com sucesso:");
    Serial.print("Tempo: "); Serial.println(tempo);
    Serial.print("Estado da Missão: "); Serial.println(estado);
    for (uint8_t i = 0; i < 5; i++) {
        Serial.print("Sensor "); Serial.print(i + 1); Serial.print(": ");
        Serial.println(dados[i]);
    }

    return true;
}

DadosArduino ComunicacaoUart::recebeDadosSensores() {
    const size_t packetSize = 29; // Tamanho total do pacote (4 + 4 + 20 + 1)

    // Verifica se o número mínimo de bytes está disponível
    if (serial.available() < packetSize) {
        return std::nullopt;
    }

    uint8_t data[packetSize - 1]; // Pacote sem o checksum
    serial.readBytes(data, packetSize - 1);

    uint8_t receivedChecksum = serial.read();  // Último byte é o checksum
    uint8_t calculatedChecksum = calculateChecksum(data, packetSize - 1);

    if (calculatedChecksum != receivedChecksum) {
        Serial.println("Erro de checksum!");
        return std::nullopt;
    }

    // Preenche o objeto PacoteDados
    PacoteDados pacote;
    size_t index = 0;

    // 1. Extrai o tempo (unsigned long, 4 bytes)
    memcpy(&pacote.tempo, &data[index], sizeof(unsigned long));
    index += sizeof(unsigned long);

    // 2. Extrai o estado da missão (int, 4 bytes)
    memcpy(&pacote.estado, &data[index], sizeof(int));
    index += sizeof(int);

    // 3. Extrai os dados dos sensores (5 floats, 4 bytes cada)
    for (uint8_t i = 0; i < 5; i++) {
        memcpy(&pacote.sensores[i], &data[index], sizeof(float));
        index += sizeof(float);
    }

    Serial.println("Dados recebidos com sucesso:");
    Serial.print("Tempo: "); Serial.println(pacote.tempo);
    Serial.print("Estado da Missão: "); Serial.println(pacote.estado);
    for (uint8_t i = 0; i < 5; i++) {
        Serial.print("Sensor "); Serial.print(i + 1); Serial.print(": ");
        Serial.println(pacote.sensores[i]);
    }

    return pacote; // Retorna o pacote preenchido
}


// Função para confirmar o recebimento do pacote
void ComunicacaoUart::confirmarRecebimento() {
    uint8_t ackPacket[2];
    ackPacket[0] = PACKET_TYPE_ACK;
    ackPacket[1] = calculateChecksum(ackPacket, 1);
    serial.write(ackPacket, 2);
}

// Função para receber a confirmação do Arduino
bool ComunicacaoUart::recebeConfirmacao() {

    unsigned long start_time = millis();

    // Espera por um pacote de confirmação com timeout de 5 segundos
    while (millis() - start_time < 5000) {  
        if (serial.available() > 0) {
            uint8_t dataType = serial.read();  // Lê o tipo de pacote

            // Verifica se o tipo é um pacote de confirmação (ACK)
            if (dataType == PACKET_TYPE_ACK) {
                Serial.println("Pacote de confirmação (ACK) recebido do Arduino.");
                return true;
            } else {
                // Descartar dados incorretos (não ACK)
                Serial.println("Pacote recebido não é um ACK.");
            }
        }
    }

    // Timeout alcançado sem receber o ACK
    Serial.println("Timeout: confirmação não recebida.");
    return false;
}


void ComunicacaoUart::enviarListaMissoes(const ListaMissao &listaMissoes) {
    // Estima o tamanho máximo do buffer de acordo com o número de missões na lista
    size_t packetSize = listaMissoes.missoes.size() * (2 + sizeof(float) + 2 + sizeof(float)) + 2;
    uint8_t packet[packetSize];  // Array de bytes para armazenar os pacotes
    size_t index = 0;

    // Define o número de missões
    packet[index++] = listaMissoes.missoes.size();

    // Itera sobre cada missão na lista e adiciona os dados ao pacote
    for (const auto& missao : listaMissoes.missoes) {
        // Adiciona profundidade ao pacote
        packet[index++] = PACKET_TYPE_FLOAT;
        packet[index++] = sizeof(float);
        memcpy(&packet[index], &missao.profundidade, sizeof(float));
        index += sizeof(float);

        // Adiciona tempo ao pacote
        packet[index++] = PACKET_TYPE_UNSIGNED_LONG;
        packet[index++] = sizeof(unsigned long);
        memcpy(&packet[index], &missao.tempo, sizeof(unsigned long));
        index += sizeof(unsigned long);
    }

    // Calcula e adiciona o checksum ao final do pacote
    uint8_t checksum = calculateChecksum(packet, index);
    packet[index++] = checksum;

    // Envia o pacote completo via UART
    serial.write(packet, index);

    Serial.println("Lista de missões enviada via UART.");
}
