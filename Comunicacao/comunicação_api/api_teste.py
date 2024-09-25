from flask import Flask, jsonify, request, render_template
import time
import serial
import threading

# Configuração da porta serial (Substitua 'COM10' pela porta correta)
ser = serial.Serial('COM10', 115200, timeout=1)

# Aguarda a inicialização do Arduino
time.sleep(2)

app = Flask(__name__)

# Rota inicial para testar o funcionamento
@app.route('/', methods=['GET'])
def home():
    return render_template('form.html')

# Endpoint de POST para enviar dados do formulário
@app.route('/submit', methods=['POST'])
def submit():
    name = request.form.get('name')
    print(f"Enviando para o Arduino: {name}")
    
    try:
        ser.write(f'{name}\n'.encode())  # Envia o dado para o Arduino
    except serial.SerialException as e:
        return f"Erro ao enviar dados: {str(e)}", 500

    return f'Formulário recebido! Nome enviado: {name}'

def monitor_serial():
    """Função que monitora a porta serial em uma thread separada."""
    while True:
        if ser.in_waiting > 0:
            try:
                # Lê a resposta do Arduino
                data = ser.readline().decode('utf-8').rstrip()
                if data:
                    print(f"Recebido do Arduino: {data}")
            except serial.SerialException as e:
                print(f"Erro de leitura da porta serial: {str(e)}")
            time.sleep(0.1)  # Evita o uso excessivo de CPU

if __name__ == '__main__':
    # Inicia o monitoramento da porta serial em uma thread separada
    serial_thread = threading.Thread(target=monitor_serial, daemon=True)
    serial_thread.start()

    # Roda o servidor Flask
    app.run(host='0.0.0.0', port=5000, debug=True)
