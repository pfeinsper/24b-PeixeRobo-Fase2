// #include <LoRa.h>

// // valores da LoRa
// const int csPin = 18;      // Pino CS (chip select) para LoRa
// const int resetPin = 23;   // Pino de reset para LoRa
// const int irqPin = 26;     // Pino de IRQ (DIO0) para LoRa

// // Definindo a struct DataPacket
// struct DataPacket {
//   unsigned long tempo;
//   int num_pacote;
// };

// // Função para ler o pacote LoRa e reconstruir a struct
// bool lerPacoteLoRa(DataPacket &receivedData) {
//   // Verificar se há pacotes recebidos
//   int packetSize = LoRa.parsePacket();
//   if (packetSize > 0) {
//     Serial.println("Pacote recebido!");

//     // Criar um buffer para armazenar os bytes recebidos
//     byte receivedBytes[sizeof(DataPacket)];
//     int index = 0;

//     // Ler os bytes recebidos e armazená-los no buffer
//     while (LoRa.available() && index < sizeof(DataPacket)) {
//       receivedBytes[index] = LoRa.read();
//       index++;
//     }

//     // Verificar se o pacote está com o tamanho correto
//     if (index == sizeof(DataPacket)) {
//       // Reconstruir a struct a partir dos bytes recebidos
//       memcpy(&receivedData, receivedBytes, sizeof(receivedData));  // Copia os bytes para a struct
//       return true;  // Pacote lido com sucesso
//     } else {
//       Serial.println("Erro: Tamanho do pacote recebido incorreto.");
//       return false;
//     }
//   }
//   // Nenhum pacote recebido
//   return false;
// }

// void setup() {
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
//   // Criar uma struct para armazenar os dados recebidos
//   DataPacket receivedData;

//   // Chamar a função para ler o pacote LoRa
//   if (lerPacoteLoRa(receivedData)) {
//     // Exibir os dados recebidos
//     Serial.print(receivedData.tempo);
//     Serial.print(",");
//     Serial.print(LoRa.packetRssi());
//     Serial.print(",");
//     Serial.print(LoRa.packetSnr());
//     Serial.print(",");
//     Serial.println(receivedData.num_pacote);


//   }
// }
//////////////////////////////////////////////////////////////////////////////////////////////

// #include <LoraHelper.h>

// LoraHelper lora(18, 23, 26, 915E6);

// void setup() {
//     Serial.begin(115200);
//     while (!Serial);
//     if (lora.iniciarLoRa()) {
//         Serial.println("Receptor LoRa pronto.");
//     }
// }

// void loop() {
//     DataPacket receivedData;
//     if (lora.lerPacote(receivedData)) {
//         Serial.print("Tempo: ");
//         Serial.print(receivedData.tempo);
//         Serial.print(", RSSI: ");
//         Serial.print(LoRa.packetRssi());
//         Serial.print(", SNR: ");
//         Serial.print(LoRa.packetSnr());
//         Serial.print(", Pacote: ");
//         Serial.println(receivedData.num_pacote);
//     }
// }


////////////////////////////////////////////////////////////////////////////


#include <LoraHelper.h>

LoraHelper lora(18, 23, 26, 915E6);

void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (lora.iniciarLoRa()) {
        Serial.println("Receptor LoRa pronto.");
    }
}

void loop() {
    Pacote receivedData;
    if (lora.lerPacote(receivedData)) {
        Serial.print("Tempo: ");
        Serial.print(receivedData.missao.tempo);
        Serial.print(", Pacote: ");
        Serial.println(receivedData.missao.profundidade);
        Serial.print("Comando: ");
        Serial.println(receivedData.comando);
    }
}


