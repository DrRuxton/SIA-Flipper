#include <Arduino.h>
#include <Wire.h>
#include <Protocol.h>

bool connected = false;   //variable für conection check

//Funktionsprototypen für das Hebel Modul
void hebelSetup();

void sendPackage(const Package& p) {
    Wire.beginTransmission(I2C_DEV_ADDR);
    Wire.write((uint8_t*)&p, sizeof(Package));
    Wire.endTransmission();
}

Package requestPackage() {
    Package p;
    Wire.requestFrom(I2C_DEV_ADDR, (uint8_t)sizeof(Package));
    uint8_t* ptr = (uint8_t*)&p;
    for (int i = 0; i < sizeof(Package) && Wire.available(); i++)
        ptr[i] = Wire.read();
    return p;
}

void makeHandshake(){
  //Handshake einleiten
  sendPackage(makePackage(HSM, "Work you fool"));

  //Antwort auf Handshake anfordern
  if(requestPackage().index != HSS){
    Serial.println("[FATAL] no or incorrect answer from slave");
    Serial.println("[INFO] retrtrying in 5 seconds");
    delay(5000);
    makeHandshake();
  }
  else{
    connected = true;
    Serial.println("[INFO] connection established successfully");
  }
}

void setup() {
  //Beginne Serielle Kommunikation mit dem PC
  Serial.begin(9600);

  //Starte Serielle Kommunikation mit ESP
  Wire.begin();

  //Ausführen des Setups im Hebel Modul
  hebelSetup();

  //Handshake durchführen
  makeHandshake();
}

