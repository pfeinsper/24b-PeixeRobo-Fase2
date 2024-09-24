from flask import Flask, jsonify, request

app = Flask(__name__)

# Rota inicial para testar o funcionamento
@app.route('/', methods=['GET'])
def home():
    return jsonify(message="API esta funcionando corretamente!")

# Endpoint de exemplo para retornar dados JSON
@app.route('/dados', methods=['GET'])
def obter_dados():
    dados = {
        'nome': 'Teste',
        'idade': 25,
        'cidade': 'São Paulo'
    }
    return jsonify(dados)

# Endpoint de POST para enviar e receber dados
@app.route('/enviar', methods=['POST'])
def enviar_dados():
    data = request.json
    print(data)
    response = {
        'mensagem': 'Dados recebidos!',
        'dados_enviados': data
    }
    
    return jsonify(response), 201

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)

