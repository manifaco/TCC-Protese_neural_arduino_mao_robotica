/*
#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 4, 8, 2, 6, 19); //(5, 4, 1, 0, 6, 19) pinos que serão utilizados no display

void setup() {
  lcd.begin(16, 2); // Define o número de linhas e colunas no display
  Serial.begin(9600); // Inicializa a comunicação serial com uma taxa de 9600 bps
}

void scrollLeft(int passos) { // Rolagem para a esquerda
  for (int posicao = 0; posicao < passos; posicao++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }
}

void scrollRight(int passos) {
  for (int posicao = 0; posicao < passos; posicao++) {
    lcd.scrollDisplayRight();
    delay(300);
  }
}

void loop() {
  if (Serial.available()) {
    int valorRecebido = Serial.parseInt(); // Lê o valor recebido do Arduino 1
    
    lcd.clear(); // Limpa a tela
    lcd.setCursor(0, 0); // Posiciona o cursor na coluna 0, linha 0
    lcd.print("Valor Recebido:"); // Texto que indica o valor recebido
    lcd.setCursor(0, 1);
    lcd.print(valorRecebido); // Exibe o valor recebido no display
    
    delay(3000);
  } else {
    lcd.clear(); // Limpa a tela
    lcd.setCursor(3, 0); // Posiciona o cursor na coluna 3, linha 0
    lcd.print("Embarcados"); // Texto que vai para o LCD
    lcd.setCursor(3, 1);
    lcd.print(" LCD 16x2");
    delay(3000);
    
    scrollLeft(3);
    scrollRight(6);
  }
}
*/