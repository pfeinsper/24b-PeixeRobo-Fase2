#include <LoRa.h>
#include <LoraHelper.h>
// Pinos Lora TTGO T-Beam
#define csPin 18
#define resetPin 23
#define irqPin 26
// Frequencia de operação
#define freq 915E6

LoraHelper lora(csPin, resetPin, irqPin, freq);
Pacote pacote;
void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (lora.iniciarLoRa()) {
        Serial.println("Transmissor LoRa pronto.");
    }
}

void loop() {
  
  lora.preencherPacote(pacote);

  // Defina os dados para enviar: um long, um int, e cinco floats
  unsigned long longValue = 1234567890;       // Exemplo de valor para long
  int intValue = 5;                 // Exemplo de valor para int
  float floatValues[5] = {1.2, 2.3, 3.4, 4.5, 5.6};  // Exemplo de valores para float

  //lora.enviarDadosMissao(longValue, intValue, floatValues, 5);
  lora.enviarPacote(pacote);

  delay(5000);  // Aguarde 5 segundos antes de enviar novamente
}
