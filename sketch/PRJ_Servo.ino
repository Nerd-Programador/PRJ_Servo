#include <ESP8266WebServer.h>  // biblioteca para criar um servidor web com o módulo ESP8266
#include <WiFiClient.h>        // biblioteca para controlar a conexão Wi-Fi
#include <Servo.h>             // biblioteca para controlar servos motores

#include "index.h"  // inclui o arquivo index.h, que contém o código HTML da página web

const char* ssid = "*******";          // nome da rede Wi-Fi
const char* password = "***********";  // senha da rede Wi-Fi

Servo meuServo;  // cria um objeto do tipo Servo, que será utilizado para controlar um servo motor

// define algumas variáveis globais que serão utilizadas para controlar o servo motor e as pontes H
int posicaoServo = 0;
int ponteHA = 5;
int ponteHB = 4;
int velocidade = 1023;

ESP8266WebServer server(80);  // cria um objeto do tipo ESP8266WebServer, que será utilizado para criar o servidor web

void handleRoot() {
  server.send(200, "text/html", MAIN_page);  // envia a página HTML para o navegador
}

void handleComando() {
  // verifica se a requisição contém um argumento chamado 'comando'
  if (server.hasArg("comando")) {
    // armazena o valor do argumento 'comando' em uma variável
    String comando = server.arg("comando");
    // exibe o valor do comando no monitor serial
    Serial.println(comando);

    // verifica qual é o valor do comando e executa as ações correspondentes
    if (comando == "A") {
      posicaoServo = 180;
      meuServo.write(posicaoServo);
      digitalWrite(ponteHA, LOW);
      digitalWrite(ponteHB, HIGH);
      delay(3000);
      posicaoServo = 0;
      meuServo.write(posicaoServo);
      digitalWrite(ponteHA, LOW);
      digitalWrite(ponteHB, LOW);
    } else if (comando == "F") {
      posicaoServo = 180;
      meuServo.write(posicaoServo);
      digitalWrite(ponteHA, HIGH);
      digitalWrite(ponteHB, LOW);
      delay(5000);
      posicaoServo = 0;
      meuServo.write(posicaoServo);
      digitalWrite(ponteHA, LOW);
      digitalWrite(ponteHB, LOW);
    } else if (comando.startsWith("P")) {
      // extrai o valor da posição do comando e armazena em uma variável
      int novaPosicao = comando.substring(1).toInt();
      // verifica se a posição está dentro do limite do servo e, se estiver, atualiza a posição do servo
      if (novaPosicao >= 0 && novaPosicao <= 180) {
        posicaoServo = novaPosicao;
        meuServo.write(posicaoServo);
      }
    }
  }
  // envia uma resposta para o navegador informando que o comando foi recebido
  server.send(200, "text/plain", "Comando recebido");
}

void setup() {

  // configura a rota /comando para chamar a função handleComando quando receber requisições
  server.on("/comando", handleComando);

  // inicializa o servo motor e as pontes H
  meuServo.attach(12);
  pinMode(ponteHA, OUTPUT);
  pinMode(ponteHB, OUTPUT);

  // inicializa a comunicação serial para debug
  Serial.begin(115200);

  // conecta à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  // exibe o endereço IP na porta serial
  Serial.println("Conectado na rede WiFi");
  Serial.print("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  // configura a rota raiz para chamar a função handleRoot quando receber requisições
  server.on("/", handleRoot);

  // inicia o servidor HTTP
  server.begin();
}

void loop() {
  // verifica se há requisições pendentes e as processa
  server.handleClient();

  // verifica se há comandos disponíveis na comunicação serial
  if (Serial.available() > 0) {
    char comando = Serial.read();

    // se o comando recebido for 'A', abre a comporta por 3 segundos
    if (comando == 'A') {
      posicaoServo = 180;
      meuServo.write(posicaoServo);
      digitalWrite(ponteHA, LOW);
      digitalWrite(ponteHB, HIGH);
      delay(3000);
      posicaoServo = 0;
      meuServo.write(posicaoServo);
      digitalWrite(ponteHA, LOW);
      digitalWrite(ponteHB, LOW);

      // se o comando recebido for 'F', fecha a comporta por 5 segundos
    } else if (comando == 'F') {
      posicaoServo = 180;
      meuServo.write(posicaoServo);
      digitalWrite(ponteHA, HIGH);
      digitalWrite(ponteHB, LOW);
      delay(5000);
      posicaoServo = 0;
      meuServo.write(posicaoServo);
      digitalWrite(ponteHA, LOW);
      digitalWrite(ponteHB, LOW);
    }
  }
}