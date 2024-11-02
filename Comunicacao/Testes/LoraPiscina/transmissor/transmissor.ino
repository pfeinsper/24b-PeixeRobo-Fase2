// #include <LoRa.h>

// // valores da LoRa
// const int csPin = 18;      // Pino CS (chip select) para LoRa
// const int resetPin = 23;   // Pino de reset para LoRa
// const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa


// // Definição da struct que será enviada
// struct DataPacket {
//   unsigned long tempo;
//   int num_pacote;
// };

// int num_pacote = 0;

// // Função para enviar a struct DataPacket via LoRa
// void enviarPacoteLoRa(const DataPacket &data) {
//   // Converter a struct para bytes
//   byte *dataBytes = (byte *) &data;  // Ponteiro para os dados da struct
//   int dataSize = sizeof(data);  // Tamanho em bytes da struct

//   // Iniciando o envio de pacote LoRa
//   LoRa.beginPacket();
//   for (int i = 0; i < dataSize; i++) {
//     LoRa.write(dataBytes[i]);  // Envia byte a byte
//   }
//   LoRa.endPacket();

//   Serial.println("Dados enviados via LoRa!");
// }

// void setup() {
//   Serial.begin(115200); // Inicializa a comunicação serial
//   while (!Serial);      // Aguarda a inicialização da porta serial

//   Serial.println("Inicializando LoRa...");

//   // Configura os pinos SPI para LoRa
//   LoRa.setPins(csPin, resetPin, irqPin);
//   LoRa.setTxPower(20);
//   // Inicializa o módulo LoRa na frequência de 915 MHz (ajuste conforme necessário para sua região)
//   if (!LoRa.begin(915E6)) {
//     Serial.println("Erro ao iniciar LoRa.");
//     while (1);
//   }

//   Serial.println("LoRa inicializado com sucesso.");
// }

// void loop() {
//   // Preencher a struct com dados
//   DataPacket data;
//   data.num_pacote = num_pacote;
//   data.tempo = millis();

//   // Chamar a função para enviar os dados via LoRa
//   enviarPacoteLoRa(data);
//   num_pacote += 1;

//   delay(500);  // Aguarda 2 segundos antes de enviar novamente
// }

// #include <LoraHelper.h>

// LoraHelper lora(csPin, 23, 26, 915E6);
// int num_pacote = 0;

// void setup() {
//     Serial.begin(115200);
//     while (!Serial);
//     if (lora.iniciarLoRa()) {
//         Serial.println("Transmissor LoRa pronto.");
//     }
// }

// void loop() {
//     DataPacket data = { millis(), num_pacote };
//     lora.enviarPacote(data);
//     num_pacote++;
//     delay(500);
// }

////////////////////////////////////////////////////////////////////

// #include <LoraHelper.h>

// // Pinos Lora TTGO T-Beam
// const int csPin = 18;      // Pino CS (chip select) para LoRa
// const int resetPin = 23;   // Pino de reset para LoRa
// const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa
// // Frequência escolhida
// const int freq = 915E6;

// LoraHelper lora(csPin, resetPin, irqPin, freq);
// int num_pacote = 0;

// void setup() {
//     Serial.begin(115200);
//     while (!Serial);
//     if (lora.iniciarLoRa()) {
//         Serial.println("Transmissor LoRa pronto.");
//     }
// }

// void loop() {
//     DataPacket data = { millis(), num_pacote };
//     lora.enviarPacote(data);
//     num_pacote++;
//     delay(500);
// }
////////////////////////////////////////////////////////////////////////////////////////////
#include <LoraHelper.h>

LoraHelper lora(18, 23, 26, 915E6);
float num_pacote = 0.0;

void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (lora.iniciarLoRa()) {
        Serial.println("Transmissor LoRa pronto.");
    }
}

void loop() {
    Missao missao = { millis(), num_pacote };
    Pacote pacote = {1, missao};
    lora.enviarPacote(pacote);
    num_pacote+=0.2;
    delay(500);
}
