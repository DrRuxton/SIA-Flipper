#include <Arduino.h>
#include <Wire.h>
#include <Protocol.h>

bool connected = false;   //variable für conection check
Package lastReceived;


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


void setup() {
  //Beginne Serielle Kommunikation mit dem PC
  Serial.begin(9600);
  Serial.setDebugOutput(false);

  //Starte Serielle Kommunikation mit ESP
  Wire.begin();

  //Ausführen des Setups im Hebel Modul
  hebelSetup();

  //Handshake durchführen
  while (!connected) {
    sendPackage(makePackage(HSM, "Work you fool"));
    lastReceived = requestPackage();

    if (lastReceived.index == HSS) {
        connected = true;
        Serial.println("[INFO] connection established successfully");
    } else {
        Serial.println("[FATAL] no or incorrect answer from slave");
        delay(5000);
    }
}
}

