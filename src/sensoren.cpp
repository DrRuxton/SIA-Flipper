#include <Arduino.h>

bool lightSensorTriggered(int pin){
    int analogValue = analogRead(pin);
    Serial.println(analogValue);
    if(analogValue < 1000){
        return true;
    }
    else{
        return false;
    }
}