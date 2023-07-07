/*
    Conecte o terminal central do potenciômetro ao pino analógico A0 do Arduino.
    Conecte um dos terminais externos do potenciômetro ao GND (terra) do Arduino.
    Conecte o outro terminal externo do potenciômetro ao 5V do Arduino.
*/
// Define os pinos utilizados
const int pinoPotenciometro = A0;  // Pino analógico para ler o valor do potenciômetro

// Define os limites da variável
const int valorMinimo = 200;  // Valor mínimo da variável
const int valorMaximo = 750;  // Valor máximo da variável

int variavel = valorMinimo;  // Variável inicializada com o valor mínimo

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Lê o valor do potenciômetro
  int valorPotenciometro = analogRead(pinoPotenciometro);
  
  // Mapeia o valor lido do potenciômetro para o intervalo desejado
  variavel = map(valorPotenciometro, 0, 1023, valorMinimo, valorMaximo);
  
  // Imprime o valor atual da variável no monitor serial
  Serial.print("Valor da variável: ");
  Serial.println(variavel);
  
  // Aguarda um pequeno intervalo antes de ler novamente o potenciômetro
  delay(100);
}
