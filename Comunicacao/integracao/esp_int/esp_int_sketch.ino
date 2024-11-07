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
//   esp_sleep_enable_timer_wakeup(10 * 1000000); // Configuração para 10s de Deep Sleep
//   enterDeepSleep();
// }

// void loop() {
//   // Etapa 1: Espera mensagem via LoRa
//   if (LoRa.parsePacket()) {
//     Pacote receivedData;
//     if (lora.lerPacote(receivedData)) {
//         // inicialmente vamos fazer o caso da primeira jornada que é enviar a missão e esperar a confirmação
//         if receivedData.comando == 1 {
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
//             dadosArduino = uart.recebeDadosArduino();
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
//     }
// //     Serial.println("Mensagem LoRa recebida: " + received_data);

// //     // Envia via Serial para o Arduino
// //     Serial.println(received_data);
    
// //     // Espera a confirmação do Arduino
// //     if (waitForArduinoConfirmation()) {
// //       // Inicia recebimento de dados via Serial do Arduino
// //       while (Serial.available()) {
// //         String incoming_data = Serial.readStringUntil('\n');
// //         data_buffer.push_back(incoming_data);

// //         // Etapa 4: Verifica o dado recebido para dar trigger
// //         if (incoming_data == "TRIGGER") {
// //           digitalWrite(TRIGGER_PIN, HIGH);
// //           trigger_activated = true;
// //           Serial.println("Trigger ativado.");
// //         }
// //       }
// //     }
// //   }

// //   // Etapa 5: Verifica status de conclusão de tarefa
// //   if (task_completed) {
// //     connectToWiFi();
// //     sendBufferedData();
// //     sendImageData();
// //     cleanupMemory();
// //     task_completed = false;
// //     enterDeepSleep();
//         }
//     }
// }


// void connectToWiFi() {
//   // Etapa 6: Conecta ao WiFi
//   WiFi.begin("SSID", "PASSWORD");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(10);
//   }
//   Serial.println("Conectado ao WiFi.");
// }

// void sendBufferedData() {
//   // Envia os dados recebidos via Serial do Arduino
//   for (String data : data_buffer) {
//     Serial.println("Enviando dado via WiFi: " + data);
//     // Aqui você implementaria o código para enviar os dados
//   }
//   data_buffer.clear();
// }

// void sendImageData() {
//   // Etapa 7: Recebimento e envio de imagem
//   Serial.println("Recebendo imagem da câmera...");
//   // Implementação para receber dados da câmera via Serial
//   // Implementação para enviar a imagem recebida via WiFi
// }

// void cleanupMemory() {
//   // 1. Limpar o buffer de dados armazenados
//   data_buffer.clear();

//   // 2. Resetar variáveis de controle e status
//   task_completed = false;
//   trigger_activated = false;
//   received_data = "";

//   // 3. Certificar que o pino de trigger está desligado
//   digitalWrite(TRIGGER_PIN, LOW);
//   Serial.println("Trigger resetado para LOW.");

//   // 4. Finalizar conexões e liberar recursos
//   if (WiFi.isConnected()) {
//     WiFi.disconnect();
//     Serial.println("Desconectado do WiFi.");
//   }
  
//   LoRa.end(); // Encerra o LoRa, se necessário.
//   Serial.println("Conexão LoRa encerrada.");

//   // 5. Limpeza de buffer Serial (opcional)
//   while (Serial.available() > 0) {
//     Serial.read(); // Limpar qualquer dado residual na Serial
//   }
  
//   Serial.println("Memória limpa e recursos redefinidos. Pronto para o próximo ciclo.");
// }


// void enterDeepSleep() {
//   Serial.println("Entrando em modo Deep Sleep.");
//   esp_deep_sleep_start();
// }
