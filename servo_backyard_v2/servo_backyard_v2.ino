#include <Servo.h>

Servo servoMotor;
#define NUM_LED 6 // define o número máximo de LEDs
#define MAX 600 // leitura máxima possível. AJUSTE ESSE VALOR!!
int reading[10];
int finalReading;
byte litLeds = 0;
byte multiplier = 1;
byte leds[] = {8, 9, 10, 11, 12, 13};

void setup() {
  Serial.begin(9600); // inicia a comunicação serial
  for (int i = 0; i < NUM_LED; i++) { // inicializa os LEDs como saídas
    pinMode(leds[i], OUTPUT);
  }
  servoMotor.attach(2);  // Use o pino 6 para o servo motor
  servoMotor.write(0);
}

void loop() {
  for (int i = 0; i < 10; i++) { // faz dez leituras em ~0.02 segundos
    reading[i] = analogRead(A0) * multiplier;
    delay(2);
  }
  for (int i = 0; i < 10; i++) { // calcula a média das dez leituras
    finalReading += reading[i];
  }
  finalReading /= 10;
  for (int j = 0; j < NUM_LED; j++) { // define todos os LEDs como LOW
    digitalWrite(leds[j], LOW);
  }
  Serial.print(finalReading);
  Serial.print("\t");
  finalReading = constrain(finalReading, 0, MAX);
  litLeds = map(finalReading, 0, MAX, 0, NUM_LED);
  Serial.println(litLeds);
  for (int k = 0; k < litLeds; k++) {
    digitalWrite(leds[k], HIGH);
  }
  if(litLeds>1) {
    servoMotor.write(160);
    delay(100);
  }
  else {
    servoMotor.write(0);
    delay(100);
  }
  // para debug serial, descomente as duas linhas abaixo.
  //Serial.println(finalReading);
  //delay(100);
}
