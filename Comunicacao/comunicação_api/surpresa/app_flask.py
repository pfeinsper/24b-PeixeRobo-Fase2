from flask import Flask, jsonify, request, render_template
import requests

app = Flask(__name__)

# Rota inicial para exibir o formulário
@app.route('/', methods=['GET'])
def home():
    return render_template('form.html')

# Endpoint para coletar dados do formulário e enviar via requisição HTTP
@app.route('/submit', methods=['POST'])
def submit():
    name = request.form.get('name')
    print(f"Nome recebido: {name}")
    #limite name entre 4500 e -4500
    if int(name) > 4500:
        name = 4500
    elif int(name) < -4500:
        name = -4500


    # Envia os dados para o servidor Flask que gerencia a comunicação serial
    try:
        response = requests.post('http://127.0.0.1:5001/enviar_dados', json={'name': name})
        if response.status_code == 200:
            return render_template('form.html')  
        else:
            return f'Erro ao enviar dados: {response.json()}'
    except requests.ConnectionError as e:
        return f'Erro ao conectar ao servidor de comunicação serial: {str(e)}'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
