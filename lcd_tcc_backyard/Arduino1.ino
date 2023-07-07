/* versão 1
const int sensorPin = A0;  // Pino analógico onde o sensor está conectado

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial com uma taxa de 9600 bps
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // Lê o valor do sensor analógico
  Serial.println(sensorValue);  // Envia o valor lido para o Arduino 2

  delay(1000);  // Aguarda 1 segundo antes de ler novamente
}
*/
/*
#include <Servo.h>

Servo servoMotor;
#define NUM_LED 6 // define o número máximo de LEDs
#define MAX 400 // leitura máxima possível. AJUSTE ESSE VALOR!!
int reading[10];
int finalReading;
byte litLeds = 0;
byte multiplier = 1;
byte leds[] = {8, 9, 10, 11, 12, 13};

void setup() {
  Serial.begin(9600); // inicia a comunicação serial com uma taxa de 9600 bps
  for (int i = 0; i < NUM_LED; i++) { // inicializa os LEDs como saídas
    pinMode(leds[i], OUTPUT);
  }
  servoMotor.attach(6);  // Use o pino 6 para o servo motor
  servoMotor.write(0);
}

void loop() {
  for (int i = 0; i < 10; i++) { // faz dez leituras em ~0.02 segundos
    reading[i] = analogRead(A0) * multiplier; // Lê o valor do sensor analógico e multiplica pelo multiplicador
    delay(2); // Aguarda um curto período de tempo para a próxima leitura
  }
  for (int i = 0; i < 10; i++) { // calcula a média das dez leituras
    finalReading += reading[i];
  }
  finalReading /= 10; // Calcula a média dividindo pelo número de leituras
  
  for (int j = 0; j < NUM_LED; j++) { // define todos os LEDs como LOW (desligados)
    digitalWrite(leds[j], LOW);
  }
  
  int valorPorcentagem = map(finalReading, 0, MAX, 0, 100); // Mapeia o valor lido para uma porcentagem usando a função map
  
  Serial.print(valorPorcentagem); // Envia o valor em porcentagem pela comunicação serial
  Serial.println(); // Adiciona uma quebra de linha após o valor enviado
  
  litLeds = map(valorPorcentagem, 0, 100, 0, NUM_LED); // Mapeia o valor em porcentagem para o número de LEDs a serem acesos
  for (int k = 0; k < litLeds; k++) {
    digitalWrite(leds[k], HIGH); // Acende os LEDs correspondentes ao valor mapeado
  }
  
  servoMotor.write(30 * litLeds); // Move o servo motor proporcional ao número de LEDs acesos
  
  // para debug serial, descomente as duas linhas abaixo.
  //Serial.println(finalReading);
  //delay(100);
}
*/