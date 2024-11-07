// // #include <LoraHelper.h>

// // // Pinos Lora TTGO T-Beam
// // #define csPin 18
// // #define resetPin 23
// // #define irqPin 26
// // // Frequencia de operação
// // #define freq 915E6

// // LoraHelper lora(csPin, resetPin, irqPin, freq);
// // float num_pacote = 0.0;

// // void setup() {
// //     Serial.begin(115200);
// //     while (!Serial);
// //     if (lora.iniciarLoRa()) {
// //         Serial.println("Transmissor LoRa pronto.");
// //     }
// // }

// // void loop() {
// //     float numero = Serial.parseFloat();  // Lê o número float enviado
// //     if (numero > 0) {  // Verifica se o número é positivo
// //       Serial.print("Você digitou um número positivo: ");
// //       Serial.println(numero);
// //       Missao missao = { input, num_pacote };
// //       Pacote pacote = {1, missao};
// //       lora.enviarPacote(pacote);
// //       num_pacote+=0.2;
// //     } else {
// //       Serial.println("Número inválido. Por favor, insira um número positivo:");
// //     }

// // }


// #include <LoraHelper.h>
// #include <ComunicacaoUart.h>
// #include <ClassesPeixe.h>

// // Pinos Lora TTGO T-Beam
// #define csPin 18
// #define resetPin 23
// #define irqPin 26
// // Frequencia de operação
// #define freq 915E6

// // Definindo objetos para comunicação
// LoraHelper lora(csPin, resetPin, irqPin, freq);
// ComunicacaoUart uart(Serial1, 115200);


// ListaMissao listaMissoes;
// Pacote pacote;
// void setup() {
//   // Inicialização dos módulos e comunicação
//   Serial.begin(115200);
//   while (!Serial); // Aguarda a conexão serial

//   if (lora.iniciarLoRa()) {
//     Serial.println("Receptor LoRa pronto.");
//   }
// }

// void loop() {
//   // Espera por input do usuário via Serial para o número de passos da missão
//   int numMissoes = 0;
//   Serial.println("Digite o número de passos da missão:");

//   // Espera até que o usuário insira um número
//   while (Serial.available() == 0) {
//     // Aguarda a entrada sem bloquear o código, o microcontrolador pode executar outras tarefas aqui.
//   }

//   // Quando há input disponível, realiza a leitura
//   numMissoes = Serial.parseInt();  // Lê o número de missões
//   Serial.println("Número de passos da missão: ");
//   Serial.println(numMissoes);  // Exibe o número de missões

//   // Limpa a lista anterior de missões
//   listaMissoes.missoes.clear();

//   // Loop para pegar os dados das missões
//   for (int i = 0; i < numMissoes; i++) {
//     Missao novaMissao;

//     // Pergunta pelo tempo da missão
//     Serial.print("Digite o tempo para a missão ");
//     Serial.print(i + 1);
//     Serial.println(":");
    
//     while (Serial.available() == 0) {
//       // Aguarda entrada do usuário para o tempo
//     }
//     novaMissao.tempo = Serial.parseInt();  // Lê o tempo da missão
//     Serial.print("Tempo registrado: ");
//     Serial.println(novaMissao.tempo);  // Exibe o tempo registrado

//     // Pergunta pela profundidade da missão
//     Serial.print("Digite a profundidade para a missão ");
//     Serial.print(i + 1);
//     Serial.println(":");
    
//     while (Serial.available() == 0) {
//       // Aguarda entrada do usuário para a profundidade
//     }
//     novaMissao.profundidade = Serial.parseFloat();  // Lê a profundidade
//     Serial.print("Profundidade registrada: ");
//     Serial.println(novaMissao.profundidade);  // Exibe a profundidade registrada

//     // Adiciona a nova missão na lista
//     listaMissoes.missoes.push_back(novaMissao);
//   }

//   // Envia o pacote de missões via LoRa
//   pacote.listaMissao.missoes.clear();
//   pacote.comando = 1;
//   pacote.listaMissao = listaMissoes;
//   lora.enviarPacote(pacote);

//   // Aguarda envio de fim da missão ou erro
//   // O código de espera por confirmação pode ser adicionado aqui
//   // while(!lora.receberFimMissao()){
//   //     Serial.println("Missão finalizada com sucesso.");
//   // }
  
//   // Aguarda um curto intervalo antes de reiniciar o loop (opcional)
//   delay(1000);
// }

#include <LoRa.h>
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
  // Defina os dados para enviar: um long, um int, e cinco floats
  unsigned long longValue = 1234567890;       // Exemplo de valor para long
  int intValue = 5;                 // Exemplo de valor para int
  float floatValues[5] = {1.2, 2.3, 3.4, 4.5, 5.6};  // Exemplo de valores para float

  lora.enviarDadosMissao(longValue, intValue, floatValues, 5);

  delay(5000);  // Aguarde 5 segundos antes de enviar novamente
}
