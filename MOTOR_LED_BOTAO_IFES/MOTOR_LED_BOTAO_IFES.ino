#define DC_MOTOR 10
#define ON_OFF 6
#define ON_OFF2 4

void setup() {
  // put your setup code here, to run once:
pinMode (DC_MOTOR, OUTPUT);
pinMode (ON_OFF, INPUT_PULLUP);
pinMode(13, OUTPUT);
pinMode(ON_OFF2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(ON_OFF) == LOW){
  analogWrite(DC_MOTOR, 255);
}

else{
  analogWrite(DC_MOTOR, 0);
}

if(digitalRead(ON_OFF2) == LOW){
 digitalWrite(13, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(13, LOW);   // turn the LED off by making the voltage LOW
  delay(1000); 
  digitalWrite(13, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(13, LOW);   // turn the LED off by making the voltage LOW
  delay(1000); 
  digitalWrite(13, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(13, LOW);   // turn the LED off by making the voltage LOW
  delay(1000); 

}
}
