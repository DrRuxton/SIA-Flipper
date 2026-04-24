#include <Arduino.h>

//definiere Schalter Pins
#define flipperButtonLeft 13
#define flipperButtonRight 12

//definiere Hebel Pins
#define flipperLeft 2
#define flipperRight 15

void hebelSetup(){
    //Pins initialisieren
    pinMode(flipperButtonLeft, INPUT_PULLUP);
    pinMode(flipperButtonRight, INPUT_PULLUP);
    pinMode(flipperLeft, OUTPUT);
    pinMode(flipperRight, OUTPUT);
}

void loop(){
  if(digitalRead(flipperButtonLeft) == LOW){
    digitalWrite(flipperLeft, HIGH);
    Serial.println("Button left");
    delay(200);
  }
  else{
    digitalWrite(flipperLeft, LOW);
  }

  if(digitalRead(flipperButtonRight) == LOW){
    digitalWrite(flipperRight, HIGH);
    Serial.println("Button right");
    delay(200);
  }
  else{
    digitalWrite(flipperRight, LOW);
  }
}