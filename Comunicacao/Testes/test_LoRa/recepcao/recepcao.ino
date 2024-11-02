//#include <SPI.h>
#include <LoRa.h>

// valores da lorona
const int csPin = 18;      // Pino CS (chip select) para LoRa
const int resetPin = 23;   // Pino de reset para LoRa
const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa

// Definição da struct para armazenar os dados recebidos
struct DadosRecebidos {
  unsigned long tempo;       // Tempo de execução (millis) do transmissor
  int rssi;                  // RSSI do pacote
  float snr;                 // SNR do pacote
};

// Função para receber e desserializar os dados
bool receberDadosLoRa(DadosRecebidos *dados) {
  int tamanhoPacote = LoRa.parsePacket();
  
  if (tamanhoPacote == sizeof(DadosRecebidos)) {
    // Lê os bytes do pacote e copia para a struct
    LoRa.readBytes((uint8_t*)dados, tamanhoPacote);
    return true;  // Dados recebidos com sucesso
  }
  
  return false;  // Nenhum dado válido recebido
}

void setup() {
    DadosRecebidos dados;
  // Verifica se os dados foram recebidos
  if (receberDadosLoRa(&dados)) {
    // Exibe os dados recebidos no monitor serial
    Serial.println("Dados recebidos:");
    Serial.printf("Tempo: %lu ms\n", dados.tempo);
    Serial.printf("RSSI: %d dBm\n", dados.rssi);
    Serial.printf("SNR: %.2f\n", dados.snr);
  }

  delay(1000); // Verifica os dados recebidos a cada 1 segundo
}
