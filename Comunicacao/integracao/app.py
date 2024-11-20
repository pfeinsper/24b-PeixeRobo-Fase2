from flask import Flask, render_template, request
import requests

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        Profundidade = request.form['Profundidade']
        Tempo = request.form['Tempo']
        
        # Enviar dados para outro servidor
        try:
            response = requests.post('http://192.168.137.29', 
                                     json={'profundidade': Profundidade, 'tempo': Tempo})
            return f"Enviado com sucesso! Resposta: {response.text}"
        except Exception as e:
            return f"Erro ao enviar: {str(e)}"
    
    return render_template('index.html')

if __name__ == '__main__':
    app.run(port=5000)