#define NUM_LED 6 // define o número máximo de LEDs
#define MAX 400 // leitura máxima possível. AJUSTE ESSE VALOR!!
#define DC_MOTOR 4

int reading[10];
int finalReading;
byte litLeds = 0;
byte multiplier = 1;
byte leds[] = {8, 9, 10, 11, 12, 13};

void setup(){
Serial.begin(9600); // inicia a comunicação serial
for(int i = 0; i < NUM_LED; i++){ // inicializa os LEDs como saídas
pinMode(leds[i], OUTPUT);
pinMode (DC_MOTOR, OUTPUT);

}
}

void loop(){
for(int i = 0; i < 10; i++){ // faz dez leituras em ~0.02 segundos
reading[i] = analogRead(A0) * multiplier;
delay(2);
}
for(int i = 0; i < 10; i++){ // calcula a média das dez leituras
finalReading += reading[i];
}
finalReading /= 10;
for(int j = 0; j < NUM_LED; j++){ // define todos os LEDs como LOW
digitalWrite(leds[j], LOW);
}
Serial.print(finalReading);
Serial.print("\t");
finalReading = constrain(finalReading, 0, MAX);
litLeds = map(finalReading, 0, MAX, 0, NUM_LED);
Serial.println(litLeds);
for(int k = 0; k < litLeds; k++){
digitalWrite(leds[k], HIGH);


}
if (finalReading>300){ 
  digitalWrite(13, HIGH);
  analogWrite(DC_MOTOR, 255);
  delay(3000);
  digitalWrite(13, LOW);
    analogWrite(DC_MOTOR, 0);

}
// para debug serial, descomente as duas linhas abaixo.
//Serial.println(finalReading);
//delay(100);
}
    
