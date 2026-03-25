#include <Arduino.h>

//definiere RX und TX pins
#define RXD2 16
#define TXD2 17

//definiere Variablen
//ESP ist standardmäßig slave
bool master = false;
#define mastercheck 22

//Zählervariable für temporären Test der Kommunikation
int counter = 0;

//Neuer Serial-Kanal für die ESPs
HardwareSerial espSerial(2);

void setup() {
  //beginne Serielle Kommunikation zum Computer
  Serial.begin(9600);

  //beginne Serielle Kommunikation mit ESPs
  espSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Communikation established with baud rate of 9600");

  //Definition ob der ESP zum Master wird erfolgt durch äußere Einflüsse
  //1. weil ich nicht mehrere Dateien haben will,
  //2. weil ich nicht weiß wie ich über PlatformIO einzelne Dateien hochlade :(
  
  //Master Bedingung ist Strom auf dem mastercheck pin
  pinMode(mastercheck, INPUT);
  if(digitalRead(mastercheck) == HIGH){
    master = true;
    Serial.println("This Device behaves as MASTER");
    Serial.println();
  }
  else{
    Serial.println("This Device behaves as SLAVE");
    Serial.println();
  }
}

void loop() {
  //Check ob der ESP Master oder Slave ist
  if(master){   //Master Code
    //Senden der Counter Variable an den anderen ESP
    espSerial.println(String(counter));

    //Ausgabe zur Kontrolle am PC
    Serial.println("Send the following: " + String(counter));

    //erhöhen der Counter Variable und Taktung auf 1s
    counter++;
    delay(1000);
  }
  else{ //Slave Code

    if (espSerial.available()) {
      // Read data and display it
      String message = espSerial.readStringUntil('\n');
      Serial.println("Received: " + message);
    }
  }
}