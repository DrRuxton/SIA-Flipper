#include <Arduino.h>
#include <Wire.h>

//Adresse des I2C Geräts (muss gleich der Adresse des Slaves sein)
#define I2C_DEV_ADDR 0x55

uint32_t i = 0;

//Funktionsprototypen für das Hebel Modul
void hebelSetup();

void setup() {
  //Beginne Serielle Kommunikation mit dem PC
  Serial.begin(9600);

  //Starte Serielle Kommunikation mit ESP
  Wire.begin();

  //TODO Handshake implementieren

  //Ausführen des Setups im Hebel Modul
  hebelSetup();
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