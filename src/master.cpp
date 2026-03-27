#include <Arduino.h>
#include <Wire.h>

//Adresse des I2C Geräts (muss gleich der Adresse des Slaves sein)
#define I2C_DEV_ADDR 0x55

//definiere Schalter Pins
#define flipperButtonLeft 13
#define flipperButtonRight 12

//definiere Hebel Pins
#define flipperLeft 2
#define flipperRight 15

uint32_t i = 0;

void setup() {
  //Pins initialisieren
  pinMode(flipperButtonLeft, INPUT_PULLUP);
  pinMode(flipperButtonRight, INPUT_PULLUP);
  pinMode(flipperLeft, OUTPUT);
  pinMode(flipperRight, OUTPUT);

  //Beginne Serielle Kommunikation mit dem PC
  Serial.begin(9600);
  //Serial.setDebugOutput(true);

  //Starte Serielle Kommunikation mit ESP
  Wire.begin();

  //TODO Handshake implementieren
}

void loop() {
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

void SendMessage(String message){
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.write(message.c_str());  //Needs changing to binary
  uint8_t error = Wire.endTransmission(true); //Beende die Übertragung und speichere potentielle Fehler
}


//Potentielle Request Funktion
/*
// Read 16 bytes from the slave
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 16);
  
  Serial.printf("requestFrom: %u\n", bytesReceived);
  if ((bool)bytesReceived) {  //If received more than zero bytes
    uint8_t temp[bytesReceived];
    Wire.readBytes(temp, bytesReceived);
    log_print_buf(temp, bytesReceived);
  }

*/