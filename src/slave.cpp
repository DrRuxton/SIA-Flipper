#include <Arduino.h>
#include <Wire.h>
#include <Protocol.h>

Package lastReceived;   //letztes eingegangenes Package
bool connected = false; //variable für conection check

void evaluatePackage();

void onRequest() {
  Package reply;
  if (lastReceived.index == HSM) {
    char version[5];
    reply = makePackage(HSS, itoa(PROT_VER, version, 4));   //wilde conversion idk better XD
  }
  else {
    reply = makePackage(INF, "Idle");
  }
  Wire.write((uint8_t*)&reply, sizeof(Package));
}

void onReceive(int len) {
  //speichere Package ab
  uint8_t* ptr = (uint8_t*)&lastReceived;
  for (int i = 0; i < sizeof(Package) && Wire.available(); i++){
    ptr[i] = Wire.read();
  }

  //Einfache überprüfung ob die Daten korrupt sind
  if (lastReceived.length != strlen(lastReceived.message)) {
    Serial.println("[ERROR] received corrupted Package");
  } 
  else {
    Serial.println("[INFO] slave received package");
    Serial.print("[INFO] package: ");
    Serial.println(lastReceived.message);
    evaluatePackage();
  }
}

void evaluatePackage(){
  switch(lastReceived.index){ //Packages nach Typ sortiert behandeln
    case HSM:
      connected = true;
      break;
    case HSS:
      break;
    case MSG:
      break;
    case ERR:
      break;
    case INF:
      break;
  }
}

void setup() {
  //Beginne Serielle Kommunikation mit dem PC
  Serial.begin(9600);
  Serial.setDebugOutput(false);

  //Setze Interrupt voids
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);

  //Starte ESP Kommunikation
  Wire.begin(I2C_DEV_ADDR);
}

void loop(){
  //nothing to see
}