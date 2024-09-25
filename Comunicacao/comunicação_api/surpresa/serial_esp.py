import time
import serial
import threading
from flask import Flask, request, jsonify

# Configura a porta serial (Substitua 'COM10' pela porta correta)
ser = serial.Serial('COM10', 115200, timeout=1)

# Aguarda a inicialização do Arduino
time.sleep(2)

app = Flask(__name__)

# Variável global para armazenar dados recebidos do Arduino
data_do_arduino = ""

def ler_arduino():
    global data_do_arduino
    while True:
        if ser.in_waiting > 0:
            try:
                # Lê a resposta do Arduino
                data_do_arduino = ser.readline().decode('utf-8').rstrip()
                print(f'Dado recebido do Arduino: {data_do_arduino}')
            except serial.SerialException as e:
                print(f'Erro de Serial: {str(e)}')
        time.sleep(0.1)  # Pequena pausa para evitar uso excessivo da CPU

# Rota para enviar dados via HTTP para o Arduino
@app.route('/enviar_dados', methods=['POST'])
def enviar_dados():
    try:
        data = request.json
        name = data.get('name')

        if name:
            # Envia o dado para o Arduino via Serial
            ser.write(f'{name}\n'.encode())
            return jsonify({'mensagem': 'Dados enviados para o Arduino!'}), 200
        else:
            return jsonify({'erro': 'Nome não fornecido!'}), 400

    except serial.SerialException as e:
        return jsonify({'erro': str(e)}), 500

# Rota para monitorar e retornar dados recebidos do Arduino
@app.route('/monitor_serial', methods=['GET'])
def monitor_serial():
    if data_do_arduino:
        return jsonify({'recebido_do_arduino': data_do_arduino}), 200
    return jsonify({'mensagem': 'Nenhum dado na fila serial'}), 204

if __name__ == '__main__':
    # Inicia a thread para ler os dados do Arduino
    arduino_thread = threading.Thread(target=ler_arduino)
    arduino_thread.daemon = True  # Permite que a thread seja encerrada quando o programa principal é encerrado
    arduino_thread.start()

    # Roda o servidor Flask que gerencia a comunicação serial com o Arduino
    app.run(host='0.0.0.0', port=5001)
