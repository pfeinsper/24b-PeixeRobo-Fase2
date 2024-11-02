import serial
import csv

# Configura a porta serial
ser = serial.Serial('COM10', 115200)  # Altere 'COM3' para a porta correta no seu sistema
ser.flushInput()

# Abre um arquivo CSV para escrita
with open('dados_lora.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    
    headers = ["Tempo", "RSSI", "SNR","num_pacote"]
    # Escreve o cabeçalho
    writer.writerow(headers)
    
    try:
        while True:
            if ser.in_waiting > 0:
                # Lê uma linha da serial
                linha_serial = ser.readline().decode('utf-8').strip()
                
                # Divide a linha em colunas
                dados = linha_serial.split(',')
                
                # Verifica se os dados estão no formato correto
                if len(dados) == len(headers):
                    writer.writerow(dados)
                    print(f"Dados recebidos: {dados}")
                    
    except KeyboardInterrupt:
        print("Programa encerrado.")
