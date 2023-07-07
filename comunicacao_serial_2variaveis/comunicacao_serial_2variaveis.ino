//transmissor
void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial com uma taxa de transmissão de 9600 bps
}

void loop() {
  int valor1 = 42;
  int valor2 = 73;

  // Envie os valores separados por um caractere delimitador (por exemplo, vírgula)
  Serial.print(valor1);
  Serial.print(",");
  Serial.println(valor2);

  delay(1000);  // Aguarda 1 segundo antes de enviar novamente
}
