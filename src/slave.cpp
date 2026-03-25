#include <Arduino.h>
#include <Wire.h>

//Adresse des I2C Geräts (muss gleich der Adresse des Masters sein)
#define I2C_DEV_ADDR 0x55

uint32_t i = 0;

void onRequest() {
  Wire.write(String(i++).c_str());
  Wire.write(" Packets.");
}

void onReceive(int len) {
  while (Wire.available()) {
    Serial.write(Wire.read());
  }
  Serial.println();
}

void setup() {
  //Beginne Serielle Kommunikation mit dem PC
  Serial.begin(9600);
  //Serial.setDebugOutput(true);

  //Setze Interrupt voids
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);

  //Starte ESP Kommunikation
  Wire.begin((uint8_t)I2C_DEV_ADDR);
}

void loop(){
  //nothing to see
}