// //#include <SPI.h>
// #include <LoRa.h>

// // valores da lorona
// const int csPin = 18;      // Pino CS (chip select) para LoRa
// const int resetPin = 23;   // Pino de reset para LoRa
// const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa

// // Definição da struct para armazenar os dados recebidos
// struct DadosRecebidos {
//   unsigned long tempo;       // Tempo de execução (millis) do transmissor
//   int rssi;                  // RSSI do pacote
//   float snr;                 // SNR do pacote
// };

// // Função para receber e desserializar os dados
// bool receberDadosLoRa(DadosRecebidos *dados) {
//   int tamanhoPacote = LoRa.parsePacket();
  
//   if (tamanhoPacote == sizeof(DadosRecebidos)) {
//     // Lê os bytes do pacote e copia para a struct
//     LoRa.readBytes((uint8_t*)dados, tamanhoPacote);
//     return true;  // Dados recebidos com sucesso
//   }
  
//   return false;  // Nenhum dado válido recebido
// }

// void setup() {
//     DadosRecebidos dados;
//   // Verifica se os dados foram recebidos
//   if (receberDadosLoRa(&dados)) {
//     // Exibe os dados recebidos no monitor serial
//     Serial.println("Dados recebidos:");
//     Serial.printf("Tempo: %lu ms\n", dados.tempo);
//     Serial.printf("RSSI: %d dBm\n", dados.rssi);
//     Serial.printf("SNR: %.2f\n", dados.snr);
//   }

//   delay(1000); // Verifica os dados recebidos a cada 1 segundo
// }

// void loop(){

// }

#include <SPI.h>
#include <LoRa.h>

// Pinos de conexão com o módulo LoRa
const int csPin = 18;      // Pino CS (Chip Select)
const int resetPin = 23;   // Pino de Reset
const int irqPin = 26;     // Pino IRQ (DIO0)

// Definição da struct para armazenar os dados recebidos
struct DadosRecebidos {
  unsigned long tempo;       // Tempo de execução (millis) do transmissor
  int rssi;                  // RSSI do pacote
  float snr;                 // SNR do pacote
};

// Função para configurar o módulo LoRa
void setupLoRa() {
  LoRa.setPins(csPin, resetPin, irqPin);  // Configura os pinos para o LoRa
  if (!LoRa.begin(915E6)) {  // Inicializa o LoRa (frequência 915 MHz para exemplo)
    Serial.println("Erro ao inicializar o LoRa.");
    while (1);  // Fica em loop infinito em caso de erro
  }
  Serial.println("LoRa iniciado com sucesso.");
}

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
  Serial.begin(9600);  // Inicia a comunicação serial
  setupLoRa();          // Configura o módulo LoRa

  Serial.println("Aguardando dados via LoRa...");
}

void loop() {
  // Verifica se há dados recebidos via LoRa
  DadosRecebidos dados;
  if (receberDadosLoRa(&dados)) {
    Serial.println("Dados recebidos via LoRa:");
    Serial.printf("Tempo: %lu ms\n", dados.tempo);
    Serial.printf("RSSI: %d dBm\n", dados.rssi);
    Serial.printf("SNR: %.2f\n", dados.snr);
  }

  delay(1000);  // Aguarda 1 segundo antes de verificar novamente
}
