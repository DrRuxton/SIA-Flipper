#include <Wire.h>

#define SLAVE_ADDR 8 // selber wert wie beim Master

int LEDPin = 13; //mach ich bei camel-case LEDPin oder LEDpin? logisch müsste es LEDPin sein, abde LEDpin fühlt sich lesbarer an

int read; 

int blinkDelay;

void setup(){
  pinMode(LEDPin, OUTPUT);
  Wire.begin(SLAVE_ADDR);

  Wire.onReceive(receiveEvent); // onReceive funktion definieren

  Serial.begin(9600);
}

void receiveEvent(){
  read = Wire.read(); // was wird das wohl machen

  Serial.println(read);
}

void loop(){
  if(read == 0){
  delay(50); //aus wenn getrückt
  }else{
  blinkDelay = map(read, 1, 255, 100, 2000); // übertrgenen wert auf auf einen wert zwischen 100 und 2000 projezieren

  digitalWrite(LEDPin, HIGH);
  delay(blinkDelay);
  digitalWrite(LEDPin,LOW);
  delay(blinkDelay);
  }
}