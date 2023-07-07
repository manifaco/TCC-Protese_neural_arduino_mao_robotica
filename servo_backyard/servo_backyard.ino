#include <Servo.h>

#define NUM_LED 6 // define o número máximo de LEDs
#define MAX 100 // leitura máxima possível. AJUSTE ESSE VALOR!!
int leitura[10];
int leituraFinal;
byte ledsAcesos = 0;
byte multiplicador = 1;
byte leds[] = {8, 9, 10, 11, 12, 13};

Servo servo;

void setup() {
  Serial.begin(9600); // inicia a comunicação serial
  
  for (int i = 0; i < NUM_LED; i++) { // inicializa os LEDs como saídas
    pinMode(leds[i], OUTPUT);
  }
  
  servo.attach(7); // define o pino do servo motor
}

void loop() {
  for (int i = 0; i < 10; i++) { // faz dez leituras em ~0.02 segundos
    leitura[i] = analogRead(A0) * multiplicador;
    delay(2);
  }
  
  for (int i = 0; i < 10; i++) { // calcula a média das dez leituras
    leituraFinal += leitura[i];
  }
  leituraFinal /= 10;
  
  for (int j = 0; j < NUM_LED; j++) { // define todos os LEDs como LOW
    digitalWrite(leds[j], LOW);
  }
  
  Serial.print(leituraFinal);
  Serial.print("\t");
  
  leituraFinal = constrain(leituraFinal, 0, MAX);
  ledsAcesos = map(leituraFinal, 0, MAX, 0, NUM_LED);
  Serial.println(ledsAcesos);
  
  for (int k = 0; k < ledsAcesos; k++) {
    digitalWrite(leds[k], HIGH);
  }
  
  int anguloServo = map(ledsAcesos, 1, NUM_LED, 0, 180); // mapeia o número de LEDs acesos para o ângulo do servo (0 a 180 graus)
  servo.write(anguloServo); // define o ângulo do servo motor
  
  // para debug serial, descomente as duas linhas abaixo.
  //Serial.println(leituraFinal);
  //delay(100);
}
