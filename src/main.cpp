#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

//ToDo pins als Variablen hinterlegen

void setup() {
  //ToDo Pin Deklarationen (evtl. automatisiert)
  tft.begin();
  tft.fillScreen(TFT_RED);
}

void loop() {
  //Programmablauf einbauen
  digitalWrite(25, HIGH);

}

//GRAFIKCHIP IST WAHRSCHEINLICH ILI9488