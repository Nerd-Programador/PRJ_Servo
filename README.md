# PRJ_Servo
Projeto para controlar via Wi-Fi o movimento de Abrir e Fechar de uma porta.
Este código implementa um servidor web em um módulo ESP8266, que controla um servo motor e um ponte H. Quando o servidor recebe um comando específico (enviado pelo navegador ou pelo monitor serial), o servo motor é movimentado e o ponte H é acionado de acordo com o comando recebido. A seguir, há uma análise mais detalhada do código:

Bibliotecas:
O código utiliza as seguintes bibliotecas:

ESP8266WebServer.h: fornece as funções necessárias para criar um servidor web em um módulo ESP8266;

WiFiClient.h: permite a conexão com uma rede Wi-Fi;

Servo.h: fornece as funções necessárias para controlar um servo motor.

Variáveis:

ssid: nome da rede Wi-Fi à qual o módulo ESP8266 irá se conectar;

password: senha da rede Wi-Fi;

meuServo: objeto que representa o servo motor;

posicaoServo: posição atual do servo motor;

ponteHA: pino do módulo ESP8266 conectado ao pino H da ponte H;

ponteHB: pino do módulo ESP8266 conectado ao pino L da ponte H;

velocidade: velocidade do servo motor (definido como 1023, que é a velocidade máxima);

server: objeto que representa o servidor web.

Funções:

handleRoot(): função que é chamada quando o servidor web recebe uma requisição na raiz (/). Essa função envia a página HTML contida no arquivo 
index.h para o navegador;

handleComando(): função que é chamada quando o servidor web recebe uma requisição na rota /comando. Essa função verifica se o argumento 'comando' foi enviado e executa a ação correspondente ao comando recebido. Em seguida, envia uma resposta para o navegador;

setup(): função que é chamada uma vez na inicialização do código. Nesta função, são configurados o servo motor, a ponte H, a conexão com a rede Wi-Fi, e as rotas do servidor web;

loop(): função que é executada continuamente enquanto o módulo ESP8266 estiver ligado. Nesta função, são verificadas as requisições pendentes do servidor web e os comandos enviados pelo monitor serial.

Fluxo principal:

A sequência principal de ações do código é a seguinte:
Configuração do servo motor e da ponte H na função setup();

Configuração da conexão com a rede Wi-Fi na função setup();

Configuração das rotas do servidor web na função setup();

Execução do servidor web na função loop();

Verificação das requisições pendentes e dos comandos enviados pelo monitor serial na função loop();

Execução das ações correspondentes aos comandos recebidos na função handleComando().
