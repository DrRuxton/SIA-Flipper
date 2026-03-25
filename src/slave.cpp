#include <Arduino.h>
#include <Wire.h>

#define I2C_DEV_ADDR 0x55

uint32_t i = 0;

void onRequest() {
  Wire.write(String(i++).c_str());
  Wire.write(" Packets.");
  Serial.println("onRequest");
  Serial.println();
}

void onReceive(int len) {
  Serial.printf("onReceive[%d]: ", len);
  while (Wire.available()) {
    Serial.write(Wire.read());
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  Wire.begin((uint8_t)I2C_DEV_ADDR);
}

void loop(){
  //nothing to see
}