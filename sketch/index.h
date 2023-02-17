// Define a página HTML principal a ser exibida pelo servidor
const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Controle do Servo Motor</title>
  <style>
    /* Define os estilos CSS para a página HTML */
    body {
      font-family: Arial, Helvetica, sans-serif;
    }
    .container {
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      margin-top: 50px;
    }
    .btn {
      font-size: 1.5em;
      width: 200px;
      height: 50px;
      margin: 10px;
      border: none;
      border-radius: 5px;
      background-color: #4CAF50;
      color: white;
    }
    .input {
      font-size: 1.5em;
      text-align: center;
      width: 200px;
      height: 50px;
      margin: 10px;
      border: none;
      border-radius: 5px;
      background-color: #f2f2f2;
      color: #333;
    }
  </style>
</head>
<body>
  <!-- Cria os elementos HTML (um campo de entrada de número e dois botões) para a página -->
  <div class="container">
    <input id="posicao" class="input" type="number" value="0" min="0" max="180" step="1">
    <button id="btn-abrir" class="btn">Abrir</button>
    <button id="btn-fechar" class="btn">Fechar</button>
  </div>
  <script>
    // Obter os elementos HTML da página pelo seu ID
    const posicaoInput = document.getElementById('posicao');
    const abrirButton = document.getElementById('btn-abrir');
    const fecharButton = document.getElementById('btn-fechar');

// Adicionar eventos de clique para os botões "Abrir" e "Fechar"
abrirButton.addEventListener('click', () => {
  enviarComandoSerial('A');
});

fecharButton.addEventListener('click', () => {
  enviarComandoSerial('F');
});

// Adicionar evento de mudança para o campo de entrada de posição
posicaoInput.addEventListener('input', () => {
  enviarComandoSerial(`P${posicaoInput.value}`);
});

// Função que envia um comando serial ao servidor quando um evento de clique é acionado, ou quando há uma mudança no campo de entrada de posição.
// Esta função utiliza o objeto XMLHttpRequest para enviar um comando HTTP GET contendo o comando a ser enviado para o servidor.
function enviarComandoSerial(comando) {
  const xhr = new XMLHttpRequest();
  xhr.open('GET', `comando?comando=${comando}`, true);
  xhr.send();
}
  </script>
</body>
</html>
)=====";