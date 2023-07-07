void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial com uma taxa de transmissão de 9600 bps
}

void loop() {
  if (Serial.available()) {
    String dadosRecebidos = Serial.readStringUntil('\n');  // Lê a linha recebida até o caractere de nova linha
    int posicaoVirgula = dadosRecebidos.indexOf(',');  // Localiza a posição da vírgula

    if (posicaoVirgula != -1) {
      String valor1String = dadosRecebidos.substring(0, posicaoVirgula);  // Extrai o valor 1 como uma string
      String valor2String = dadosRecebidos.substring(posicaoVirgula + 1);  // Extrai o valor 2 como uma string

      int valor1 = valor1String.toInt();  // Converte o valor 1 para um inteiro
      int valor2 = valor2String.toInt();  // Converte o valor 2 para um inteiro

      // Faça algo com os valores recebidos
      Serial.print("Valor 1: ");
      Serial.println(valor1);
      Serial.print("Valor 2: ");
      Serial.println(valor2);
    }
  }
}
