#include <LiquidCrystal.h>
LiquidCrystal lcd(5,4, 8, 2, 6, 19); //(5,4, 1, 0, 6, 19)pinos que serão utilizados no display

void setup(){
  lcd.begin(16,2); //define numero de linhas e colunas no display
}

void scrollLeft (int passos){ //rolagem para a esquerda
  for (int posicao = 0; posicao < passos; posicao++){
    lcd.scrollDisplayLeft();
    delay (300);
  }
}

void scrollRight (int passos){
  for (int posicao = 0; posicao < passos; posicao++){
    lcd.scrollDisplayRight();
    delay(300);
  }
}

void loop (){
  lcd.clear(); //Limpa a tela
  lcd.setCursor(3,0); //Posiciona o cursor na coluna 3, linha 0;
  lcd.print("Embarcados");//texto que vai para o lcd
  lcd.setCursor(3, 1);
  lcd.print(" LCD 16x2");
  delay(3000);

  scrollLeft(3);
  scrollRight(6);
}
