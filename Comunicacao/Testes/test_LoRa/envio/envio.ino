// #include <LoRa.h>

// const int csPin = 18;      // Pino CS (chip select) para LoRa
// const int resetPin = 23;   // Pino de reset para LoRa
// const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa
// int numero = 1;

// void setup() {
//   pinMode(2,OUTPUT);
//   pinMode(13,OUTPUT);
//   pinMode(25,OUTPUT);

//   digitalWrite(2,HIGH);
//   digitalWrite(13,HIGH);
//   digitalWrite(25,HIGH);
  
//   Serial.begin(115200); // Inicializa a comunicação serial
//   while (!Serial);      // Aguarda a inicialização da porta serial

//   Serial.println("Inicializando LoRa...");

//   // Configura os pinos SPI para LoRa
//   LoRa.setPins(csPin, resetPin, irqPin);

//   // Inicializa o módulo LoRa na frequência de 915 MHz (ajuste conforme necessário para sua região)
//   if (!LoRa.begin(915E6)) {
//     Serial.println("Erro ao iniciar LoRa.");
//     while (1);
//   }

//   Serial.println("LoRa inicializado com sucesso.");
// }

// void loop() {

//     // Inicia a mensagem LoRa
//     LoRa.beginPacket();

//     // Converte o número para um byte e o envia
//     LoRa.write((uint8_t*)&numero, sizeof(numero));

//     LoRa.endPacket();
  
//     numero = numero*2;
//     delay(2000); // Aguarda 2 segundos antes de enviar o próximo pacote
// }


#include <SPI.h>
#include <LoRa.h>

// Pinos de conexão com o módulo LoRa
const int csPin = 18;      // Pino CS (Chip Select)
const int resetPin = 23;   // Pino de Reset
const int irqPin = 26;     // Pino IRQ (DIO0)

// Definição da struct para armazenar os dados a serem enviados
struct Dados {
  unsigned long tempo;      // Tempo de execução (em milissegundos)
  int rssi;                 // RSSI (indicador de qualidade do sinal)
  float snr;                // SNR (Signal-to-Noise Ratio)
};

Dados dados;  // Instância da struct para armazenar os dados

// Função para configurar o módulo LoRa
void setupLoRa() {
  LoRa.setPins(csPin, resetPin, irqPin);  // Configura os pinos para o LoRa
  if (!LoRa.begin(915E6)) {  // Inicializa o LoRa (frequência 915 MHz para exemplo)
    Serial.println("Erro ao inicializar o LoRa.");
    while (1);  // Fica em loop infinito em caso de erro
  }
  Serial.println("LoRa iniciado com sucesso.");
}

// Função para enviar dados via LoRa
void enviarDadosLoRa(Dados *dados) {
  LoRa.beginPacket();            // Inicia o pacote de dados
  LoRa.write((uint8_t*)dados, sizeof(Dados));  // Envia os dados serializados
  LoRa.endPacket();              // Finaliza o envio
  Serial.println("Dados enviados.");
}

void setup() {
  Serial.begin(9600);  // Inicia a comunicação serial
  setupLoRa();          // Configura o módulo LoRa

  Serial.println("Aguardando entrada do usuário para enviar dados...");
}

void loop() {
  // Verifica se há dados disponíveis para leitura no Serial
  if (Serial.available() > 0) {
    // Espera o usuário inserir os dados
    Serial.print("Digite o tempo (ms): ");
    while (Serial.available() == 0);  // Espera o usuário inserir os dados
    dados.tempo = Serial.parseInt();  // Lê o tempo do serial

    Serial.print("Digite o RSSI (dBm): ");
    while (Serial.available() == 0);
    dados.rssi = Serial.parseInt();  // Lê o RSSI do serial

    Serial.print("Digite o SNR: ");
    while (Serial.available() == 0);
    dados.snr = Serial.parseFloat();  // Lê o SNR do serial

    // Envia os dados coletados via LoRa
    enviarDadosLoRa(&dados);
  }

  delay(1000);  // Aguarda 1 segundo antes de verificar novamente
}
