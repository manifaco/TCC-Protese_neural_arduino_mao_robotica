/*
#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(18, 17, 5, 4, 16, 15); //portas display

Servo servoMotor;
#define NUM_LED 6 // define o número máximo de LEDs
#define MAX 555 // leitura máxima possível. AJUSTE ESSE VALOR!!
int reading[10];
int finalReading;
int finalReadingD1=0;
int finalReadingD1LCD=0;
int finalReadingD2LCD=0;
byte litLeds = 0;
byte multiplier = 1;
byte leds[] = {8, 9, 10, 11, 12, 13};
int cont = 0;


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
  

  //-------------------------------lcd----------------------------------
  lcd.clear(); //Limpa a tela
  lcd.setCursor(0,0); //Posiciona o cursor na coluna 3, linha 0;
  lcd.print("TCC Kaio Littike");//texto que vai para o lcd
  lcd.setCursor(0, 1);
  lcd.print("D1= ");
  cont+=1;
  if (Serial.available()) {//leitura serial
    finalReadingD1 = Serial.parseInt();// Lê o valor recebido do Arduino 1
  }
  else{
    finalReadingD1 = 0;
  }
  if(cont%5==0){ //D1 - para só exibir o valor no LCD a cada 5 medidas.
    finalReadingD1LCD=finalReadingD1;
    lcd.print(finalReadingD1LCD);
  }
  else{
    lcd.print(finalReadingD1LCD);
  }
  lcd.setCursor(7, 1);
  lcd.print(" D2= ");

  if(cont%5==0){ //D2 - para só exibir o valor no LCD a cada 5 medidas.
    finalReadingD2LCD=finalReading;
    lcd.print(finalReadingD2LCD);
  }
  else{
    lcd.print(finalReadingD2LCD);
  }
  delay(2);

  //-----------------------------LEDS------------------------------------
  for (int k = 0; k < litLeds; k++) {
    digitalWrite(leds[k], HIGH);
  }

  //---------------------------servo-------------------------------------
  if(litLeds>2) {
    servoMotor.write(0);
    delay(10);
  }
  else {
    servoMotor.write(160);
    delay(10);
  }
}
*/