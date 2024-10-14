### Este script é um exemplo de como usar um trigger para ativar a câmera.
# O script está sendo feito para testes e foi utilizado o OpenMV IDE para suir na placa OpenMV M7.

import sensor
import time
import pyb  # Importa a biblioteca para controlar os pinos


# Inicializa a câmera
sensor.reset()  # Reset e inicializa o sensor
sensor.set_pixformat(sensor.RGB565)  # Define o formato de pixel para RGB565 (ou GRAYSCALE)
sensor.set_framesize(sensor.QVGA)  # Define o tamanho do frame para QVGA (320x240)
sensor.skip_frames(time=2000)  # Aguarda 2 segundos para que as configurações tenham efeito

clock = time.clock()  # Cria um objeto clock para rastrear o FPS

# Configura o pino 6 como entrada (input) para o trigger
trigger_pin = pyb.Pin('P6', pyb.Pin.IN, pyb.Pin.PULL_DOWN)

is_recording = False  # Flag para verificar se está gravando ou não
previous_trigger_state = 0  # Armazena o estado anterior do pino

def debounce(pin, delay=50):
    """Função de debounce para garantir que o sinal esteja estável."""
    state = pin.value()
    time.sleep_ms(delay)  # Atraso para debouncing
    return state == pin.value()  # Verifica se o estado é consistente após o atraso

while True:
    current_trigger_state = trigger_pin.value()  # Lê o estado atual do pino

    # Detecção de borda de subida (de 0 para 1) - inicia gravação
    if current_trigger_state == 1 and previous_trigger_state == 0:
        if debounce(trigger_pin):  # Verifica se o estado é estável
            if not is_recording:
                print("Iniciando gravação...")
                is_recording = True  # Inicia a gravação
            else:
                print("Parando a gravação...")
                is_recording = False


    # Se estiver gravando, captura imagens continuamente
    if is_recording:
        clock.tick()  # Atualiza o clock de FPS
        img = sensor.snapshot()  # Tira uma foto e retorna a imagem
        print(clock.fps())  # Exibe o FPS atual

    # Atualiza o estado anterior do pino para a próxima verificação
    previous_trigger_state = current_trigger_state
