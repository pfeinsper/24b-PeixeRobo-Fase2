#include <LoRa.h>
#include <ClassesPeixe.h>
#include <LoraHelper.h>
#include <ComunicacaoUart.h>

// Pinos Lora TTGO T-Beam
#define csPin 18
#define resetPin 23
#define irqPin 26
// Frequencia de operação
#define freq 915E6

//ComunicacaoUart uart(Serial2, 9600, SERIAL_8N1);  // Usando Serial2 com baudRate de 9600 e configuração SERIAL_8N1


LoraHelper lora(csPin, resetPin, irqPin, freq);
// Na esp32 os outros pinos de comunicação serial são 15 e 14
// ComunicacaoUart uart(Serial2, 9600, SERIAL_8N1, 15, 14);
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
  Pacote pacote;
  
  if(lora.lerPacote(pacote)){

    lora.enviaConfirmacao(true);
    
    

  };
};
  




