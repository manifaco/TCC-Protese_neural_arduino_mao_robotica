  /*
  * -------------------------------------------------- -------------------------------------------------- -
  * Cérebros do Quintal 2016
  * Muscle SpikerShield Arduino UNO Código para testar a funcionalidade da garra.
  *
  * V1.0
  * Escrito por Tim Marzullo
  *
  * Testado com Muscle SpikerShield V2.6
  * -------------------------------------------------- -------------------------------------------------- -
  */

  #include <Servo.h>  
  #define SERVO_PIN 2 //pino para servo motor
  Garra servo; //servo para pinça


  //------------------------------------------------ -----------------------------------
  // Configura o servo
  // ------------------------------------------------ ----------------------------------
  void setup(){
    //inicia o servo
    Gripper.attach(SERVO_PIN);
  }


  //------------------------------------------------ -----------------------------------
  // Loop principal
  // Move a garra entre as posições aberta e fechada para testar a funcionalidade da garra
  // ------------------------------------------------ ----------------------------------
  loop void() {
    Gripper.write(105); //fecha a garra
    atraso(500); // atraso 500 ms
    Gripper.write(190); //abre a garra
    atraso(2000); // atraso 2000 ms
}

