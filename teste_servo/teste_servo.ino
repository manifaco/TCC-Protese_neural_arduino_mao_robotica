#include <Servo.h>

Servo servoMotor; // Cria um objeto do tipo Servo

void setup() {
  servoMotor.attach(2); // Define o pino 9 como saída para o servo motor
}

void loop() {
  // Gira o servo para 0 graus
  servoMotor.write(0);
  delay(1000); // Aguarda 1 segundo

  // Gira o servo para 180 graus
  servoMotor.write(160);
  delay(1000); // Aguarda 1 segundo

  // Retorna o servo para 0 graus
  servoMotor.write(0);
  delay(1000); // Aguarda 1 segundo
}
