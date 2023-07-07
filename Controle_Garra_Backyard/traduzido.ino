"""
* ----------------------------------------------------------------------------------------------------
* Backyard Brains 2015
* Código do Arduino UNO para o controle do Robotic Gripper usando o Muscle SpikerShield
*
* O código monitora a amplitude do envelope EMG, exibe a intensidade do EMG em uma barra de LED e controla
* o Robotic Gripper por meio do controle de um servo motor.
*
* V1.0
* Escrito por Marcio Amorim
* Atualizado por Stanislav Mircic
*
* Testado com o Muscle SpikerShield V2.31
* ----------------------------------------------------------------------------------------------------
"""
/*
#include <Servo.h>  
#define GRIPPER_STATE_BUTTON_PIN 4          // pino para o botão que alterna o estado padrão do gripper (aberto/fechado)
#define SERVO_PIN 2                         // pino para o servo motor
#define SENSITIVITY_BUTTON_PIN 7            // pino para o botão que seleciona a sensibilidade
#define NUM_LED 6                           // número de LEDs na barra de LED
#define GRIPPER_MINIMUM_STEP 5              // zona morta de 5 graus (usada para evitar oscilação do posicionamento)
#define OPEN_MODE 1                         // estado padrão do gripper é aberto
#define CLOSED_MODE 2                       // estado padrão do gripper é fechado
#define MINIMUM_SERVO_UPDATE_TIME 100       // atualiza a posição do servo a cada 100ms

Servo Gripper;                              // servo para o gripper
byte ledPins[] = {8, 9, 10, 11, 12, 13};     // pinos para os LEDs na barra de LED

// valores de saturação do EMG (quando o EMG atinge esse valor, o gripper estará totalmente aberto/fechado)
int sensitivities[] = {200, 350, 520, 680, 840, 1000};
int lastSensitivitiesIndex = 2;              // define o índice de sensibilidade inicial

int emgSaturationValue = 0;                  // valor de saturação do EMG/sensibilidade selecionada
int analogReadings;                          // valor medido para o EMG
byte ledbarHeight = 0;                       // variável temporária para a altura da barra de LED

unsigned long oldTime = 0;                   // marcação do último ângulo do servo atualizado (ms)
int oldDegrees = 0;                          // valor antigo do ângulo do servo
int newDegree;                               // novo valor do ângulo do servo

unsigned long debouncerTimer = 0;            // temporizador para o debouncer do botão
int gripperStateButtonValue = 0;             // variável temporária que armazena o estado do botão
int userReleasedButton = 1;                  // flag usada para evitar múltiplos eventos de botão quando o usuário segura o botão

int currentFunctionality = OPEN_MODE;        // posição padrão atual da garra


//-----------------------------------------------------------------------------------
//   Configuração do servo, entradas e saídas
//-----------------------------------------------------------------------------------
void setup(){
  // inicializa o servo
  Gripper.attach(SERVO_PIN); 
  
  // define os pinos dos botões como entrada
  pinMode(GRIPPER_STATE_BUTTON_PIN, INPUT);                             
  pinMode(SENSITIVITY_BUTTON_PIN, INPUT);                            
  
  // define todos os pinos dos LEDs como saída
  for(int i = 0; i < NUM_LED; i++){ 
    pinMode(ledPins[i], OUTPUT);
  }
  
  // obtém a sensibilidade atual
  emgSaturationValue = sensitivities[lastSensitivitiesIndex];
}


//-----------------------------------------------------------------------------------
//   Loop principal
//
//   - Verifica o estado do botão de sensibilidade
//   - Verifica o estado do botão de estado padrão do gripper
//   - Mede o EMG
//   - Mostra a intensidade do EMG na barra de LED
//   - Define o ângulo do servo com base na intensidade do EMG e no modo atual (aberto/fechado)
//-----------------------------------------------------------------------------------
void loop()
{
  //----------------------- Alternar sensibilidade ------------------------------------
  // verifica se o botão está pressionado (HIGH)
  if (digitalRead(SENSITIVITY_BUTTON_PIN))
  { 
    // desliga todos os LEDs na barra de LED
    for(int j = 0; j < NUM_LED; j++){  
      digitalWrite(ledPins[j], LOW);
    }
  
    // incrementa o índice de sensibilidade
    lastSensitivitiesIndex++;
    if(lastSensitivitiesIndex==NUM_LED){
      lastSensitivitiesIndex = 0;
    }
  
    // obtém o valor de sensibilidade atual
    emgSaturationValue = sensitivities[lastSensitivitiesIndex]; 
    
    // acende o LED na posição lastSensitivitiesIndex para feedback visual
    digitalWrite(ledPins[lastSensitivitiesIndex], HIGH);
   
    // aguarda o usuário soltar o botão
    while (digitalRead(SENSITIVITY_BUTTON_PIN)){  
      delay(10);
    }       
    // espera um pouco mais para que o feedback do LED esteja sempre visível
    delay(100);        
  }

  //----------------------- Alternar posição padrão do gripper (aberto/fechado) --------------------
  // verifica se tempo suficiente passou para o contato do botão se estabilizar
  if((millis() - debouncerTimer) > 50){
    gripperStateButtonValue = digitalRead(GRIPPER_STATE_BUTTON_PIN);
    // se o botão estiver pressionado
    if(gripperStateButtonValue == HIGH){
      // se da última vez que verificamos o botão ele não estava pressionado
      if(userReleasedButton){
        debouncerTimer = millis();
        // bloqueia eventos do botão até que o usuário o solte
        userReleasedButton = 0;
        
        // alterna o modo de operação
        if(currentFunctionality == OPEN_MODE){
          currentFunctionality = CLOSED_MODE;
        }
        else{
          currentFunctionality = OPEN_MODE;
        }
      }
    }
    else{
      userReleasedButton = 1;
    }
  }

  //----------------------------- Medir EMG -----------------------------------------------
  analogReadings = analogRead(A0); // lê o valor do EMG da entrada analógica A0

  //---------------------- Mostrar intensidade do EMG na barra de LED ------------------------------------------
  // desliga todos os LEDs da barra de LED
  for(int j = 0; j < NUM_LED; j++){  
    digitalWrite(ledPins[j], LOW);
  }
   
  // calcula quais LEDs devem ser ligados na barra de LED
  analogReadings = constrain(analogReadings, 30, emgSaturationValue);
  ledbarHeight = map(analogReadings, 30, emgSaturationValue, 0, NUM_LED);
  
  // liga os LEDs na barra de LED
  for(int k = 0; k < ledbarHeight; k++){
    digitalWrite(ledPins[k], HIGH);
  }

  //-------------------- Controlar a garra de acordo com a intensidade do EMG -----------------------------
  // define o novo ângulo se tempo suficiente passou
  if (millis() - oldTime > MINIMUM_SERVO_UPDATE_TIME){
    // calcula o novo ângulo para o servo
    if(currentFunctionality == OPEN_MODE){  
      analogReadings = constrain(analogReadings, 40, emgSaturationValue);
      newDegree = map(analogReadings, 40 ,emgSaturationValue, 190, 105); 
    }
    else{
      analogReadings = constrain(analogReadings, 120, emgSaturationValue);
      newDegree = map(analogReadings, 120 ,emgSaturationValue, 105, 190);
    }
  
    // verifica se estamos na zona morta do servo
    if(abs(newDegree-oldDegrees) > GRIPPER_MINIMUM_STEP){
      // define o novo ângulo do servo
      Gripper.write(newDegree); 
    }
    oldTime = millis();
    oldDegrees = newDegree;
  }
}
*/