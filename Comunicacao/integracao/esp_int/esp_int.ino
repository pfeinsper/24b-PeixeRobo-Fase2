// #include <Arduino.h>
// #include <LoraHelper.h>
// #include <ComunicacaoUart.h>

// // Pinos Lora TTGO T-Beam
// #define csPin 18
// #define resetPin 23
// #define irqPin 26
// // Frequencia de operação
// #define freq 915E6

// LoraHelper lora(csPin, resetPin, irqPin, freq);
// ComunicacaoUart uart(Serial1, 115200);

// void setup() {
//     Serial.begin(115200);
//     while (!Serial);
//     if (lora.iniciarLoRa()) {
//         Serial.println("Receptor LoRa pronto.");
//     }
// }

// void loop() {
//     Pacote receivedData;
//     if (lora.lerPacote(receivedData)) {
//       if (receivedData.comando == 1) {
//         //Serial.print("Missão recebida, transferindo dados para o sistema de controle via serial...");
//         uart.sendMissaoPacket(receivedData.missao);
//         // espera 1 segundo sem travar o código para receber a confirmação e se não receber reenvia o pacote da missão
//         bool ack = uart.recebeConfirmacao();
 
//         bool iniciaMissao = uart.recebeIniciarMissao();

        

//     }
// }
// }

// #include <LoraHelper.h>
// #include <ComunicacaoUart.h>

// // Configurações de pinos e variáveis
// #define TRIGGER_PIN 13  // Pino para o trigger

// // Pinos Lora TTGO T-Beam
// #define csPin 18
// #define resetPin 23
// #define irqPin 26
// // Frequencia de operação
// #define freq 915E6

// // Definindo objetos para comunicação
// LoraHelper lora(csPin, resetPin, irqPin, freq);
// ComunicacaoUart uart(Serial1, 115200);

// // Variáveis para status e controle
// bool task_completed = false;
// bool trigger_activated = false; 
// // Armazena os dados coletados
// std::vector<DadosArduino> dadosMissao;

// void setup() {
//   // Inicialização dos módulos e comunicação
//     Serial.begin(115200);
//     while (!Serial);
//     if (lora.iniciarLoRa()) {
//         Serial.println("Receptor LoRa pronto.");
//     }
//   // Inicialização do pino de trigger
//   pinMode(TRIGGER_PIN, OUTPUT);
//   digitalWrite(TRIGGER_PIN, LOW);
  
//   // Modo Deep Sleep
//   // esp_sleep_enable_timer_wakeup(10 * 1000000); // Configuração para 10s de Deep Sleep
//   // enterDeepSleep();
// }

// void loop() {
//   // Etapa 1: Espera mensagem via LoRa
//   Serial.println("esperando algo via lora");
//   if (LoRa.parsePacket()) {
//     Serial.println("RECEBEU ALGO VIA LORA");
//     Pacote receivedData;
//     if (lora.lerPacote(receivedData)) {
//       Serial.print
//         // inicialmente vamos fazer o caso da primeira jornada que é enviar a missão e esperar a confirmação
//         if (receivedData.comando == 1 ){
//         //Serial.print("Missão recebida, transferindo dados para o sistema de controle via serial...");
//         uart.enviarListaMissoes(receivedData.listaMissao);
//         // espera 5 segundo sem travar o código para receber a confirmação e se não receber reenvia o pacote da missão
//         bool confirmacao = uart.recebeConfirmacao();

//         while(!confirmacao){
//             uart.enviarListaMissoes(receivedData.listaMissao);  
//             confirmacao = uart.recebeConfirmacao();
//         }
//         // Missao inicia e enquanto está na missao recebe os dados do arduino de 10 em 10 segundos
//         bool fimMissao = false;
//         DadosArduino dadosArduino;
//         while(!fimMissao){
//             uart.recebeDadosArduino(dadosArduino);
//             // Guarda os dados recebidos do Arduino
//             dadosMissao.push_back(dadosArduino);
//             if(dadosArduino.estado == -1){
//                 fimMissao = true;
//             }   
//             // Fazer a lógica do trigger da câmera aqui dentro
//         }
//         // Se a missao acabou, então significa que ele voltou a superfície e podemos enviar os dados via LoRa
//         lora.enviarDadosArduino(dadosMissao);
//         lora.sinalizarFimMissao();
//       }
//     }
//   }
//   delay(2000);
// }

#include <LoRa.h>
#include <ClassesPeixe.h>
#include <LoraHelper.h>

// Pinos Lora TTGO T-Beam
#define csPin 18
#define resetPin 23
#define irqPin 26
// Frequencia de operação
#define freq 915E6

LoraHelper lora(csPin, resetPin, irqPin, freq);
void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (lora.iniciarLoRa()) {
        Serial.println("Transmissor LoRa pronto.");
    }
}

void loop() {
  // Verifique se há pacotes LoRa disponíveis
  DadosArduino dados;

  if(lora.receberDadosMissao(dados)){
    // Exibe os dados recebidos no Serial Monitor
  Serial.print("Long: ");
  Serial.println(dados.tempo);

  Serial.print("Int: ");
  Serial.println(dados.estado);

  Serial.print("Floats: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(dados.sensores[i]);
    if (i < 4) Serial.print(", ");
  }
  Serial.println();
  }

  };
  




