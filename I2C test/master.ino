#include <Wire.h>

#define SLAVE_ADDR 8

int potiPin = 0;
int buttonPin = 13;
int transVal = 0;
int pressed = 0;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  pinMode(buttonPin,INPUT_PULLUP);  // button ≙ input
}

void loop(){
  delay(50);
  pressed = digitalRead(buttonPin);
  if(pressed == LOW){
    transVal = 0;     //wenn button gedrückt: kein blinken
  }else{
  transVal = map(analogRead(potiPin), 0, 1023, 255, 1);  // poti giebt wert zwischen 0 und 1023 aus, wier wollen zwischen 255 und 1, + wird "umgedreht"
  }
  Serial.println(transVal);
  Wire.beginTransmission(SLAVE_ADDR); 
  Wire.write(transVal);                //sended den wert an den slave 
  Wire.endTransmission();
}
