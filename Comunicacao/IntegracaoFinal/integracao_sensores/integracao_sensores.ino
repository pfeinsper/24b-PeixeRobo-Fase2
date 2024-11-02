// Inclusão das bibliotecas necessárias.
#include <Arduino.h>               // Biblioteca principal do Arduino.
#include <arduino-timer.h>         // Biblioteca para manipulação de timers.
#include <OneWire.h>               // Biblioteca para comunicação com dispositivos OneWire.
#include <DallasTemperature.h>     // Biblioteca para trabalhar com o sensor de temperatura Dallas.

//// Declaração dos objetos e variáveis globais.
OneWire oneWire(8);                 // Objeto OneWire para comunicação com dispositivos OneWire, como sensores de temperatura.
DallasTemperature sensors(&oneWire);// Objeto para gerenciar o sensor de temperatura Dallas.

const int pH_Pin = A0;              // Pino analógico ligado ao módulo de pH.
const int turb_Pin = A1;            // Pino analógico ligado ao módulo de turbidez.
auto timer = timer_create_default(); // Cria um timer padrão para agendar tarefas periódicas.

// Configuração dos pinos para os sensores de limite e motor.
const int limitSwitchMin_Pin = 3;   // Pino para o interruptor de limite mínimo.
const int limitSwitchMax_Pin = 2;   // Pino para o interruptor de limite máximo.

// Variáveis para armazenar os valores dos sensores.
float temp_Value;                   // Armazena a temperatura.
int turb_Value;                     // Armazena a turbidez.
float pH_Value;                     // Armazena o valor do pH.

// Variáveis de controle.
bool mode;                          // Modo de operação, pode ser auto ou manual.
String serialData = "";             // Armazena os dados recebidos via serial.
bool limitSwitchMin;                // Estado do interruptor de limite mínimo.
bool limitSwitchMax;                // Estado do interruptor de limite máximo.
bool enable;                        // Habilita ou desabilita o motor.
bool dir;                           // Direção do motor, 1 para subir.

// Variáveis para debouncing dos interruptores de limite.
//unsigned long debounceDelay = 200;               
volatile unsigned long lastDebounceTimeMin = 0;  
volatile unsigned long lastDebounceTimeMax = 0;

bool updateSensors(void*) {
  // Medição de temperatura
  sensors.requestTemperatures();
  temp_Value = 0.9964 * sensors.getTempCByIndex(0) - 0.2338; // Resultado da calibração
  // Medição de pH
  float pH_Voltage = analogRead(pH_Pin) * (5.0/1023.0);
  float calculus = - 1024.0 * pH_Voltage / 5.0 + 1024.0;
  float ph_Value = calculus * 14.0 / 1024.0;
  pH_Value = 2.0373 * ph_Value  - 6.705; // Resultado da calibração
  // Medição de turbidez
  float turbidityVoltage = analogRead(turb_Pin) * (5.0 / 1023.0);
  // Resultado da calibração qualitativa
  if (turbidityVoltage < 0.6) {
    turb_Value = 5;
  } else if (turbidityVoltage < 1.5) {
    turb_Value = 4;
  } else if (turbidityVoltage < 2.5) {
    turb_Value = 3;
  } else if (turbidityVoltage < 3.5) {
    turb_Value = 2;
  } else {
    turb_Value = 1;
  }
  // Imprime valores na Serial
  Serial.print("Temperatura (°C): ");
  Serial.println(temp_Value);
  Serial.print("pH: ");
  Serial.println(pH_Value);
  Serial.print("Turbidez (1 a 5): ");
  Serial.println(turb_Value);
  Serial.println(" ");
  return true;
}

void setup() {
  Serial.begin(9600);
  sensors.begin();
//  pinMode(limitSwitchMin_Pin, INPUT);
//  pinMode(limitSwitchMax_Pin, INPUT);
  timer.every(2000, updateSensors);  // Atualiza a cada 2 segundos
}

void loop() {
  timer.tick();
}
