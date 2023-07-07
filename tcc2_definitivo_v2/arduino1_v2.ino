
#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(18, 17, 5, 4, 16, 15); //portas display
//-------potênciômetro-----------------------
const int pinoPotenciometro = A5;  // Pino analógico para ler o valor do potenciômetro
const int valorMinimo = 200;  // Valor mínimo da variável
const int valorMaximo = 750;  // Valor máximo da variável
int MAX = 500;  // sensibilidade sensor neural2

Servo servoMotor;
#define NUM_LED 6 // define o número máximo de LEDs
int reading[10];
int finalReading;
byte litLeds = 0;
byte multiplier = 1;
byte leds[] = {8, 9, 10, 11, 12, 13};
int cont = 0;
int finalReadingLCD=0;

void setup() {
  Serial.begin(9600); // inicia a comunicação serial
  for (int i = 0; i < NUM_LED; i++) { // inicializa os LEDs como saídas
    pinMode(leds[i], OUTPUT);
  }
  servoMotor.attach(2);  // Use o pino 6 para o servo motor
  servoMotor.write(160);
  lcd.begin(16,2); //define numero de linhas e colunas no display
}

void loop() {
  //----------------potênciômetro-----------------------
  int valorPotenciometro = analogRead(pinoPotenciometro);// Lê o valor do potenciômetro
  MAX = map(valorPotenciometro, 0, 1023, valorMinimo, valorMaximo);// Mapeia o valor lido do potenciômetro para o intervalo desejado
  
  //----------------------Leitura sensor--------------------------------
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
  finalReading = constrain(finalReading, 0, MAX);
  litLeds = map(finalReading, 0, MAX, 0, NUM_LED);
  Serial.print(finalReading);
  Serial.print(",");
  Serial.println(MAX);

  //-----------------------------LEDS------------------------------------
  for (int k = 0; k < litLeds; k++) {
    digitalWrite(leds[k], HIGH);
  }

  //---------------------------servo-------------------------------------
  if(litLeds>2) {
    servoMotor.write(160);
    delay(10);
  }
  else {
    servoMotor.write(0);
    delay(10);
  }
}
