#include <Servo.h>

Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;
Servo servoMotor4;

#define NUM_LED 6 // define o número máximo de LEDs
#define MAX 400 // leitura máxima possível. AJUSTE ESSE VALOR!!
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
  servoMotor1.attach(A1);  // Use o pino 6 para o servo motor
  servoMotor2.attach(A2);
  servoMotor3.attach(A3);
  servoMotor4.attach(A4);
  servoMotor1.write(0);
  servoMotor2.write(0);
  servoMotor3.write(0);
  servoMotor4.write(0);
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
  servoMotor1.write(30 * litLeds);
  servoMotor2.write(30 * litLeds);
  servoMotor3.write(30 * litLeds);
  servoMotor4.write(30 * litLeds);
  // para debug serial, descomente as duas linhas abaixo.
  //Serial.println(finalReading);
  //delay(100);
}
