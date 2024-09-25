import serial
import time

# Substitua 'COM10' pela porta correta do Arduino no seu sistema
ser = serial.Serial('COM10', 115200, timeout=1)  # Configura a porta serial

time.sleep(2)  # Espera 2 segundos para a inicialização do Arduino

# Envia dados para o Arduino
# envia um numero inteiro 


# Lê a resposta do Arduino (se houver)
while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()  # Lê a linha recebida
        print(line)
    # input_data = int(input('Digite um número inteiro: '))
    # ser.write(str(input_data).encode())  # Envia o número digitado para o Arduino


ser.close()  # Fecha a conexão serial
