// #include <LoraHelper.h>
// #include <ComunicacaoUart.h>

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
//     Serial.begin(115200);
//     while (!Serial);
//     if (lora.iniciarLoRa()) {
//         Serial.println("Receptor LoRa pronto.");
//     }

// }

// void loop(){
//     // Número de passos da missão
//     int numMissoes = Serial.parseInt();
//     Serial.print("Número de passos da missão: ");
//     Serial.println(numMissoes);

//     // Limpa a lista anterior de missões
//     listaMissoes.missoes.clear();

//     for (int i = 0; i < numMissoes; i++) {
//         Missao novaMissao;

//         // Pergunta pelo tempo da missão
//         Serial.print("Digite o tempo para a missão ");
//         Serial.print(i + 1);
//         Serial.println(":");
//         while (Serial.available() == 0) {
//             // Aguarda entrada do usuário
//         }
//         novaMissao.tempo = Serial.parseInt();
//         Serial.print("Tempo registrado: ");
//         Serial.println(novaMissao.tempo);

//         // Pergunta pela profundidade da missão
//         Serial.print("Digite a profundidade para a missão ");
//         Serial.print(i + 1);
//         Serial.println(":");
//         while (Serial.available() == 0) {
//             // Aguarda entrada do usuário
//         }
//         novaMissao.profundidade = Serial.parseFloat();
//         Serial.print("Profundidade registrada: ");
//         Serial.println(novaMissao.profundidade);

//         // Adiciona a nova missão na lista
//         listaMissoes.missoes.push_back(novaMissao);
//     }

//     pacote.clear();
//     pacote.comando = 1;
//     pacote.listaMissao = listaMissoes;
//     lora.enviarPacote(pacote);

//     // Aguarda envio de fim da missao ou erro

//     while(!lora.receberFimMissao()){
//         Serial.println("Missão finalizada com sucesso.");
//     };





// }